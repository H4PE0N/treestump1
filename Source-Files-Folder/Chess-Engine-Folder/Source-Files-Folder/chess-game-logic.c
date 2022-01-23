
#include "../Header-Files-Folder/engine-include-file.h"

bool king_inside_check(const Piece board[], Info info, Point kingPoint)
{
	for(Point point = 0; point < BOARD_LENGTH; point += 1)
	{
		if(piece_does_check(board, info, kingPoint, point)) return true;
	}
	return false;
}

bool piece_does_check(const Piece board[], Info info, Point kingPoint, Point point)
{
	Move move = (START_MOVE_MACRO(point) | STOP_MOVE_MACRO(kingPoint));

	Piece piece = board[point];


	if(!correct_move_flag(&move, piece, info)) return false;

	if(!move_pseudo_legal(board, info, move)) return false;

	return true;
}

bool game_still_running(const Piece board[], Info info, Kings kings)
{
	unsigned short currentTeam = INFO_TEAM_MACRO(info);

	if(check_mate_ending(board, info, kings, currentTeam)) return false;

	if(check_draw_ending(board, info, kings, currentTeam)) return false;

	return true;
}

bool check_mate_ending(const Piece board[], Info info, Kings kings, unsigned short team)
{
	Point kingPoint = POINT_NONE;

	if(team == TEAM_WHITE) kingPoint = KINGS_WHITE_MACRO(kings);

	else if(team == TEAM_BLACK) kingPoint = KINGS_BLACK_MACRO(kings);

	else return false;


	if(!king_inside_check(board, info, kingPoint)) return false;

	if(team_pieces_movable(board, info, kings, team)) return false;

	return true;
}

bool check_draw_ending(const Piece board[], Info info, Kings kings, unsigned short team)
{
	Point kingPoint = POINT_NONE;

	if(team == TEAM_WHITE) kingPoint = KINGS_WHITE_MACRO(kings);

	else if(team == TEAM_BLACK) kingPoint = KINGS_BLACK_MACRO(kings);

	else return false;


	if(king_inside_check(board, info, kingPoint)) return false;

	if(team_pieces_movable(board, info, kings, team)) return false;

	return true;
}

bool team_pieces_movable(const Piece board[], Info info, Kings kings, unsigned short team)
{
	for(Point point = 0; point < BOARD_LENGTH; point += 1)
	{
		unsigned short currentTeam = PIECE_TEAM_MACRO(board[point]);

		if(currentTeam != team) continue;

		if(chess_piece_movable(board, info, kings, point)) return true;
	}
	return false;
}

bool chess_piece_movable(const Piece board[], Info info, Kings kings, Point piecePoint)
{
	Piece piece = board[piecePoint];

	for(Point point = 0; point < BOARD_LENGTH; point += 1)
	{
		Move move = (START_MOVE_MACRO(piecePoint) | STOP_MOVE_MACRO(point));

		if(!correct_move_flag(&move, piece, info)) continue;

		if(move_fully_legal(board, info, kings, move)) return true;
	}
	return false;
}
