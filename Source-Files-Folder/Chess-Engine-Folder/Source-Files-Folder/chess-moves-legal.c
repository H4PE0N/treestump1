
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
		return false;
	}

	// This function checks:
	// - if the move pattern fits on the board and iteracts with the pieces that it needs
	if(!move_pattern_fits(board, info, move))
	{
		return false;
	}

	// This function checks:
	// - if the path between the start point and the stop point is clear
	if(!clear_moving_path(board, move, startPiece))
	{
		return false;
	}

	return true;
}

bool clear_moving_path(const Piece board[], Move move, Piece piece)
{
	//Piece pieceTeam = PIECE_TEAM_MACRO(piece);
	Piece pieceType = PIECE_TYPE_MACRO(piece);

	if(pieceType == PIECE_TYPE_KNIGHT) return true;


	Point startPoint = MOVE_START_MACRO(move);
	Point stopPoint = MOVE_STOP_MACRO(move);

	Rank startRank = POINT_RANK_MACRO(startPoint);
	File startFile = POINT_FILE_MACRO(startPoint);

	File stopFile = POINT_FILE_MACRO(stopPoint);
	Rank stopRank = POINT_RANK_MACRO(stopPoint);

	short rankOffset = (stopRank - startRank);
	short fileOffset = (stopFile - startFile);

	unsigned short absRankOffset = ABS_SHORT_NUMBER(rankOffset);
	unsigned short absFileOffset = ABS_SHORT_NUMBER(fileOffset);

	// If both rank- and file-offset is 0, then its not moving
	if(absRankOffset == 0 && absFileOffset == 0) return false;

	// Either it can go straight (one is 0), or it can go diagonal (both the same)

	if( (absRankOffset != 0 && absFileOffset != 0) && absRankOffset != absFileOffset) return false;

	unsigned short moveSteps = (absRankOffset > absFileOffset) ? absRankOffset : absFileOffset;


	short rankFactor = (absRankOffset == 0) ? 0 : (rankOffset / absRankOffset);
	short fileFactor = (absFileOffset == 0) ? 0 : (fileOffset / absFileOffset);


	for(unsigned short index = 1; index < moveSteps; index = index + 1)
	{
		File currentFile = startFile + (index * fileFactor);
		Rank currentRank = startRank + (index * rankFactor);

		Point point = (currentFile << POINT_FILE_SHIFT) | (currentRank << POINT_RANK_SHIFT);

		Piece currentTeam = (board[point] & PIECE_TEAM_MASK);
		Piece currentType = (board[point] & PIECE_TYPE_MASK);

		if(currentType != PIECE_TYPE_NONE || currentTeam != PIECE_TEAM_NONE) return false;
	}

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

		Piece pieceTeam = (piece & PIECE_TEAM_MASK);

		signed short movePattern = (stopPoint - startPoint);

		Info castles = (info & INFO_CASTLES_MASK);


		if(pieceTeam == PIECE_TEAM_WHITE)
		{
			if(movePattern == KING_CASTLE_PAT)
			{
				if(!(castles & INFO_WHITE_KING)) return false;
			}
			else if(movePattern == QUEEN_CASTLE_PAT)
			{
				if(!(castles & INFO_WHITE_QUEEN)) return false;
			}
			else return false;
		}
		else if(pieceTeam == PIECE_TEAM_BLACK)
		{
			if(movePattern == KING_CASTLE_PAT)
			{
				if(!(castles & INFO_BLACK_KING)) return false;
			}
			else if(movePattern == QUEEN_CASTLE_PAT)
			{
				if(!(castles & INFO_BLACK_QUEEN)) return false;
			}
			else return false;
		}
		else return false;
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
	Point startPoint = MOVE_START_MACRO(move);
	Point stopPoint = MOVE_STOP_MACRO(move);
	
	Piece startTeam = (board[startPoint] & PIECE_TEAM_MASK);
	Piece startType = (board[startPoint] & PIECE_TYPE_MASK);

	Piece stopTeam = (board[stopPoint] & PIECE_TEAM_MASK);

	
	short fileOffset = move_file_offset(move, startTeam);
	short rankOffset = move_rank_offset(move, startTeam);


	Move moveFlag = (move & MOVE_FLAG_MASK);


	if(board_teams_team(startTeam, stopTeam)) return false;

	if(moveFlag == MOVE_FLAG_CASTLE)
	{
		// This checks if the king is the one moving, and if the rook is in its place

	}

	if(startType == PIECE_TYPE_PAWN)
	{
		if(fileOffset == 0 && (rankOffset == 1 || rankOffset == 2))
		{
			if(!chess_piece_empty(board[stopPoint])) return false;
		}

		else if(fileOffset == 1 && rankOffset == 1)
		{
			if(!board_teams_enemy(startTeam, stopTeam)) return false;
		}

	}

	return true;
}

// This function should give the move its correct flag
// To do that, it checks for patterns, but the move don't have to be legal,
// this function just sets the flag that it would have had to have.
bool correct_move_flag(Move* move, Piece piece, Info info)
{
	Piece pieceTeam = (piece & PIECE_TEAM_MASK);
	Piece pieceType = (piece & PIECE_TYPE_MASK);

	Point stopPoint = MOVE_STOP_MACRO(*move);

	File stopFile = POINT_FILE_MACRO(stopPoint);
	Rank stopRank = POINT_RANK_MACRO(stopPoint);

	short fileOffset = ABS_SHORT_NUMBER(move_file_offset(*move, pieceTeam));
	short rankOffset = ABS_SHORT_NUMBER(move_rank_offset(*move, pieceTeam));

	Passant passantFile = INFO_PASSANT_MACRO(info);

	Move moveFlag = MOVE_FLAG_NONE;

	if(pieceType == PIECE_TYPE_PAWN && rankOffset == 2 && fileOffset == 0)
	{
		moveFlag = MOVE_FLAG_DOUBLE;
	}
	else if(pieceType == PIECE_TYPE_KING && rankOffset == 0 && fileOffset == 2)
	{
		moveFlag = MOVE_FLAG_CASTLE;
	}
	else if((pieceType == PIECE_TYPE_PAWN) && ((stopFile + 1) == passantFile) &&
		((pieceTeam == PIECE_TEAM_WHITE && stopRank == BLACK_PAWN_RANK + BLACK_MOVE_VALUE) ||
		(pieceTeam == PIECE_TEAM_BLACK && stopRank == WHITE_PAWN_RANK + WHITE_MOVE_VALUE)))
	{
		moveFlag = MOVE_FLAG_PASSANT;
	}
	else if((pieceType == PIECE_TYPE_PAWN) &&
		((pieceTeam == PIECE_TEAM_WHITE && stopRank == BLACK_START_RANK) ||
		(pieceTeam == PIECE_TEAM_BLACK && stopRank == WHITE_START_RANK)))
	{
		moveFlag = MOVE_FLAG_QUEEN;
	}

	*move |= (moveFlag & MOVE_FLAG_MASK);

	return true;
}