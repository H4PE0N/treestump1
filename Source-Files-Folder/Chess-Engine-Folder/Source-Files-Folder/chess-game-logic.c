
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
	Piece stopPiece = board[kingPoint];


	if(!correct_move_flag(&move, startPiece, info))
	{
		return false;
	}


	// This function checks:
	// - if the moving pattern and flag matches the piece
	if(!move_pattern_valid(move, startPiece)) return false;

	// This function checks:
	// - if the move can be done, if it has the ability (castling)
	if(!move_ability_valid(move, startPiece, info)) return false;

	// This function checks:
	// - if the move pattern fits on the board and iteracts with the pieces that it needs
	if(!move_pattern_fits(board, info, move)) return false;

	// This function checks:
	// - if the path between the start point and the stop point is clear
	if(!clear_moving_path(board, move, startPiece)) return false;


	printf("\npiece_does_check: (%d-%d) -> (%d-%d)",
		POINT_RANK_MACRO(MOVE_START_MACRO(move)),
		POINT_FILE_MACRO(MOVE_START_MACRO(move)),
		POINT_RANK_MACRO(MOVE_STOP_MACRO(move)),
		POINT_FILE_MACRO(MOVE_STOP_MACRO(move)));

	printf("[%d %d] [%d %d]\n", PIECE_TEAM_MACRO(startPiece), PIECE_TYPE_MACRO(startPiece), PIECE_TEAM_MACRO(stopPiece), PIECE_TYPE_MACRO(stopPiece));

	return true;
}

bool game_still_running(const Piece board[], Info info, Kings kings)
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
