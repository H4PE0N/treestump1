
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

	if(!move_pattern_valid(move, startPiece))
	{
		return false;
	}

	if(!move_pattern_fits(board, info, move))
	{
		return false;
	}

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

// This function is going to check if the move-pattern
// fits inside the board (pawn-takes, castling, pawn double jump)
bool move_pattern_fits(const Piece board[], Info info, Move move)
{
	if(!move_inside_board(move))
	{
		return false;
	}

	Point startPoint = MOVE_START_MACRO(move);
	Point stopPoint = MOVE_STOP_MACRO(move);

	Piece startPiece = board[startPoint];
	Piece stopPiece = board[stopPoint];

	Piece startTeam = startPiece & PIECE_TEAM_MASK;
	Piece stopTeam = stopPiece & PIECE_TEAM_MASK;

	Piece startType = startPiece & PIECE_TYPE_MASK;


	signed short moveValue = 1;

	if(startTeam == PIECE_TEAM_WHITE)
	{
		moveValue = WHITE_MOVE_VALUE;
	}
	else if(startTeam == PIECE_TEAM_BLACK)
	{
		moveValue = BLACK_MOVE_VALUE;
	}
	else // PIECE_TEAM_NONE
	{
		return false;
	}





	if(startTeam == stopTeam)
	{
		// You cant move a piece into a piece in the same team
		return false;
	}

	if(startType == PIECE_TYPE_PAWN)
	{
		// If the piece is a pawn, we have to check for:
		// - pawn takes (they are diagonal)
		// - double jumps (they move two steps)

		if(pattern_list_valid(PAWN_TAKE_DIRS, TAKE_DIRS_AMOUNT, move, startTeam))
		{
			// If the pawn is "attacking" / "taking", we have to check if the other piece is the enemy

			if(!board_teams_enemy(startTeam, stopTeam))
			{
				// If the pieces is not enemy, the pawn should not move that way
				return false;
			}
		}
		else
		{
			// If the pawn is not "attacking" / "taking", we have to check if the other piece is the team

			if(!board_teams_team(startTeam, stopTeam))
			{
				// If the pieces is not enemy, the pawn should not move that way
				return false;
			}
		}
		
		if((PAWN_DOUBLE_DIR * moveValue) == (stopPoint - startPoint))
		{
			// If the pawn is making a double jump

			if(startTeam == PIECE_TEAM_WHITE)
			{
				if(POINT_RANK_MACRO(startPoint) != WHITE_PAWN_RANK)
				{
					return false;
				}
			}
			else if(startTeam == PIECE_TEAM_BLACK)
			{
				if(POINT_RANK_MACRO(startPoint) != BLACK_PAWN_RANK)
				{
					return false;
				}
			}
			else
			{
				// If there is no team
				return false;
			}
		}
	}

	if(startType == PIECE_TYPE_KING)
	{
		// If the piece is a king, we have to check for:
		// - castling (it moves two squares)

		if(pattern_list_valid(CATSLE_MOVE_DIRS, CASTLE_DIRS_AMOUNT, move, startTeam))
		{
			// If the king is castling, we have to check:
			// - if the king is at its starting point
			// - if the rook is standing at its starting point
			// - if it has castle ability

			if(POINT_FILE_MACRO(startPoint) != KING_START_FILE)
			{
				return false;
			}
			if(startTeam == PIECE_TEAM_WHITE)
			{
				if(POINT_RANK_MACRO(startPoint) != WHITE_START_RANK)
				{
					return false;
				}
			}
			else if(startTeam == PIECE_TEAM_BLACK)
			{
				if(POINT_RANK_MACRO(startPoint) != BLACK_START_RANK)
				{
					return false;
				}
			}
			else
			{
				// If there is no team
				return false;
			}
		}
	}

	return true;
}

// This function is going to check if the move-pattern
// can be done for the moving piece
bool move_pattern_valid(Move move, Piece piece)
{
	Piece pieceTeam = piece & PIECE_TEAM_MASK;
	Piece pieceType = piece & PIECE_TYPE_MASK;



	if(pieceType == PIECE_TYPE_PAWN)
	{
		return pattern_list_valid(PAWN_MOVE_DIRS, PAWN_DIRS_AMOUNT, move, pieceTeam);
	}
	else if(pieceType == PIECE_TYPE_KNIGHT)
	{
		return pattern_list_valid(KNIGHT_MOVE_DIRS, KNIGHT_DIRS_AMOUNT, move, pieceTeam);
	}
	else if(pieceType == PIECE_TYPE_BISHOP)
	{
		return pattern_list_valid(BISHOP_MOVE_DIRS, BISHOP_DIRS_AMOUNT, move, pieceTeam);
	}
	else if(pieceType == PIECE_TYPE_ROOK)
	{
		return pattern_list_valid(ROOK_MOVE_DIRS, ROOK_DIRS_AMOUNT, move, pieceTeam);
	}
	else if(pieceType == PIECE_TYPE_QUEEN)
	{
		return pattern_list_valid(QUEEN_MOVE_DIRS, QUEEN_DIRS_AMOUNT, move, pieceTeam);
	}
	else if(pieceType == PIECE_TYPE_KING)
	{
		return pattern_list_valid(KING_MOVE_DIRS, KING_DIRS_AMOUNT, move, pieceTeam);
	}
	else
	{
		return false;
	}
}

bool pattern_list_valid(const signed short patternList[], unsigned short length, Move move, Piece pieceTeam)
{
	Point startPoint = MOVE_START_MACRO(move);
	Point stopPoint = MOVE_STOP_MACRO(move);

	signed short movePattern = stopPoint - startPoint;



	signed short moveValue = 1;

	if(pieceTeam == PIECE_TEAM_WHITE)
	{
		moveValue = WHITE_MOVE_VALUE;
	}
	else if(pieceTeam == PIECE_TEAM_BLACK)
	{
		moveValue = BLACK_MOVE_VALUE;
	}
	else // PIECE_TEAM_NONE
	{
		return false;
	}



	for(unsigned short index = 0; index < length; index += 1)
	{
		signed short pattern = patternList[index];

		if((pattern * moveValue) != movePattern) continue;


		// This checks if the pattern can 
		
		printf("The piece could move: %d\n", movePattern);

		return true;
	}

	printf("The piece could not move: %d\n", movePattern);

	return false;
}