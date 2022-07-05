
#include "../Header-Files-Folder/engine-include-file.h"

int totalMoves = 0;

bool amount_engine_moves(Move** moveArray, const Piece board[], Info info, Kings kings, unsigned short team, signed short depth, unsigned short amount)
{
	Move* engineMoves;
	if(!sorted_engine_moves(&engineMoves, board, info, kings, team, depth)) return false;

	paste_engine_moves(moveArray, amount, engineMoves);

	free(engineMoves); return true;
}

void paste_engine_moves(Move** moveArray, unsigned short amount, const Move engineMoves[])
{
	unsigned short engineAmount = move_array_amount(engineMoves);

	*moveArray = create_move_array(amount);

	for(unsigned short index = 0; index < amount; index += 1)
	{
		if((index + 1) > engineAmount) break;

		(*moveArray)[index] = engineMoves[index];
	}
}

bool sorted_engine_moves(Move** moveArray, const Piece board[], Info info, Kings kings, unsigned short team, signed short depth)
{
	if(depth <= 0) return false;

	if(!team_legal_moves(moveArray, board, info, kings, team)) return false;

	unsigned short moveAmount = move_array_amount(*moveArray);
	if(moveAmount <= 0) return false;

	short* moveValues = NULL;
	if(!move_array_values(&moveValues, board, info, kings, team, depth, *moveArray)) return false;

	qsort_moves_values(*moveArray, moveValues, moveAmount, team);

	free(moveValues); return true;
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
		if(!chess_move_value(&moveValue, board, info, kings, team, (depth - 1), MIN_STATE_VALUE, MAX_STATE_VALUE, currentMove))
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

bool chess_move_value(signed short* moveValue, const Piece board[], Info info, Kings kings, unsigned short currentTeam, signed short depth, signed short alpha, signed short beta, Move move)
{
	Info infoCopy = info;
	infoCopy = ALLOC_INFO_TEAM(infoCopy, TEAM_INFO_MACRO(currentTeam));

	Kings kingsCopy = kings;

	Piece* boardCopy = malloc(sizeof(Piece) * BOARD_LENGTH);
	memcpy(boardCopy, board, sizeof(Piece) * BOARD_LENGTH);

	bool result = simulate_move_value(moveValue, boardCopy, infoCopy, kingsCopy, currentTeam, depth, alpha, beta, move);

	free(boardCopy); return result;
}

bool simulate_move_value(signed short* moveValue, Piece* boardCopy, Info infoCopy, Kings kingsCopy, unsigned short currentTeam, signed short depth, signed short alpha, signed short beta, Move move)
{
	if(!move_chess_piece(boardCopy, &infoCopy, &kingsCopy, move)) return false;

	unsigned short nextTeam = normal_team_enemy(currentTeam);

	*moveValue = board_depth_value(boardCopy, infoCopy, kingsCopy, nextTeam, depth, alpha, beta);

	return true;
}

bool create_engine_move(Move* move, const Piece board[], Info info, Kings kings, unsigned short currentTeam, signed short depth)
{
	if(depth <= 0) return false;

	Move* moveArray;
	if(!team_legal_moves(&moveArray, board, info, kings, currentTeam)) return false;

	bool result = choose_engine_move(move, board, info, kings, currentTeam, depth, moveArray);

	free(moveArray); return result;
}

bool choose_engine_move(Move* move, const Piece board[], Info info, Kings kings, unsigned short currentTeam, signed short depth, const Move moveArray[])
{
	unsigned short moveAmount = move_array_amount(moveArray);

	if(moveAmount <= 0) return false;


	Move bestMove = moveArray[0];
	signed short bestValue = team_weight_value(MIN_STATE_VALUE, currentTeam);

	for(unsigned short index = 0; index < moveAmount; index += 1)
	{
		Move currentMove = moveArray[index];

		short currentValue;
		if(!chess_move_value(&currentValue, board, info, kings, currentTeam, (depth - 1), MIN_STATE_VALUE, MAX_STATE_VALUE, currentMove)) continue;

		printf("CurrentMove: [%d -> %d]\tCurrentValue: %d\n", MOVE_START_MACRO(currentMove), MOVE_STOP_MACRO(currentMove), currentValue);

		if((currentTeam == TEAM_WHITE && currentValue > bestValue) ||
			(currentTeam == TEAM_BLACK && currentValue < bestValue))
		{
			bestMove = currentMove; bestValue = currentValue;
		}
	}
	printf("Total Moves: %d\n", totalMoves);

	*move = bestMove; return true;
}

unsigned short board_depth_value(const Piece board[], Info info, Kings kings, unsigned short currentTeam, signed short depth, signed short alpha, signed short beta)
{
	if(depth <= 0)
	{
		totalMoves += 1;

		return board_state_value(board, info, kings);
	}

	Move* moveArray;
	if(!team_legal_moves(&moveArray, board, info, kings, currentTeam))
		return board_state_value(board, info, kings);

	signed short bestValue = choose_move_value(board, info, kings, currentTeam, depth, alpha, beta, moveArray);

	free(moveArray); return bestValue;
}

signed short choose_move_value(const Piece board[], Info info, Kings kings, unsigned short currentTeam, signed short depth, signed short alpha, signed short beta, const Move moveArray[])
{
	unsigned short moveAmount = move_array_amount(moveArray);

	if(moveAmount <= 0) return board_state_value(board, info, kings);


	signed short bestValue = team_weight_value(MIN_STATE_VALUE, currentTeam);

	for(unsigned short index = 0; index < moveAmount; index += 1)
	{
		Move currentMove = moveArray[index];

		short currentValue;
		if(!chess_move_value(&currentValue, board, info, kings, currentTeam, (depth - 1), alpha, beta, currentMove)) continue;

		update_best_value(currentValue, &bestValue, currentTeam);

		update_alpha_beta(currentValue, &alpha, &beta, currentTeam);

		if(beta <= alpha) break;
	}
	return bestValue;
}

void update_best_value(signed short currentValue, signed short* bestValue, unsigned short team)
{
	if(team == TEAM_WHITE) *bestValue = MAX_NUMBER_VALUE(*bestValue, currentValue);
	if(team == TEAM_BLACK) *bestValue = MIN_NUMBER_VALUE(*bestValue, currentValue);
}

void update_alpha_beta(signed short currentValue, signed short* alpha, signed short* beta, unsigned short team)
{
	if(team == TEAM_WHITE) *alpha = MAX_NUMBER_VALUE(*alpha, currentValue);
	if(team == TEAM_BLACK) *beta = MIN_NUMBER_VALUE(*beta, currentValue);
}
