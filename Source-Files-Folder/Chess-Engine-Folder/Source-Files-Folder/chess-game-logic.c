
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

bool game_still_running(const Piece board[], Info info)
{
	return true;
}

bool check_mate_ending(const Piece board[], Info info, Point kingPoint)
{
	Piece pieceTeam = (board[kingPoint] & PIECE_TEAM_MASK);
	//Piece pieceType = (board[kingPoint] & PIECE_TYPE_MASK);

	if(!king_inside_check(board, info, kingPoint))
	{
		return false;
	}

	if(team_prevent_check(board, info, pieceTeam))
	{
		return false;
	}

	return true;
}

bool check_draw_ending(const Piece board[], Info info, Point kingPoint)
{
	Piece pieceTeam = (board[kingPoint] & PIECE_TEAM_MASK);
	//Piece pieceType = (board[kingPoint] & PIECE_TYPE_MASK);

	if(king_inside_check(board, info, kingPoint))
	{
		return false;
	}

	if(team_pieces_movable(board, info, pieceTeam))
	{
		return false;
	}

	return true;
}

bool team_pieces_movable(const Piece board[], Info info, Piece pieceTeam)
{
	return true;
}

bool team_prevent_check(const Piece board[], Info info, Piece pieceTeam)
{
	return true;
}