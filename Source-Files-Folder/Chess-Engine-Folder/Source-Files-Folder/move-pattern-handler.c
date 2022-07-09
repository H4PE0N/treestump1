
#include "../Header-Files-Folder/engine-include-file.h"

bool move_pattern_valid(Move move, Piece piece)
{
	unsigned short team = PIECE_TEAM_MACRO(piece);

	if(PIECE_STORE_TYPE(piece, PIECE_TYPE_PAWN))
		return pawn_pattern_handler(move, team);

	if(PIECE_STORE_TYPE(piece, PIECE_TYPE_KNIGHT))
		return knight_pattern_handler(move, team);

	if(PIECE_STORE_TYPE(piece, PIECE_TYPE_BISHOP))
		return bishop_pattern_handler(move, team);

	if(PIECE_STORE_TYPE(piece, PIECE_TYPE_ROOK))
		return rook_pattern_handler(move, team);

	if(PIECE_STORE_TYPE(piece, PIECE_TYPE_QUEEN))
		return queen_pattern_handler(move, team);

	if(PIECE_STORE_TYPE(piece, PIECE_TYPE_KING))
		return king_pattern_handler(move, team);

	return false;
}

bool pawn_pattern_handler(Move move, unsigned short team)
{
	if(MOVE_STORE_FLAG(move, MOVE_FLAG_DOUBLE))
		return double_pattern_valid(move, team);

	if(MOVE_STORE_FLAG(move, MOVE_FLAG_PASSANT))
		return passant_pattern_valid(move, team);

	if(MOVE_PROMOTE_FLAG(move))
		return promote_pattern_valid(move, team);

	if(MOVE_STORE_FLAG(move, MOVE_FLAG_NONE))
		return pawn_pattern_valid(move, team);

	return false;
}

bool knight_pattern_handler(Move move, unsigned short team)
{
	if(!MOVE_STORE_FLAG(move, MOVE_FLAG_NONE)) return false;

	return knight_pattern_valid(move, team);
}

bool bishop_pattern_handler(Move move, unsigned short team)
{
	if(!MOVE_STORE_FLAG(move, MOVE_FLAG_NONE)) return false;

	return bishop_pattern_valid(move, team);
}

bool rook_pattern_handler(Move move, unsigned short team)
{
	if(!MOVE_STORE_FLAG(move, MOVE_FLAG_NONE)) return false;

	return rook_pattern_valid(move, team);
}

bool queen_pattern_handler(Move move, unsigned short team)
{
	if(!MOVE_STORE_FLAG(move, MOVE_FLAG_NONE)) return false;

	return queen_pattern_valid(move, team);
}

bool king_pattern_handler(Move move, unsigned short team)
{
	if(MOVE_STORE_FLAG(move, MOVE_FLAG_CASTLE))
		return castle_pattern_valid(move, team);

	if(MOVE_STORE_FLAG(move, MOVE_FLAG_NONE))
		return king_pattern_valid(move, team);

	return false;
}
