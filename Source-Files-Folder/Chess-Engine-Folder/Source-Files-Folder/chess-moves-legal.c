
#include "../Header-Files-Folder/engine-include-file.h"

// This function should check:
// - the move is pseudo legal
// - the own king is not set in check
bool move_fully_legal(const Piece board[], Info info, Move move)
{
	if(!move_pseudo_legal(board, info, move))
	{
		return false;
	}

	return true;
}

// This function should check:
// - the piece is allowed to move that way
// - the move path is clear (except for the knight)
bool move_pseudo_legal(const Piece board[], Info info, Move move)
{
	if(!move_inside_board(move))
	{
		return false;
	}

	Point startPoint = MOVE_START_MACRO(move);
	Piece startPiece = board[startPoint];

	// This function checks:
	// - if the moving pattern and flag matches the piece
	if(!move_pattern_valid(move, startPiece))
	{
		return false;
	}

	// This function checks:
	// - if the move can be done, if it has the ability (castling)
	if(!move_ability_valid(move, startPiece, info))
	{

	}

	// This function checks:
	// - if the move pattern fits on the board and iteracts with the pieces that it needs
	if(!move_pattern_fits(board, info, move))
	{
		return false;
	}

	// This function checks:
	// - if the path between the start point and the stop point is clear
	if(!clear_moving_path(board, move))
	{
		return false;
	}

	return true;
}

bool clear_moving_path(const Piece board[], Move move)
{
	return true;
}

bool move_ability_valid(Move move, Piece piece, Info info)
{
	Point startPoint = MOVE_START_MACRO(move);
	Point stopPoint = MOVE_STOP_MACRO(move);

	Move moveFlag = move & MOVE_FLAG_MASK;

	if(moveFlag == MOVE_FLAG_CASTLE)
	{
		// If the move flag is saying that the move is a castle:
		// - we have to check if the ability at that side is valid

		Piece pieceTeam = piece & PIECE_TEAM_MASK;

		signed short movePattern = stopPoint - startPoint;

		Info castles = info & INFO_CASTLES_MASK;

		if(pieceTeam == PIECE_TEAM_WHITE)
		{
			if(movePattern == KING_CASTLE_PAT)
			{
				if(!(castles & INFO_WHITE_KING))
				{
					return false;
				}
			}
			else if(movePattern == QUEEN_CASTLE_PAT)
			{
				if(!(castles & INFO_WHITE_QUEEN))
				{
					return false;
				}
			}
			else
			{
				// The move pattern is not castling!
				return false;
			}
		}
		else if(pieceTeam == PIECE_TEAM_BLACK)
		{
			if(movePattern == KING_CASTLE_PAT)
			{
				if(!(castles & INFO_BLACK_KING))
				{
					return false;
				}
			}
			else if(movePattern == QUEEN_CASTLE_PAT)
			{
				if(!(castles & INFO_BLACK_QUEEN))
				{
					return false;
				}
			}
			else
			{
				// The move pattern is not castling!
				return false;
			}
		}
		else
		{
			return false;
		}
		
	}

	return true;
}

// This function is going to check if the move-pattern
// fits inside the board (pawn-takes, castling, pawn double jump)
// - the stop piece can't be of same team
// - the stop piece must be empty if the pawn moves forward
// - it must be a rook in the corner, if it is castle
bool move_pattern_fits(const Piece board[], Info info, Move move)
{
	if(!move_inside_board(move))
	{
		return false;
	}

	Point startPoint = MOVE_START_MACRO(move);
	Point stopPoint = MOVE_STOP_MACRO(move);

	Move moveFlag = move & MOVE_FLAG_MASK;



	Piece startPiece = board[startPoint];
	Piece stopPiece = board[stopPoint];



	Piece startTeam = startPiece & PIECE_TEAM_MASK;
	Piece stopTeam = stopPiece & PIECE_TEAM_MASK;

	Piece startType = startPiece & PIECE_TYPE_MASK;
	//Piece stopType = stopPiece & PIECE_TYPE_MASK;

	

	signed short moveValue = 1;

	if(startTeam == PIECE_TEAM_WHITE)
	{
		moveValue = WHITE_MOVE_VALUE;
	}
	else if(startTeam == PIECE_TEAM_BLACK)
	{
		moveValue = BLACK_MOVE_VALUE;
	}
	else
	{
		// No team
		return false;
	}

	signed short movePattern = (stopPoint - startPoint) * moveValue;



	if(moveFlag == MOVE_FLAG_CASTLE)
	{
		// This checks if the king is the one moving, and if the rook is in its place

	}

	if(startType == PIECE_TYPE_PAWN)
	{
		if(movePattern == +8 || movePattern == +16)
		{
			// Going straight

			if(stopTeam != PIECE_TEAM_NONE)
			{
				return false;
			}
		}

		else if(movePattern == +7 || movePattern == +9)
		{
			// Pawn take

			if(!board_teams_enemy(startTeam, stopTeam))
			{
				return false;
			}
		}

	}

	return true;
}