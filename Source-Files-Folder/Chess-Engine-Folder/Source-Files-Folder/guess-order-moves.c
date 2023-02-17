
#include "../Header-Files-Folder/engine-include-file.h"

bool ordered_legal_moves(Move** moveArray, int* moveAmount, const Piece board[], State state, uint8_t evalTeam)
{
	if(!team_legal_moves(moveArray, moveAmount, board, state)) return false;

	return guess_order_moves(*moveArray, *moveAmount, board, state, evalTeam);
}

bool guess_order_moves(Move* moveArray, int moveAmount, const Piece board[], State state, uint8_t evalTeam)
{
	if(moveAmount <= 0) return false;

	int* moveScores;
	if(!guess_moves_scores(&moveScores, moveArray, moveAmount, board, state, evalTeam)) return false;

	qsort_moves_scores(moveArray, moveScores, moveAmount, evalTeam);

	free(moveScores); return true;
}

bool guess_moves_scores(int** moveScores, const Move moveArray[], int moveAmount, const Piece board[], State state, uint8_t evalTeam)
{
	if(moveAmount <= 0) return false;

	*moveScores = create_score_array(moveAmount);

	for(int index = 0; index < moveAmount; index += 1)
	{
		(*moveScores)[index] = guess_move_score(board, state, evalTeam, moveArray[index]);
	}
	return true;
}

int guess_move_score(const Piece board[], State state, uint8_t evalTeam, Move move)
{
	int moveScore = 0;

	Piece stopPiece = MOVE_STOP_PIECE(board, move);

	if(!PIECE_STORE_TYPE(stopPiece, PIECE_TYPE_NONE))
	{
		Piece startPiece = MOVE_START_PIECE(board, move);

		int stopScore = CHESS_PIECE_SCORE(stopPiece);
		int startScore = CHESS_PIECE_SCORE(startPiece);

		moveScore = (10 * stopScore - startScore);
	}
	if(MOVE_PROMOTE_FLAG(move))
	{
		Piece promotePiece = move_promote_piece(move);

		moveScore += CHESS_PIECE_SCORE(promotePiece);
	}
	return TEAM_WEIGHT_SCORE(moveScore, evalTeam);
}
