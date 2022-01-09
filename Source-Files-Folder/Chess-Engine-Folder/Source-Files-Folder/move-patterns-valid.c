
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
	return true;
}

// The move pattern of a knight should include:
// - it only moving in small L:s
// - moving flags: [NONE, PASSANT]
bool knight_pattern_valid(Move move, Piece pieceTeam)
{
	return true;
}

// The move pattern of a bishop should include:
// - it only moving diagonal, for how far it wants
// - moving flags: [NONE, PASSANT]
bool bishop_pattern_valid(Move move, Piece pieceTeam)
{
	return true;
}

// The move pattern of a rook should include:
// - it only moving straight, for how far it wants
// - moving flags: [PASSANT, NONE]
bool rook_pattern_valid(Move move, Piece pieceTeam)
{
	/*Point startPoint = MOVE_START_MACRO(move);
	Point stopPoint = MOVE_STOP_MACRO(move);

	File startFile = POINT_FILE_MACRO(startPoint);
	Rank startRank = POINT_RANK_MACRO(startPoint);

	File stopFile = POINT_FILE_MACRO(stopPoint);
	Rank stopRank = POINT_RANK_MACRO(stopPoint);*/

	return true;
}

// The move pattern of a queen should include:
// - it only going straight and diagonal, for how far it wants
// - moving flags: [NONE, PASSANT]
bool queen_pattern_valid(Move move, Piece pieceTeam)
{
	return true;
}

// The move pattern of a king should include:
// - it only going straight and diagonal
// - moving flags: [NONE, CASTLE, PASSANT]
bool king_pattern_valid(Move move, Piece pieceTeam)
{
	return true;
}