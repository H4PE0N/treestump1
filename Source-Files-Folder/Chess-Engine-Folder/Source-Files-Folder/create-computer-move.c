
#include "../Header-Files-Folder/engine-include-file.h"

bool amount_engine_moves(Move** moveArray, const Piece board[], Info info, Kings kings, unsigned short team, signed short depth, unsigned short amount)
{
	Move* engineMoves;
	if(!sorted_engine_moves(&engineMoves, board, info, kings, team, depth)) return false;

	unsigned short moveAmount = move_array_amount(engineMoves);

	*moveArray = create_move_array(amount);

	for(short index = 0; index < amount; index += 1)
	{
		if(index > (moveAmount - 1) ) break;

		(*moveArray)[index] = engineMoves[index];
	}
	free(engineMoves); return true;
}

bool sorted_engine_moves(Move** moveArray, const Piece board[], Info info, Kings kings, unsigned short team, signed short depth)
{
	if(depth <= 0) return false;

	if(!team_legal_moves(moveArray, board, info, kings, team)) return false;

	unsigned short moveAmount = move_array_amount(*moveArray);

	if(moveAmount <= 0) return false;


	short* moveValues = NULL;
	if(!move_array_values(&moveValues, board, info, kings, team, depth, *moveArray)) return false;

	qsort_moves_values(*moveArray, moveValues, moveAmount);

	free(moveValues); return true;
}

void qsort_moves_values(Move* moveArray, short* moveValues, unsigned short length)
{
	qsort_moves_indexis(moveArray, moveValues, 0, length - 1);
}

void qsort_moves_indexis(Move* moveArray, short* moveValues, short index1, short index2)
{
	if(index1 >= index2) return;

	short partIndex = partly_qsort_moves(moveArray, moveValues, index1, index2);

	qsort_moves_indexis(moveArray, moveValues, index1, partIndex - 1);

	qsort_moves_indexis(moveArray, moveValues, partIndex + 1, index2);
}

short partly_qsort_moves(Move* moveArray, short* moveValues, short index1, short index2)
{
	short pivotValue = moveValues[index2];

	short iIndex = (index1 - 1);

	for(short jIndex = index1; jIndex <= index2 - 1; jIndex += 1)
	{
		if(moveValues[jIndex] > pivotValue)
		{
			qswap_moves_values(moveArray, moveValues, ++iIndex, jIndex);
		}
	}
	qswap_moves_values(moveArray, moveValues, iIndex + 1, index2);

	return (iIndex + 1);
}

void qswap_moves_values(Move* moveArray, short* moveValues, short index1, short index2)
{
	short tempValue = moveValues[index1];

	moveValues[index1] = moveValues[index2];

	moveValues[index2] = tempValue;


	Move tempMove = moveArray[index1];

	moveArray[index1] = moveArray[index2];

	moveArray[index2] = tempMove;
}

bool move_array_values(short** moveValues, const Piece board[], Info info, Kings kings, unsigned short team, signed short depth, const Move moveArray[])
{
	unsigned short moveAmount = move_array_amount(moveArray);

	if(moveAmount <= 0) return false;

	*moveValues = create_short_array(moveAmount);

	for(unsigned short index = 0; index < moveAmount; index += 1)
	{
		Move currentMove = moveArray[index];

		signed short moveValue = 0;
		if(!chess_move_value(&moveValue, board, info, kings, depth, MIN_BOARD_VALUE, MAX_BOARD_VALUE, team, team, currentMove))
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

bool chess_move_value(signed short* moveValue, const Piece board[], Info info, Kings kings, signed short depth, short alpha, short beta, unsigned short team, unsigned short currentTeam, Move move)
{
	Info infoCopy = info;
	infoCopy = ALLOC_INFO_TEAM(infoCopy, TEAM_INFO_MACRO(currentTeam));

	Kings kingsCopy = kings;

	Piece* boardCopy = malloc(sizeof(Piece) * BOARD_LENGTH);
	memcpy(boardCopy, board, sizeof(Piece) * BOARD_LENGTH);

	bool result = simulate_move_value(moveValue, boardCopy, infoCopy, kingsCopy, depth, alpha, beta, team, currentTeam, move);

	free(boardCopy); return result;
}

bool simulate_move_value(signed short* moveValue, Piece* boardCopy, Info infoCopy, Kings kingsCopy, signed short depth, short alpha, short beta, unsigned short team, unsigned short currentTeam, Move move)
{
	if(!move_chess_piece(boardCopy, &infoCopy, &kingsCopy, move)) return false;

	unsigned short nextTeam = normal_team_enemy(currentTeam);

	*moveValue = board_depth_value(boardCopy, infoCopy, kingsCopy, depth, alpha, beta, team, nextTeam);

	return true;
}

bool best_computer_move(Move* move, const Piece board[], Info info, Kings kings, unsigned short team, signed short depth)
{
	if(depth <= 0) return false;

	Move* moveArray;
	if(!team_legal_moves(&moveArray, board, info, kings, team)) return false;

	unsigned short movesAmount = move_array_amount(moveArray);

	if(movesAmount <= 0) { free(moveArray); return false; }

	Move bestMove = moveArray[0];
	signed short bestValue = MIN_BOARD_VALUE;

	for(unsigned short index = 0; index < movesAmount; index += 1)
	{
		Move currentMove = moveArray[index];

		short currentValue;
		if(!chess_move_value(&currentValue, board, info, kings, (depth - 1), MIN_BOARD_VALUE, MAX_BOARD_VALUE, team, team, currentMove)) continue;

		printf("CurrentMove: [%d -> %d]\tCurrentValue: %d\n", MOVE_START_MACRO(currentMove), MOVE_STOP_MACRO(currentMove), currentValue);

		if(currentValue > bestValue)
		{
			bestMove = currentMove; bestValue = currentValue;
		}
	}
	free(moveArray); *move = bestMove; return true;
}

unsigned short board_depth_value(const Piece board[], Info info, Kings kings, signed short depth, signed short alpha, signed short beta, unsigned short team, unsigned short currentTeam)
{
	if(!normal_team_exists(team) || !normal_team_exists(currentTeam)) return 0;

	if(depth <= 0) return team_state_value(board, info, kings, team);


	Info infoCopy = info;
	infoCopy = ALLOC_INFO_TEAM(infoCopy, TEAM_INFO_MACRO(currentTeam));

	Move* moveArray;
	if(!team_legal_moves(&moveArray, board, infoCopy, kings, currentTeam)) return false;

	unsigned short movesAmount = move_array_amount(moveArray);

	if(movesAmount <= 0)
	{
		free(moveArray);

		return team_state_value(board, info, kings, team);
	}

	signed short bestValue = (currentTeam == team) ? MIN_BOARD_VALUE : MAX_BOARD_VALUE;

	for(unsigned short index = 0; index < movesAmount; index += 1)
	{
		Move currentMove = moveArray[index];

		short currentValue;
		if(!chess_move_value(&currentValue, board, info, kings, (depth - 1), alpha, beta, team, currentTeam, currentMove)) continue;

		update_engine_vals(team, currentTeam, currentValue, &bestValue, &alpha, &beta);

		if(beta <= alpha) break;
	}
	free(moveArray); return bestValue;
}

void update_engine_vals(unsigned short team, unsigned short currentTeam, short currentValue, short* bestValue, short* alpha, short* beta)
{
	if(currentTeam == team && currentValue > *bestValue) *bestValue = currentValue;
	if(currentTeam != team && currentValue < *bestValue) *bestValue = currentValue;

	if(currentTeam == team && currentValue > *alpha) *alpha = currentValue;
	if(currentTeam != team && currentValue < *beta) *beta = currentValue;
}
