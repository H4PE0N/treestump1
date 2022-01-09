
#include "../Header-Files-Folder/engine-include-file.h"

// This function checks:
// - if the moving pattern and flag matches the piece
bool move_pattern_valid(Move move, Piece piece)
{
	Piece pieceType = piece & PIECE_TYPE_MASK;
	Piece pieceTeam = piece & PIECE_TEAM_MASK;

	if(pieceType == PIECE_TYPE_NONE)
	{
		return false;
	}
	else if(pieceType == PIECE_TYPE_PAWN)
	{
		return pawn_pattern_valid(move, pieceTeam);
	}
	else if(pieceType == PIECE_TYPE_KNIGHT)
	{
		return knight_pattern_valid(move, pieceTeam);
	}
	else if(pieceType == PIECE_TYPE_BISHOP)
	{
		return bishop_pattern_valid(move, pieceTeam);
	}
	else if(pieceType == PIECE_TYPE_ROOK)
	{
		return rook_pattern_valid(move, pieceTeam);
	}
	else if(pieceType == PIECE_TYPE_QUEEN)
	{
		return queen_pattern_valid(move, pieceTeam);
	}
	else if(pieceType == PIECE_TYPE_KING)
	{
		return king_pattern_valid(move, pieceTeam);
	}
	else
	{
		return false;
	}
}

// The move pattern of a pawn should include:
// - it moving one step forward
// - it taking pieces one step diagonal
// - double jumping to steps from its starting rank
// - moving flags: [NONE, QUEEN, ROOK, BISHOP, KNIGHT, DOUBLE, PASSANT]
bool pawn_pattern_valid(Move move, Piece pieceTeam)
{
	Point startPoint = MOVE_START_MACRO(move);
	Point stopPoint = MOVE_STOP_MACRO(move);

	File startFile = POINT_FILE_MACRO(startPoint);
	Rank startRank = POINT_RANK_MACRO(startPoint);

	File stopFile = POINT_FILE_MACRO(stopPoint);
	Rank stopRank = POINT_RANK_MACRO(stopPoint);

	unsigned short fileOffset = positive_short_value(stopFile - startFile);
	unsigned short rankOffset = positive_short_value(stopRank - startRank);

	File pawnRank;

	if(!team_pawn_rank(&pawnRank, pieceTeam))
	{
		return false;
	}



	Move moveFlag = move & MOVE_FLAG_MASK;

	if(moveFlag == MOVE_FLAG_DOUBLE)
	{
		// If it moves double, it has to be at start rank

		if(startRank != pawnRank)
		{
			return false;
		}

		if(fileOffset != 0 || rankOffset != 2)
		{
			return false;
		}

		return true;
	}

	if(moveFlag != MOVE_FLAG_NONE && moveFlag != MOVE_FLAG_PASSANT)
	{
		// The pawn can only have the move flags: NONE, QUEEN, ROOK, BISHOP, KNIGHT, DOUBLE, PASSANT
		return false;
	}

	if(fileOffset == 1 && rankOffset == 1)
	{
		return true;
	}

	if(fileOffset == 0 && rankOffset == 1)
	{
		return true;
	}

	return false;
}

// The move pattern of a knight should include:
// - it only moving in small L:s
// - moving flags: [NONE, PASSANT]
bool knight_pattern_valid(Move move, Piece pieceTeam)
{
	Point startPoint = MOVE_START_MACRO(move);
	Point stopPoint = MOVE_STOP_MACRO(move);

	File startFile = POINT_FILE_MACRO(startPoint);
	Rank startRank = POINT_RANK_MACRO(startPoint);

	File stopFile = POINT_FILE_MACRO(stopPoint);
	Rank stopRank = POINT_RANK_MACRO(stopPoint);

	unsigned short fileOffset = positive_short_value(stopFile - startFile);
	unsigned short rankOffset = positive_short_value(stopRank - startRank);

	Move moveFlag = move & MOVE_FLAG_MASK;

	if(moveFlag != MOVE_FLAG_NONE && moveFlag != MOVE_FLAG_PASSANT)
	{
		// The bishop can only have the move flags: NONE, PASSANT
		return false;
	}

	if(fileOffset == 1 && rankOffset == 2)
	{
		return true;
	}

	if(fileOffset == 2 && rankOffset == 1)
	{
		return true;
	}

	return false;
}

// The move pattern of a bishop should include:
// - it only moving diagonal, for how far it wants
// - moving flags: [NONE, PASSANT]
bool bishop_pattern_valid(Move move, Piece pieceTeam)
{
	Point startPoint = MOVE_START_MACRO(move);
	Point stopPoint = MOVE_STOP_MACRO(move);

	File startFile = POINT_FILE_MACRO(startPoint);
	Rank startRank = POINT_RANK_MACRO(startPoint);

	File stopFile = POINT_FILE_MACRO(stopPoint);
	Rank stopRank = POINT_RANK_MACRO(stopPoint);

	unsigned short fileOffset = positive_short_value(stopFile - startFile);
	unsigned short rankOffset = positive_short_value(stopRank - startRank);

	Move moveFlag = move & MOVE_FLAG_MASK;

	if(moveFlag != MOVE_FLAG_NONE && moveFlag != MOVE_FLAG_PASSANT)
	{
		// The bishop can only have the move flags: NONE, PASSANT
		return false;
	}

	// It goes diagonal
	if(fileOffset == rankOffset)
	{
		return true;
	}

	return false;
}

// The move pattern of a rook should include:
// - it only moving straight, for how far it wants
// - moving flags: [PASSANT, NONE]
bool rook_pattern_valid(Move move, Piece pieceTeam)
{
	Point startPoint = MOVE_START_MACRO(move);
	Point stopPoint = MOVE_STOP_MACRO(move);

	File startFile = POINT_FILE_MACRO(startPoint);
	Rank startRank = POINT_RANK_MACRO(startPoint);

	File stopFile = POINT_FILE_MACRO(stopPoint);
	Rank stopRank = POINT_RANK_MACRO(stopPoint);

	unsigned short fileOffset = positive_short_value(stopFile - startFile);
	unsigned short rankOffset = positive_short_value(stopRank - startRank);

	Move moveFlag = move & MOVE_FLAG_MASK;

	if(moveFlag != MOVE_FLAG_NONE && moveFlag != MOVE_FLAG_PASSANT)
	{
		// The rook can only have the move flags: NONE, PASSANT
		return false;
	}

	// It goes straight
	if(fileOffset == 0 || rankOffset == 0)
	{
		return true;
	}

	return false;
}

// The move pattern of a queen should include:
// - it only going straight and diagonal, for how far it wants
// - moving flags: [NONE, PASSANT]
bool queen_pattern_valid(Move move, Piece pieceTeam)
{
	Point startPoint = MOVE_START_MACRO(move);
	Point stopPoint = MOVE_STOP_MACRO(move);

	File startFile = POINT_FILE_MACRO(startPoint);
	Rank startRank = POINT_RANK_MACRO(startPoint);

	File stopFile = POINT_FILE_MACRO(stopPoint);
	Rank stopRank = POINT_RANK_MACRO(stopPoint);

	unsigned short fileOffset = positive_short_value(stopFile - startFile);
	unsigned short rankOffset = positive_short_value(stopRank - startRank);

	Move moveFlag = move & MOVE_FLAG_MASK;

	if(moveFlag != MOVE_FLAG_NONE && moveFlag != MOVE_FLAG_PASSANT)
	{
		// The queen can only have the move flags: NONE, PASSANT
		return false;
	}

	// It goes diagonal
	if(fileOffset == rankOffset)
	{
		return true;
	}

	// It goes straight
	if(fileOffset == 0 || rankOffset == 0)
	{
		return true;
	}

	return false;
}

// The move pattern of a king should include:
// - it only going straight and diagonal
// - moving flags: [NONE, CASTLE, PASSANT]
bool king_pattern_valid(Move move, Piece pieceTeam)
{
	Point startPoint = MOVE_START_MACRO(move);
	Point stopPoint = MOVE_STOP_MACRO(move);

	File startFile = POINT_FILE_MACRO(startPoint);
	Rank startRank = POINT_RANK_MACRO(startPoint);

	File stopFile = POINT_FILE_MACRO(stopPoint);
	Rank stopRank = POINT_RANK_MACRO(stopPoint);

	unsigned short fileOffset = positive_short_value(stopFile - startFile);
	unsigned short rankOffset = positive_short_value(stopRank - startRank);


	File teamRank;

	if(!team_starting_rank(&teamRank, pieceTeam))
	{
		return false;
	}


	Move moveFlag = move & MOVE_FLAG_MASK;

	if(moveFlag == MOVE_FLAG_CASTLE)
	{
		// This should control that the king is in its starting position,
		// and that it moves only sideways 2 steps

		if(startFile != KING_START_FILE || startRank != teamRank)
		{
			return false;
		}

		if(rankOffset != 0 || (fileOffset != KING_CASTLE_PAT || fileOffset != QUEEN_CASTLE_PAT) )
		{
			return false;
		}

		return true;
	}
	else if(moveFlag != MOVE_FLAG_NONE && moveFlag != MOVE_FLAG_PASSANT)
	{
		// The rook can only have the move flags: NONE, PASSANT

		return false;
	}

	// It only goes one square
	if(fileOffset <= 1 && rankOffset <= 1)
	{
		return true;
	}

	return false;
}