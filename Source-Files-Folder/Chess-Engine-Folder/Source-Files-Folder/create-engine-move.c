
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

	*bestMove = moveArray[0]; int bestScore = MIN_STATE_SCORE;

	if(moveAmount == 1) return true;

	for(int index = 0; index < moveAmount; index += 1)
	{
		Move currMove = moveArray[index];

		int currScore = chess_move_score(board, state, hashTable, depth, MIN_STATE_SCORE, MAX_STATE_SCORE, playerSign, currMove);

		if(currScore > bestScore)
		{
			*bestMove = currMove; bestScore = currScore;
		}
	}
	return true;
}

// Change the name of this function some time
int storgryta(const Piece board[], State state, Entry* hashTable, int depth, int alpha, int beta, int playerSign)
{
	// uint64_t zobristHash = create_zobrist_hash(board, state);
	//
	// int hashIndex = (zobristHash % HASH_TABLE_SIZE);
	//
	// Entry oldEntry = hashTable[hashIndex];
	//
	// if((oldEntry.hash == zobristHash) && (oldEntry.depth >= depth))
	// {
	// 	if(oldEntry.flag == ENTRY_FLAG_EXACT) return oldEntry.score;
	//
	// 	else if(oldEntry.flag == ENTRY_FLAG_LOWER)
	// 	{
	// 		alpha = MAX_NUMBER_VALUE(alpha, oldEntry.score);
	// 	}
	// 	else if(oldEntry.flag == ENTRY_FLAG_UPPER)
	// 	{
	// 		beta = MIN_NUMBER_VALUE(beta, oldEntry.score);
	// 	}
	// 	if(alpha >= beta) return oldEntry.score;
	// }

	int bestScore = board_depth_score(board, state, hashTable, depth, alpha, beta, playerSign);


	// Entry newEntry = (Entry) {.hash = zobristHash, .depth = depth, .score = bestScore};
	//
	// if(bestScore <= alpha) newEntry.flag = ENTRY_FLAG_UPPER;
	//
	// else if(bestScore >= beta) newEntry.flag = ENTRY_FLAG_LOWER;
	//
	// else newEntry.flag = ENTRY_FLAG_EXACT;
	//
	// hashTable[hashIndex] = newEntry;


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
	int bestScore = MIN_STATE_SCORE;

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

	return -storgryta(boardCopy, stateCopy, hashTable, (depth - 1), -beta, -alpha, -playerSign);
}
