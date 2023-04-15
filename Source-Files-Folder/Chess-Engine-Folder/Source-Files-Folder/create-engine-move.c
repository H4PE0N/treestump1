
#include "../Header-Files-Folder/engine-include-file.h"

bool engine_depth_move(Move* bestMove, const Piece board[], State state, Entry* hashTable, int depth)
{
	if(depth <= 0) return false;

	Move* moveArray; int moveAmount;
	if(!team_legal_moves(&moveArray, &moveAmount, board, state)) return false;

	int playerSign = CURRENT_TEAM_WEIGHT(state);

	bool result = choose_engine_move(bestMove, board, state, hashTable, depth, playerSign, moveArray, moveAmount);

	free(moveArray); return result;
}

bool choose_engine_move(Move* bestMove, const Piece board[], State state, Entry* hashTable, int depth, int playerSign, const Move moveArray[], int moveAmount)
{
	if(moveAmount <= 0) return false;

	*bestMove = moveArray[0]; int bestScore = -MATE_SCORE;

	if(moveAmount == 1) return true;

	for(int index = 0; index < moveAmount; index += 1)
	{
		Move currMove = moveArray[index];

		int currScore = chess_move_score(board, state, hashTable, depth, -MATE_SCORE, MATE_SCORE, playerSign, currMove);

		if(currScore <= bestScore) continue;

		*bestMove = currMove; bestScore = currScore;
	}
	return true;
}

bool lookup_hash_entry(int* bestScore, Entry* hashTable, uint64_t zobristHash, int depth, int* alpha, int* beta)
{
	int hashIndex = HASH_TABLE_INDEX(zobristHash);

	Entry oldEntry = hashTable[hashIndex];

	if((oldEntry.hash != zobristHash) || (oldEntry.depth < depth)) return false;

	if(oldEntry.flag == ENTRY_FLAG_EXACT)
	{
		*bestScore = oldEntry.score; return true;
	}
	else if(oldEntry.flag == ENTRY_FLAG_LOWER)
	{
		*alpha = MAX_NUMBER_VALUE(*alpha, oldEntry.score);
	}
	else if(oldEntry.flag == ENTRY_FLAG_UPPER)
	{
		*beta = MIN_NUMBER_VALUE(*beta, oldEntry.score);
	}
	if(*alpha < *beta) return false;

	*bestScore = oldEntry.score; return true;
}

bool store_hash_entry(Entry* hashTable, uint64_t zobristHash, int depth, int alpha, int beta, int score)
{
	int hashIndex = HASH_TABLE_INDEX(zobristHash);

	Entry newEntry = {.hash = zobristHash, .depth = depth, .score = score};

	if(score <= alpha) newEntry.flag = ENTRY_FLAG_UPPER;

	else if(score >= beta) newEntry.flag = ENTRY_FLAG_LOWER;

	else newEntry.flag = ENTRY_FLAG_EXACT;

	hashTable[hashIndex] = newEntry; return true;
}

int entry_board_score(const Piece board[], State state, Entry* hashTable, int depth, int alpha, int beta, int playerSign)
{
	uint64_t zobristHash = create_zobrist_hash(board, state);

	int bestScore;

	if(lookup_hash_entry(&bestScore, hashTable, zobristHash, depth, &alpha, &beta)) return bestScore;

	bestScore = board_depth_score(board, state, hashTable, depth, alpha, beta, playerSign);

	store_hash_entry(hashTable, zobristHash, depth, alpha, beta, bestScore);

	return bestScore;
}

int board_depth_score(const Piece board[], State state, Entry* hashTable, int depth, int alpha, int beta, int playerSign)
{
	if(depth <= 0) return (playerSign * board_state_score(board, state));

	int team = STATE_CURRENT_MACRO(state);

	Move* moveArray; int moveAmount;
	if(!ordered_legal_moves(&moveArray, &moveAmount, board, state, team))
	{
		return (playerSign * board_state_score(board, state));
	}
	int bestScore = choose_move_score(board, state, hashTable, depth, alpha, beta, playerSign, moveArray, moveAmount);

	free(moveArray); return bestScore;
}

int choose_move_score(const Piece board[], State state, Entry* hashTable, int depth, int alpha, int beta, int playerSign, const Move moveArray[], int moveAmount)
{
	int bestScore = -MATE_SCORE;

	for(int index = 0; index < moveAmount; index += 1)
	{
		int currScore = chess_move_score(board, state, hashTable, depth, alpha, beta, playerSign, moveArray[index]);

		bestScore = MAX_NUMBER_VALUE(bestScore, currScore);

		alpha = MAX_NUMBER_VALUE(alpha, bestScore);

		if(alpha >= beta) break;
	}
	return bestScore;
}

int chess_move_score(const Piece board[], State state, Entry* hashTable, int depth, int alpha, int beta, int playerSign, Move move)
{
	Piece* boardCopy = copy_chess_board(board);

	int moveScore = simulate_move_score(boardCopy, state, hashTable, depth, alpha, beta, playerSign, move);

	free(boardCopy); return moveScore;
}

int simulate_move_score(Piece* boardCopy, State stateCopy, Entry* hashTable, int depth, int alpha, int beta, int playerSign, Move move)
{
	if(!execute_chess_move(boardCopy, &stateCopy, move)) return 0;

	return -entry_board_score(boardCopy, stateCopy, hashTable, (depth - 1), -beta, -alpha, -playerSign);
}
