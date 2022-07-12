
#include "../Header-Files-Folder/engine-include-file.h"

bool amount_engine_moves(Move** moveArray, const Piece board[], Info info, unsigned short team, short depth, short amount)
{
	Move* engineMoves;
	if(!sorted_engine_moves(&engineMoves, board, info, team, depth)) return false;

	unsigned short engineAmount = move_array_amount(engineMoves);

	paste_engine_moves(moveArray, amount, engineMoves, engineAmount);

	free(engineMoves); return true;
}

void paste_engine_moves(Move** moveArray, short amount, const Move engineMoves[], short engineAmount)
{
	*moveArray = create_move_array(amount);

	for(unsigned short index = 0; index < amount; index += 1)
	{
		if((index + 1) > engineAmount) break;

		(*moveArray)[index] = engineMoves[index];
	}
}

bool sorted_engine_moves(Move** moveArray, const Piece board[], Info info, unsigned short team, short depth)
{
	if(depth <= 0) return false;

	if(!team_legal_moves(moveArray, board, info, team)) return false;

	unsigned short moveAmount = move_array_amount(*moveArray);
	if(moveAmount <= 0) return false;

	short* moveValues = NULL;
	if(!move_array_values(&moveValues, board, info, team, depth, *moveArray, moveAmount)) return false;

	qsort_moves_values(*moveArray, moveValues, moveAmount, team);

	free(moveValues); return true;
}

bool move_array_values(short** moveValues, const Piece board[], Info info, unsigned short team, short depth, const Move moveArray[], short moveAmount)
{
	if(moveAmount <= 0) return false;

	*moveValues = create_short_array(moveAmount);

	for(unsigned short index = 0; index < moveAmount; index += 1)
	{
		Move currentMove = moveArray[index];

		signed short moveValue = 0;
		if(!chess_move_value(&moveValue, board, info, team, (depth - 1), MIN_STATE_VALUE, MAX_STATE_VALUE, currentMove))
		{
			free(*moveValues); return false;
		}

		(*moveValues)[index] = moveValue;
	}
	return true;
}

short* create_short_array(unsigned short length)
{
	short* moveValues = malloc(sizeof(short) * (length + 1));
	for(unsigned short index = 0; index < (length + 1); index += 1)
	{
		moveValues[index] = 0;
	}
	return moveValues;
}
