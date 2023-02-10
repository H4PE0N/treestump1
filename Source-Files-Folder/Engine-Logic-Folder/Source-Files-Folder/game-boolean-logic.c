
#include "../Header-Files-Folder/englog-include-file.h"

bool king_inside_check(const Piece board[], Point kingPoint)
{
	if(!POINT_INSIDE_BOARD(kingPoint)) return false;

	uint8_t kingTeam = BOARD_POINT_TEAM(board, kingPoint);

	for(Point point = 0; point < BOARD_POINTS; point += 1)
	{
		uint8_t currentTeam = BOARD_POINT_TEAM(board, point);
		if(!NORMAL_TEAMS_ENEMY(currentTeam, kingTeam)) continue;

		if(piece_does_check(board, kingPoint, point)) return true;
	}
	return false;
}

bool piece_does_check(const Piece board[], Point kingPoint, Point point)
{
	if(!POINTS_INSIDE_BOARD(point, kingPoint)) return false;

	if(!BOARD_POINTS_ENEMY(board, kingPoint, point)) return false;

	Move move = START_STOP_MOVE(point, kingPoint);

	return board_move_legal(board, move);
}

bool game_still_running(const Piece board[], State state)
{
	uint8_t currentTeam = STATE_CURRENT_MACRO(state);

	if(check_mate_ending(board, state, currentTeam)) return false;

	if(check_draw_ending(board, state, currentTeam)) return false;

	return true;
}

bool check_mate_ending(const Piece board[], State state, uint8_t team)
{
	if(!NORMAL_TEAM_EXISTS(team)) return false;

	Point kingPoint = board_king_point(board, team);
	if(kingPoint == POINT_NONE) return false;

	if(!king_inside_check(board, kingPoint)) return false;

	if(team_pieces_movable(board, state, team)) return false;

	return true;
}

bool check_draw_ending(const Piece board[], State state, uint8_t team)
{
	if(!NORMAL_TEAM_EXISTS(team)) return false;

	if(STATE_CLOCK_MACRO(state) >= 100) return true;

	if(little_material_draw(board)) return true;

	Point kingPoint = board_king_point(board, team);
	if(kingPoint == POINT_NONE) return false;

	if(king_inside_check(board, kingPoint)) return false;

	if(team_pieces_movable(board, state, team)) return false;

	return true;
}
/*
if(knightAmount >= 2) return false;

if((knightAmount >= 1) && (blackBishops || whiteBishops)) return false;

if(blackBishops && whiteBishops) return false;

return true;
*/
bool little_material_draw(const Piece board[])
{
	uint8_t blackBishops = 0, whiteBishops = 0, knightAmount = 0;

	for(Point point = 0; point < BOARD_POINTS; point += 1)
	{
		if(!CHESS_PIECE_EXISTS(board[point])) continue;

		uint8_t type = PIECE_TYPE_MACRO(board[point]);

		if((type == TYPE_ROOK) || (type == TYPE_PAWN) || (type == TYPE_QUEEN)) return false;

		if((type != TYPE_KNIGHT) && (type != TYPE_BISHOP)) continue;


		if(type == TYPE_KNIGHT) knightAmount += 1;

		else if(POINT_SQAURE_WHITE(point)) whiteBishops += 1;

		else blackBishops += 1;


		if(knightAmount >= 2) return false;

		if((knightAmount >= 1) && (blackBishops || whiteBishops)) return false;

		if(blackBishops && whiteBishops) return false;
	}
	return true;
}

bool team_pieces_movable(const Piece board[], State state, uint8_t team)
{
	if(!NORMAL_TEAM_EXISTS(team)) return false;

	for(Point point = 0; point < BOARD_POINTS; point += 1)
	{
		uint8_t currentTeam = BOARD_POINT_TEAM(board, point);

		if(!NORMAL_TEAMS_TEAM(currentTeam, team)) continue;

		if(chess_piece_movable(board, state, point)) return true;
	}
	return false;
}

bool chess_piece_movable(const Piece board[], State state, Point piecePoint)
{
	if(!POINT_INSIDE_BOARD(piecePoint)) return false;

	Move* moveArray; int moveAmount;
	if(!piece_pattern_moves(&moveArray, &moveAmount, board, piecePoint)) return false;

	bool result = piece_movable_test(board, state, moveArray, moveAmount);

	free(moveArray); return result;
}

bool piece_movable_test(const Piece board[], State state, const Move moveArray[], int moveAmount)
{
	for(int index = 0; index < moveAmount; index += 1)
	{
		Move move = moveArray[index];

		if(!correct_move_flag(&move, board, state)) continue;

		if(move_fully_legal(board, state, move)) return true;
	}
	return false;
}

bool move_deliver_check(const Piece board[], State state, Move move)
{
	if(!MOVE_INSIDE_BOARD(move)) return false;

	Piece* boardCopy = copy_chess_board(board);

	bool result = deliver_check_test(boardCopy, state, move);

	free(boardCopy); return result;
}

bool deliver_check_test(Piece* boardCopy, State stateCopy, Move move)
{
	uint8_t enemyTeam = MOVE_START_ENEMY(boardCopy, move);

	if(!execute_chess_move(boardCopy, &stateCopy, move)) return false;

	Point kingPoint = board_king_point(boardCopy, enemyTeam);
	if(kingPoint == POINT_NONE) return false;

	return king_inside_check(boardCopy, kingPoint);
}

bool move_deliver_mate(const Piece board[], State state, Move move)
{
	if(!MOVE_INSIDE_BOARD(move)) return false;

	Piece* boardCopy = copy_chess_board(board);

	bool result = deliver_mate_test(boardCopy, state, move);

	free(boardCopy); return result;
}

bool deliver_mate_test(Piece* boardCopy, State stateCopy, Move move)
{
	uint8_t enemyTeam = MOVE_START_ENEMY(boardCopy, move);

	if(!execute_chess_move(boardCopy, &stateCopy, move)) return false;

	return check_mate_ending(boardCopy, stateCopy, enemyTeam);
}
