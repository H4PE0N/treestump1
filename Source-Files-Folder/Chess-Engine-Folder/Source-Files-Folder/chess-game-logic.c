
#include "../Header-Files-Folder/engine-include-file.h"

bool king_inside_check(const Piece board[], Info info, Point kingPoint) // point of king?
{
	for(Point point = 0; point < BOARD_LENGTH; point += 1)
	{
		if(piece_does_check(board, info, kingPoint, point))
		{
			return true;
		}
	}
	return false;
}

bool piece_does_check(const Piece board[], Info info, Point kingPoint, Point startPoint) // point of king?
{
	Move move = START_MOVE_MACRO(startPoint) | STOP_MOVE_MACRO(kingPoint);

	Piece startPiece = board[startPoint];


	if(!correct_move_flag(&move, startPiece, info))
	{
		return false;
	}


	if(!move_pseudo_legal(board, info, move))
	{
		return false;
	}


	return true;
}

bool game_still_running(const Piece board[], Info info, Kings kings)
{
	unsigned short currentTeam = INFO_TEAM_MACRO(info);

	if(check_mate_ending(board, info, kings, TEAM_PIECE_MACRO(currentTeam) )) return false;

	if(check_draw_ending(board, info, kings, TEAM_PIECE_MACRO(currentTeam))) return false;

	return true;
}

bool check_mate_ending(const Piece board[], Info info, Kings kings, Piece pieceTeam)
{
	Point kingPoint = POINT_NONE;

	if(pieceTeam == PIECE_TEAM_WHITE) kingPoint = KINGS_WHITE_MACRO(kings);

	else if(pieceTeam == PIECE_TEAM_BLACK) kingPoint = KINGS_BLACK_MACRO(kings);

	else return false;


	if(!king_inside_check(board, info, kingPoint))
	{
		return false;
	}

	if(team_pieces_movable(board, info, kings, pieceTeam))
	{
		printf("team_pieces_movable\n\n");
		return false;
	}

	printf("Mate for: %d\n", pieceTeam);

	return true;
}

bool check_draw_ending(const Piece board[], Info info, Kings kings, Piece pieceTeam)
{
	Point kingPoint = POINT_NONE;

	if(pieceTeam == PIECE_TEAM_WHITE) kingPoint = KINGS_WHITE_MACRO(kings);

	else if(pieceTeam == PIECE_TEAM_BLACK) kingPoint = KINGS_BLACK_MACRO(kings);

	else return false;

	if(king_inside_check(board, info, kingPoint))
	{
		return false;
	}

	if(team_pieces_movable(board, info, kings, pieceTeam))
	{
		return false;
	}

	printf("Draw for: %d\n", pieceTeam);

	return true;
}

bool team_pieces_movable(const Piece board[], Info info, Kings kings, Piece pieceTeam)
{
	for(Point point = 0; point < BOARD_LENGTH; point += 1)
	{
		Piece currentTeam = (board[point] & PIECE_TEAM_MASK);

		if(currentTeam != pieceTeam) continue;

		if(chess_piece_movable(board, info, kings, point))
		{
			return true;
		}
	}
	return false;
}

bool chess_piece_movable(const Piece board[], Info info, Kings kings, Point piecePoint)
{
	for(Point point = 0; point < BOARD_LENGTH; point += 1)
	{
		Move move = START_MOVE_MACRO(piecePoint) | STOP_MOVE_MACRO(point);

		Piece currentPiece = board[point];

		if(!correct_move_flag(&move, currentPiece, info))
		{
			continue;
		}

		if(move_fully_legal(board, info, kings, move)) return true;
	}
	return false;
}
