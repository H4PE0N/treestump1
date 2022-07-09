
#include "../Header-Files-Folder/engine-include-file.h"

long search_depth_nodes(const Piece board[], Info info, unsigned short currentTeam, short depth, long startClock, short seconds)
{
	if(depth <= 0) return 1;

	if(timing_limit_ended(startClock, seconds)) return 1;

	Move* moveArray;
	if(!team_legal_moves(&moveArray, board, info, currentTeam)) return 1;

	unsigned short moveAmount = move_array_amount(moveArray);

	long localNodes = 0;

	for(unsigned short index = 0; index < moveAmount; index += 1)
	{
		Move currentMove = moveArray[index];

		localNodes += search_move_nodes(board, info, currentTeam, (depth - 1), currentMove, startClock, seconds);
	}
	free(moveArray); return localNodes;
}

long search_move_nodes(const Piece board[], Info info, unsigned short currentTeam, short depth, Move move, long startClock, short seconds)
{
	Info infoCopy = info;
	infoCopy = ALLOC_INFO_TEAM(infoCopy, TEAM_INFO_MACRO(currentTeam));

	Piece* boardCopy = copy_chess_board(board);

	if(!move_chess_piece(boardCopy, &infoCopy, move))
	{ free(boardCopy); return 1; }

	unsigned short nextTeam = normal_team_enemy(currentTeam);

	long moveNodes = search_depth_nodes(boardCopy, infoCopy, nextTeam, depth, startClock, seconds);

	free(boardCopy); return moveNodes;
}

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

bool guess_order_moves(Move* moveArray, short moveAmount, const Piece board[], Info info)
{
	if(moveAmount <= 0) return false;

	signed short* moveValues = NULL;
	if(!guess_moves_values(&moveValues, moveArray, moveAmount, board, info)) return false;

	unsigned short team = move_start_team(moveArray[0], board);

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

	Piece startPieceType = start_piece_type(move, board);
	Piece stopPieceType = stop_piece_type(move, board);

	unsigned short startTeam = move_start_team(move, board);

	if(stopPieceType != PIECE_TYPE_NONE)
	{
		signed short stopPieceValue = PIECE_TYPE_VALUES[stopPieceType];
		signed short startPieceValue = PIECE_TYPE_VALUES[startPieceType];

		moveScore = 10 * stopPieceValue - startPieceValue;
	}

	if(MOVE_PROMOTE_FLAG(move)) moveScore += move_promote_piece(move);

	return team_weight_value(moveScore, startTeam);
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

bool chess_move_value(signed short* moveValue, const Piece board[], Info info, unsigned short currentTeam, short depth, signed short alpha, signed short beta, Move move)
{
	Info infoCopy = info;
	infoCopy = ALLOC_INFO_TEAM(infoCopy, TEAM_INFO_MACRO(currentTeam));

	Piece* boardCopy = copy_chess_board(board);

	bool result = simulate_move_value(moveValue, boardCopy, infoCopy, currentTeam, depth, alpha, beta, move);

	free(boardCopy); return result;
}

bool simulate_move_value(signed short* moveValue, Piece* boardCopy, Info infoCopy, unsigned short currentTeam, short depth, signed short alpha, signed short beta, Move move)
{
	if(!move_chess_piece(boardCopy, &infoCopy, move)) return false;

	unsigned short nextTeam = normal_team_enemy(currentTeam);

	*moveValue = board_depth_value(boardCopy, infoCopy, nextTeam, depth, alpha, beta);

	return true;
}

bool optimal_depth_move(Move* move, const Piece board[], Info info, unsigned short team, short seconds)
{
	Move* moveArray;
	if(!team_legal_moves(&moveArray, board, info, team)) return false;

	unsigned short moveAmount = move_array_amount(moveArray);

	bool result = search_depths_move(move, board, info, team, seconds, moveArray, moveAmount);

	free(moveArray); return result;
}

bool search_depths_move(Move* move, const Piece board[], Info info, unsigned short team, short seconds, const Move moveArray[], short moveAmount)
{
	if(moveAmount <= 0) return false;
	if(moveAmount == 1) { *move = moveArray[0]; return true; }

	long startClock = clock();

	Move engineMove = moveArray[0]; signed short engineValue = 0;

	for(unsigned short depth = 1;; depth += 1)
	{
		if(!choose_timing_move(&engineMove, &engineValue, board, info, team, depth, startClock, seconds, moveArray, moveAmount)) return false;

		if(timing_limit_ended(startClock, seconds)) break;

		printf("Depth: %d Time: %.2f Move: %d -> %d\n", depth, time_passed_since(startClock), MOVE_START_MACRO(engineMove), MOVE_STOP_MACRO(engineMove));

		if(current_mate_value(engineValue, team)) break;
	}
	*move = engineMove; return true;
}

bool choose_timing_move(Move* move, signed short* value, const Piece board[], Info info, unsigned short team, short depth, long startClock, short seconds, const Move moveArray[], short moveAmount)
{
	if(moveAmount <= 0) return false;

	Move bestMove = moveArray[0];
	signed short bestValue = team_weight_value(MIN_STATE_VALUE, team);

	for(unsigned short index = 0; index < moveAmount; index += 1)
	{
		if(timing_limit_ended(startClock, seconds)) return true;

		Move currentMove = moveArray[index];

		short currentValue;
		if(!chess_move_value(&currentValue, board, info, team, (depth - 1), MIN_STATE_VALUE, MAX_STATE_VALUE, currentMove)) continue;

		if(update_mate_value(currentMove, currentValue, &bestMove, &bestValue, team)) break;

		update_move_value(currentMove, currentValue, &bestMove, &bestValue, team);
	}
	*move = bestMove; *value = bestValue; return true;
}

double time_passed_since(long startClock)
{
	return (double) (clock() - startClock) / CLOCKS_PER_SEC;
}

bool timing_limit_ended(long startClock, short seconds)
{
	return (time_passed_since(startClock) >= seconds);
}

bool current_mate_value(signed short currentValue, unsigned short team)
{
	if(team == TEAM_WHITE && currentValue > team_weight_value(MATE_VALUE, team)) return true;
	if(team == TEAM_BLACK && currentValue < team_weight_value(MATE_VALUE, team)) return true;

	return false;
}

bool update_mate_value(Move currentMove, signed short currentValue, Move* bestMove, signed short* bestValue, unsigned short team)
{
	if(!current_mate_value(currentValue, team)) return false;

	*bestMove = currentMove; *bestValue = currentValue; return true;
}

bool ordered_legal_moves(Move** moveArray, const Piece board[], Info info, unsigned short team)
{
	if(!team_legal_moves(moveArray, board, info, team)) return false;

	unsigned short moveAmount = move_array_amount(*moveArray);

	return guess_order_moves(*moveArray, moveAmount, board, info);
}

bool engine_depth_move(Move* move, const Piece board[], Info info, unsigned short team, signed short depth)
{
	if(depth <= 0 || !normal_team_exists(team)) return false;

	Move* moveArray;
	if(!team_legal_moves(&moveArray, board, info, team)) return false;

	unsigned short moveAmount = move_array_amount(moveArray);

	bool result = choose_engine_move(move, board, info, team, depth, moveArray, moveAmount);

	free(moveArray); return result;
}

bool choose_engine_move(Move* move, const Piece board[], Info info, unsigned short team, short depth, const Move moveArray[], short moveAmount)
{
	if(moveAmount <= 0) return false;
	if(moveAmount == 1) { *move = moveArray[0]; return true; }

	Move bestMove = moveArray[0];
	signed short bestValue = team_weight_value(MIN_STATE_VALUE, team);

	for(unsigned short index = 0; index < moveAmount; index += 1)
	{
		Move currentMove = moveArray[index];

		short currentValue;
		if(!chess_move_value(&currentValue, board, info, team, (depth - 1), MIN_STATE_VALUE, MAX_STATE_VALUE, currentMove)) continue;

		printf("CurrentMove: [%d -> %d]\tCurrentValue: %d\n", MOVE_START_MACRO(currentMove), MOVE_STOP_MACRO(currentMove), currentValue);

		update_move_value(currentMove, currentValue, &bestMove, &bestValue, team);
	}
	*move = bestMove; return true;
}

signed short board_depth_value(const Piece board[], Info info, unsigned short currentTeam, short depth, signed short alpha, signed short beta)
{
	if(depth <= 0) return board_state_value(board, info);

	Move* moveArray;
	if(!ordered_legal_moves(&moveArray, board, info, currentTeam))
		return board_state_value(board, info);

	unsigned short moveAmount = move_array_amount(moveArray);

	signed short bestValue = choose_move_value(board, info, currentTeam, depth, alpha, beta, moveArray, moveAmount);

	free(moveArray); return bestValue;
}

signed short choose_move_value(const Piece board[], Info info, unsigned short currentTeam, short depth, signed short alpha, signed short beta, const Move moveArray[], short moveAmount)
{
	if(moveAmount <= 0) return board_state_value(board, info);

	signed short bestValue = team_weight_value(MIN_STATE_VALUE, currentTeam);

	for(unsigned short index = 0; index < moveAmount; index += 1)
	{
		Move currentMove = moveArray[index];

		short currentValue;
		if(!chess_move_value(&currentValue, board, info, currentTeam, (depth - 1), alpha, beta, currentMove)) continue;

		update_best_value(currentValue, &bestValue, currentTeam);

		update_alpha_beta(currentValue, &alpha, &beta, currentTeam);

		if(beta <= alpha) break;
	}
	return bestValue;
}

void update_move_value(Move currentMove, signed short currentValue, Move* bestMove, signed short* bestValue, unsigned short team)
{
	if((team == TEAM_WHITE && currentValue > *bestValue) ||
		 (team == TEAM_BLACK && currentValue < *bestValue))
	{ *bestMove = currentMove; *bestValue = currentValue; }
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
