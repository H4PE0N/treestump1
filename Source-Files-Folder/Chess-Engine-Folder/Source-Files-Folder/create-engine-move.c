
#include "../Header-Files-Folder/engine-include-file.h"

long totalNodes = 0;
long totalPassant = 0;
long totalCastles = 0;
long totalPromote = 0;

bool amount_engine_moves(Move** moveArray, const Piece board[], Info info, Kings kings, unsigned short team, short depth, short amount)
{
	Move* engineMoves;
	if(!sorted_engine_moves(&engineMoves, board, info, kings, team, depth)) return false;

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

bool sorted_engine_moves(Move** moveArray, const Piece board[], Info info, Kings kings, unsigned short team, short depth)
{
	if(depth <= 0) return false;

	if(!team_legal_moves(moveArray, board, info, kings, team)) return false;

	unsigned short moveAmount = move_array_amount(*moveArray);
	if(moveAmount <= 0) return false;

	short* moveValues = NULL;
	if(!move_array_values(&moveValues, board, info, kings, team, depth, *moveArray, moveAmount)) return false;

	qsort_moves_values(*moveArray, moveValues, moveAmount, team);

	free(moveValues); return true;
}

bool move_array_values(short** moveValues, const Piece board[], Info info, Kings kings, unsigned short team, short depth, const Move moveArray[], short moveAmount)
{
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

bool chess_move_value(signed short* moveValue, const Piece board[], Info info, Kings kings, unsigned short currentTeam, short depth, signed short alpha, signed short beta, Move move)
{
	Info infoCopy = info;
	infoCopy = ALLOC_INFO_TEAM(infoCopy, TEAM_INFO_MACRO(currentTeam));

	Piece* boardCopy = copy_chess_board(board);

	if(depth <= 0)
	{
		totalNodes += 1;

		Move moveFlag = MASK_MOVE_FLAG(move);

		if(moveFlag == MOVE_FLAG_CASTLE) totalCastles += 1;

		if(moveFlag == MOVE_FLAG_PASSANT) totalPassant += 1;

		if(moveFlag == MOVE_FLAG_KNIGHT || moveFlag == MOVE_FLAG_BISHOP || moveFlag == MOVE_FLAG_ROOK || moveFlag == MOVE_FLAG_QUEEN) totalPromote += 1;
	}

	bool result = simulate_move_value(moveValue, boardCopy, infoCopy, kings, currentTeam, depth, alpha, beta, move);

	free(boardCopy); return result;
}

bool simulate_move_value(signed short* moveValue, Piece* boardCopy, Info infoCopy, Kings kingsCopy, unsigned short currentTeam, short depth, signed short alpha, signed short beta, Move move)
{
	if(!move_chess_piece(boardCopy, &infoCopy, &kingsCopy, move)) return false;

	unsigned short nextTeam = normal_team_enemy(currentTeam);

	*moveValue = board_depth_value(boardCopy, infoCopy, kingsCopy, nextTeam, depth, alpha, beta);

	return true;
}

bool optimal_depth_move(Move* move, const Piece board[], Info info, Kings kings, unsigned short team, short seconds)
{
	Move* moveArray;
	if(!team_legal_moves(&moveArray, board, info, kings, team)) return false;

	unsigned short moveAmount = move_array_amount(moveArray);

	bool result = search_depths_move(move, board, info, kings, team, seconds, moveArray, moveAmount);

	free(moveArray); return result;
}

bool search_depths_move(Move* move, const Piece board[], Info info, Kings kings, unsigned short team, short seconds, const Move moveArray[], short moveAmount)
{
	if(moveAmount <= 0) return false;

	if(moveAmount == 1)
	{
		*move = moveArray[0];

		return true;
	}

	long startClock = clock();

	Move engineMove = moveArray[0];
	signed short engineValue = 0;

	double time = (double) (clock() - startClock) / CLOCKS_PER_SEC;

	for(unsigned short depth = 1; time < seconds; depth += 1)
	{
		if(!choose_timing_move(&engineMove, &engineValue, board, info, kings, team, depth, startClock, seconds, moveArray, moveAmount)) return false;

		if((team == TEAM_WHITE && engineValue > team_weight_value(MATE_VALUE, team)) ||
			(team == TEAM_BLACK && engineValue < team_weight_value(MATE_VALUE, team))) break;

		time = (double) (clock() - startClock) / CLOCKS_PER_SEC;

		printf("Depth: %d Time: %.2f Move: %d -> %d\n", depth, time, MOVE_START_MACRO(engineMove), MOVE_STOP_MACRO(engineMove));
	}
	*move = engineMove; return true;
}

bool choose_timing_move(Move* move, signed short* value, const Piece board[], Info info, Kings kings, unsigned short team, short depth, long startClock, short seconds, const Move moveArray[], short moveAmount)
{
	if(moveAmount <= 0) return false;


	totalNodes = 0;
	totalPassant = 0;
	totalCastles = 0;
	totalPromote = 0;


	Move bestMove = moveArray[0];
	signed short bestValue = team_weight_value(MIN_STATE_VALUE, team);

	for(unsigned short index = 0; index < moveAmount; index += 1)
	{
		double time = (double) (clock() - startClock) / CLOCKS_PER_SEC;
		if(time >= seconds) return true;

		Move currentMove = moveArray[index];

		short currentValue;
		if(!chess_move_value(&currentValue, board, info, kings, team, (depth - 1), MIN_STATE_VALUE, MAX_STATE_VALUE, currentMove)) continue;

		if((team == TEAM_WHITE && currentValue > team_weight_value(MATE_VALUE, team)) ||
			(team == TEAM_BLACK && currentValue < team_weight_value(MATE_VALUE, team)))
		{
			bestMove = currentMove; bestValue = currentValue;

			break;
		}

		if((team == TEAM_WHITE && currentValue > bestValue) ||
			(team == TEAM_BLACK && currentValue < bestValue))
		{
			bestMove = currentMove; bestValue = currentValue;
		}
	}
	printf("Nodes=%ld Passant=%ld Castles=%ld Promote=%ld\n", totalNodes, totalPassant, totalCastles, totalPromote);

	*move = bestMove; *value = bestValue; return true;
}

bool engine_depth_move(Move* move, const Piece board[], Info info, Kings kings, unsigned short team, signed short depth)
{
	if(depth <= 0) return false;

	Move* moveArray;
	if(!team_legal_moves(&moveArray, board, info, kings, team)) return false;

	unsigned short moveAmount = move_array_amount(moveArray);

	bool result = choose_engine_move(move, board, info, kings, team, depth, moveArray, moveAmount);

	free(moveArray); return result;
}

bool choose_engine_move(Move* move, const Piece board[], Info info, Kings kings, unsigned short team, short depth, const Move moveArray[], short moveAmount)
{
	if(moveAmount <= 0) return false;


	totalNodes = 0;
	totalPassant = 0;
	totalCastles = 0;
	totalPromote = 0;


	Move bestMove = moveArray[0];
	signed short bestValue = team_weight_value(MIN_STATE_VALUE, team);

	for(unsigned short index = 0; index < moveAmount; index += 1)
	{
		Move currentMove = moveArray[index];

		short currentValue;
		if(!chess_move_value(&currentValue, board, info, kings, team, (depth - 1), MIN_STATE_VALUE, MAX_STATE_VALUE, currentMove)) continue;

		printf("CurrentMove: [%d -> %d]\tCurrentValue: %d\n", MOVE_START_MACRO(currentMove), MOVE_STOP_MACRO(currentMove), currentValue);

		if((team == TEAM_WHITE && currentValue > bestValue) ||
			(team == TEAM_BLACK && currentValue < bestValue))
		{
			bestMove = currentMove; bestValue = currentValue;
		}
	}
	printf("Nodes=%ld Passant=%ld Castles=%ld Promote=%ld\n", totalNodes, totalPassant, totalCastles, totalPromote);

	*move = bestMove; return true;
}

unsigned short board_depth_value(const Piece board[], Info info, Kings kings, unsigned short currentTeam, short depth, signed short alpha, signed short beta)
{
	if(depth <= 0) return board_state_value(board, info, kings);

	Move* moveArray;
	if(!team_legal_moves(&moveArray, board, info, kings, currentTeam))
		return board_state_value(board, info, kings);

	unsigned short moveAmount = move_array_amount(moveArray);

	signed short bestValue = choose_move_value(board, info, kings, currentTeam, depth, alpha, beta, moveArray, moveAmount);

	free(moveArray); return bestValue;
}

signed short choose_move_value(const Piece board[], Info info, Kings kings, unsigned short currentTeam, short depth, signed short alpha, signed short beta, const Move moveArray[], short moveAmount)
{
	if(moveAmount <= 0) return board_state_value(board, info, kings);

	signed short bestValue = team_weight_value(MIN_STATE_VALUE, currentTeam);

	for(unsigned short index = 0; index < moveAmount; index += 1)
	{
		Move currentMove = moveArray[index];

		short currentValue;
		if(!chess_move_value(&currentValue, board, info, kings, currentTeam, (depth - 1), alpha, beta, currentMove)) continue;

		update_best_value(currentValue, &bestValue, currentTeam);

		update_alpha_beta(currentValue, &alpha, &beta, currentTeam);

		// if(beta <= alpha) break;
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
