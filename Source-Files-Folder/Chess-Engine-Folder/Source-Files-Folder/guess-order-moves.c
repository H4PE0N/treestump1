
#include "../Header-Files-Folder/engine-include-file.h"

bool ordered_legal_moves(Move** moveArray, int* moveAmount, const Piece board[], Info info, uint8_t team)
{
	if(!team_legal_moves(moveArray, moveAmount, board, info, team)) return false;

	return guess_order_moves(*moveArray, *moveAmount, board, info, team);
}

bool guess_order_moves(Move* moveArray, int moveAmount, const Piece board[], Info info, uint8_t team)
{
	if(moveAmount <= 0) return false;

	int* moveScores;
	if(!guess_moves_scores(&moveScores, moveArray, moveAmount, board, info)) return false;

	qsort_moves_scores(moveArray, moveScores, moveAmount, team);

	free(moveScores); return true;
}

bool guess_moves_scores(int** moveScores, const Move moveArray[], int moveAmount, const Piece board[], Info info)
{
	if(moveAmount <= 0) return false;

	*moveScores = malloc(sizeof(int) * moveAmount);
	memset(*moveScores, 0, sizeof(int) * moveAmount);

	for(int index = 0; index < moveAmount; index += 1)
	{
		(*moveScores)[index] = guess_move_score(board, info, moveArray[index]);
	}
	return true;
}

// Make this guess function better, it will benifit
int guess_move_score(const Piece board[], Info info, Move move)
{
	int moveScore = 0;

	Piece stopPieceType = STOP_PIECE_TYPE(board, move);

	if(stopPieceType != PIECE_TYPE_NONE)
	{
		Piece startPieceType = START_PIECE_TYPE(board, move);

		int stopPieceScore = PIECE_TYPE_SCORES[stopPieceType];
		int startPieceScore = PIECE_TYPE_SCORES[startPieceType];

		moveScore = (10 * stopPieceScore - startPieceScore);
	}
	if(MOVE_PROMOTE_FLAG(move)) moveScore += move_promote_piece(move);

	uint8_t startTeam = MOVE_START_TEAM(board, move);

	return TEAM_WEIGHT_SCORE(moveScore, startTeam);
}
