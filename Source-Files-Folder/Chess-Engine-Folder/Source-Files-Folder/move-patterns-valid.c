
#include "../Header-Files-Folder/engine-include-file.h"

// This function checks:
// - if the moving pattern and flag matches the piece
bool move_pattern_valid(Move move, Piece piece)
{
	Piece pieceType = (piece & PIECE_TYPE_MASK);
	Piece pieceTeam = (piece & PIECE_TEAM_MASK);

	if(pieceType == PIECE_TYPE_NONE) return false;

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
	else return false;
}

// The move pattern of a pawn should include:
// - it moving one step forward
// - it taking pieces one step diagonal
// - double jumping two steps from its starting rank
// - moving flags: [NONE, QUEEN, ROOK, BISHOP, KNIGHT, DOUBLE, PASSANT]
bool pawn_pattern_valid(Move move, Piece pieceTeam)
{
	Point startPoint = MOVE_START_MACRO(move);
	unsigned short startRank = POINT_RANK_MACRO(startPoint);

	short fileOffset = ABS_SHORT_NUMBER(move_file_offset(move, pieceTeam));
	short rankOffset = move_rank_offset(move, pieceTeam);

	Move moveFlag = (move & MOVE_FLAG_MASK);


	if(moveFlag == MOVE_FLAG_DOUBLE)
	{
		// If it moves double, it has to be at pawn rank

		if(fileOffset != 0 || rankOffset != 2) return false;


		if(pieceTeam == PIECE_TEAM_WHITE && startRank == WHITE_PAWN_RANK) return true;

		else if(pieceTeam == PIECE_TEAM_BLACK && startRank == BLACK_PAWN_RANK) return true;


		else return false;
	}
	else if(moveFlag == MOVE_FLAG_PASSANT)
	{
		// If it is taking a passant pawn, it has to go diagonal

		if(fileOffset == 1 && rankOffset == 1) return true;

		else return false;
	}
	else if(moveFlag == MOVE_FLAG_NONE || moveFlag == MOVE_FLAG_KNIGHT || moveFlag == MOVE_FLAG_BISHOP || moveFlag == MOVE_FLAG_ROOK || moveFlag == MOVE_FLAG_QUEEN)
	{
		// If it just does a normal move, it can go forward one step or diagonal

		if(fileOffset == 1 && rankOffset == 1) return true;

		else if(fileOffset == 0 && rankOffset == 1) return true;

		else return false;
	}
	else return false;
}

// The move pattern of a knight should include:
// - it only moving in small L:s
// - moving flags: [NONE, PASSANT]
bool knight_pattern_valid(Move move, Piece pieceTeam)
{
	short fileOffset = ABS_SHORT_NUMBER(move_file_offset(move, pieceTeam));
	short rankOffset = ABS_SHORT_NUMBER(move_rank_offset(move, pieceTeam));

	Move moveFlag = (move & MOVE_FLAG_MASK);

	if(moveFlag == MOVE_FLAG_NONE || moveFlag == MOVE_FLAG_PASSANT)
	{
		// The knight can only have the move flags: NONE, PASSANT

		if(fileOffset == 1 && rankOffset == 2) return true;

		else if(fileOffset == 2 && rankOffset == 1) return true;

		else return false;
	}
	else return false;
}

// The move pattern of a bishop should include:
// - it only moving diagonal, for how far it wants
// - moving flags: [NONE, PASSANT]
bool bishop_pattern_valid(Move move, Piece pieceTeam)
{
	short fileOffset = ABS_SHORT_NUMBER(move_file_offset(move, pieceTeam));
	short rankOffset = ABS_SHORT_NUMBER(move_rank_offset(move, pieceTeam));

	Move moveFlag = (move & MOVE_FLAG_MASK);

	if(moveFlag == MOVE_FLAG_NONE || moveFlag == MOVE_FLAG_PASSANT)
	{
		// The bishop can only have the move flags: NONE, PASSANT

		if(fileOffset == rankOffset) return true;

		else return false;
	}

	else return false;
}

// The move pattern of a rook should include:
// - it only moving straight, for how far it wants
// - moving flags: [PASSANT, NONE]
bool rook_pattern_valid(Move move, Piece pieceTeam)
{
	short fileOffset = ABS_SHORT_NUMBER(move_file_offset(move, pieceTeam));
	short rankOffset = ABS_SHORT_NUMBER(move_rank_offset(move, pieceTeam));

	Move moveFlag = (move & MOVE_FLAG_MASK);

	if(moveFlag == MOVE_FLAG_NONE || moveFlag == MOVE_FLAG_PASSANT)
	{
		// The rook can only have the move flags: NONE, PASSANT

		if(fileOffset == 0 || rankOffset == 0) return true;

		else return false;
	}

	else return false;
}

// The move pattern of a queen should include:
// - it only going straight and diagonal, for how far it wants
// - moving flags: [NONE, PASSANT]
bool queen_pattern_valid(Move move, Piece pieceTeam)
{
	short fileOffset = ABS_SHORT_NUMBER(move_file_offset(move, pieceTeam));
	short rankOffset = ABS_SHORT_NUMBER(move_rank_offset(move, pieceTeam));

	Move moveFlag = (move & MOVE_FLAG_MASK);

	if(moveFlag == MOVE_FLAG_NONE || moveFlag == MOVE_FLAG_PASSANT)
	{
		// The queen can only have the move flags: NONE, PASSANT

		if(fileOffset == rankOffset) return true;

		else if(fileOffset == 0 || rankOffset == 0) return true;

		else return false;
	}
	else return false;
}

// The move pattern of a king should include:
// - it only going straight and diagonal
// - moving flags: [NONE, CASTLE, PASSANT]
bool king_pattern_valid(Move move, Piece pieceTeam)
{
	Point startPoint = MOVE_START_MACRO(move);

	unsigned short startFile = POINT_FILE_MACRO(startPoint);
	unsigned short startRank = POINT_RANK_MACRO(startPoint);

	short fileOffset = ABS_SHORT_NUMBER(move_file_offset(move, pieceTeam));
	short rankOffset = ABS_SHORT_NUMBER(move_rank_offset(move, pieceTeam));

	Move moveFlag = (move & MOVE_FLAG_MASK);

	if(moveFlag == MOVE_FLAG_CASTLE)
	{
		// This should control that the king is in its starting position,
		// and that it moves only sideways 2 steps

		if(startFile != KING_START_FILE) return false;


		if(pieceTeam == PIECE_TEAM_WHITE && startRank != WHITE_START_RANK) return false;

		if(pieceTeam == PIECE_TEAM_BLACK && startRank != BLACK_START_RANK) return false;

		if(pieceTeam != PIECE_TEAM_WHITE && pieceTeam != PIECE_TEAM_BLACK) return false;


		if(rankOffset != 0) return false;

		if(fileOffset != KING_CASTLE_PAT || fileOffset != QUEEN_CASTLE_PAT) return false;


		return true;
	}
	else if(moveFlag == MOVE_FLAG_NONE || moveFlag == MOVE_FLAG_PASSANT)
	{
		// The rook can only have the move flags: NONE, PASSANT

		if(fileOffset <= 1 && rankOffset <= 1) return true;

		else return false;
	}
	else return false;
}
