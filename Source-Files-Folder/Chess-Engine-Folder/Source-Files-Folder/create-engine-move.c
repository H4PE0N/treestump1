
#include "../Header-Files-Folder/engine-include-file.h"

bool engine_depth_move(Move* move, const Piece board[], Info info, unsigned short team, signed short depth)
{
	if((depth <= 0) || !normal_team_exists(team)) return false;

	Move* moveArray;
	if(!team_legal_moves(&moveArray, board, info, team)) return false;

	unsigned short moveAmount = move_array_amount(moveArray);

	bool result = choose_engine_move(move, board, info, team, depth, moveArray, moveAmount);

	free(moveArray); return result;
}

bool chess_move_value(signed short* moveValue, const Piece board[], Info info, unsigned short currentTeam, short depth, signed short alpha, signed short beta, Move move)
{
	Info infoCopy = ALLOC_TEAM_INFO(info, currentTeam);

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

		char moveString[16];
		create_string_move(moveString, currentMove);

		printf("info depth %d time %d move %s value %d\n", depth, 0, moveString, currentValue);

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

bool current_mate_value(signed short currentValue, unsigned short team)
{
	signed short mateValue = team_weight_value(MATE_VALUE, team);

	if((team == TEAM_WHITE) && (currentValue > mateValue)) return true;
	if((team == TEAM_BLACK) && (currentValue < mateValue)) return true;

	return false;
}

bool update_mate_value(Move currentMove, signed short currentValue, Move* bestMove, signed short* bestValue, unsigned short team)
{
	if(!current_mate_value(currentValue, team)) return false;

	*bestMove = currentMove; *bestValue = currentValue; return true;
}

void update_move_value(Move currentMove, signed short currentValue, Move* bestMove, signed short* bestValue, unsigned short team)
{
	if(!((team == TEAM_WHITE) && (currentValue > *bestValue)) &&
		!((team == TEAM_BLACK) && (currentValue < *bestValue))) return;

	*bestMove = currentMove; *bestValue = currentValue;
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
