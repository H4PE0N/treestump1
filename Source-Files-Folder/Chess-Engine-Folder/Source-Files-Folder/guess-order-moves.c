
#include "../Header-Files-Folder/engine-include-file.h"

bool ordered_legal_moves(Move** moveArray, const Piece board[], Info info, unsigned short team)
{
	if(!team_legal_moves(moveArray, board, info, team)) return false;

	unsigned short moveAmount = move_array_amount(*moveArray);

	return guess_order_moves(*moveArray, moveAmount, board, info);
}

bool guess_order_moves(Move* moveArray, short moveAmount, const Piece board[], Info info)
{
	if(moveAmount <= 0) return false;

	signed short* moveValues = NULL;
	if(!guess_moves_values(&moveValues, moveArray, moveAmount, board, info)) return false;

	unsigned short team = MOVE_START_TEAM(board, moveArray[0]);

	qsort_moves_values(moveArray, moveValues, moveAmount, team);

	free(moveValues); return true;
}

bool guess_moves_values(signed short** moveValues, const Move moveArray[], short moveAmount, const Piece board[], Info info)
{
	if(moveAmount <= 0) return false;

	*moveValues = create_short_array(moveAmount);

	for(unsigned short index = 0; index < moveAmount; index += 1)
	{
		Move currentMove = moveArray[index];

		signed short moveValue = guess_move_value(board, info, currentMove);

		(*moveValues)[index] = moveValue;
	}
	return true;
}

signed short guess_move_value(const Piece board[], Info info, Move move)
{
	signed short moveScore = 0;

	Piece startPieceType = START_PIECE_TYPE(board, move);
	Piece stopPieceType = STOP_PIECE_TYPE(board, move);

	unsigned short startTeam = MOVE_START_TEAM(board, move);

	if(stopPieceType != PIECE_TYPE_NONE)
	{
		signed short stopPieceValue = PIECE_TYPE_VALUES[stopPieceType];
		signed short startPieceValue = PIECE_TYPE_VALUES[startPieceType];

		moveScore = 10 * stopPieceValue - startPieceValue;
	}

	if(MOVE_PROMOTE_FLAG(move)) moveScore += move_promote_piece(move);

	return team_weight_value(moveScore, startTeam);
}
