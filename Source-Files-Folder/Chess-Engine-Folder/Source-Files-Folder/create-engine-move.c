
#include "../Header-Files-Folder/engine-include-file.h"

// Maybe remove team from the arguments, and instead use info team
bool engine_depth_move(Move* bestMove, const Piece board[], Info info, int depth)
{
	if(depth <= 0) return false;

	int team = INFO_TEAM_MACRO(info);

	Move* moveArray; short moveAmount;
	if(!team_legal_moves(&moveArray, &moveAmount, board, info, team)) return false;

	int playerSign = TEAM_SCORE_WEIGHT(team);

	bool result = choose_engine_move(bestMove, board, info, depth, playerSign, moveArray, moveAmount);

	free(moveArray); return result;
}

bool choose_engine_move(Move* bestMove, const Piece board[], Info info, int depth, int playerSign, const Move moveArray[], short moveAmount)
{
	if(moveAmount <= 0) return false;

	*bestMove = moveArray[0];

	if(moveAmount == 1) return true;

	int bestScore = MIN_STATE_SCORE;

	for(int index = 0; index < moveAmount; index += 1)
	{
		Move currMove = moveArray[index];

		int currScore = chess_move_score(board, info, depth, MIN_STATE_SCORE, MAX_STATE_SCORE, playerSign, currMove);

		if(currScore > bestScore)
		{
			*bestMove = currMove; bestScore = currScore;
		}
	}
	return true;
}

int board_depth_score(const Piece board[], Info info, int depth, int alpha, int beta, int playerSign)
{
	if(depth <= 0) return (playerSign * board_state_score(board, info));

	int team = INFO_TEAM_MACRO(info);

	Move* moveArray; short moveAmount;
	if(!ordered_legal_moves(&moveArray, &moveAmount, board, info, team))
	{
		return (playerSign * board_state_score(board, info));
	}
	int bestScore = choose_move_score(board, info, depth, alpha, beta, playerSign, moveArray, moveAmount);

	free(moveArray); return bestScore;
}

int choose_move_score(const Piece board[], Info info, int depth, int alpha, int beta, int playerSign, const Move moveArray[], short moveAmount)
{
	int bestScore = MIN_STATE_SCORE;

	for(int index = 0; index < moveAmount; index += 1)
	{
		int currScore = chess_move_score(board, info, depth, alpha, beta, playerSign, moveArray[index]);

		bestScore = MAX_NUMBER_VALUE(bestScore, currScore);

		alpha = MAX_NUMBER_VALUE(alpha, bestScore);

		if(alpha >= beta) break;
	}
	return bestScore;
}

int chess_move_score(const Piece board[], Info info, int depth, int alpha, int beta, int playerSign, Move move)
{
	Piece* boardCopy = copy_chess_board(board);

	int moveScore = simulate_move_score(boardCopy, info, depth, alpha, beta, playerSign, move);

	free(boardCopy); return moveScore;
}

int simulate_move_score(Piece* boardCopy, Info infoCopy, int depth, int alpha, int beta, int playerSign, Move move)
{
	if(!execute_chess_move(boardCopy, &infoCopy, move)) return 0;

	return -board_depth_score(boardCopy, infoCopy, (depth - 1), -beta, -alpha, -playerSign);
}
