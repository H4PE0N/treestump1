
#include "../Header-Files-Folder/engine-include-file.h"

bool move_fully_legal(const Piece board[], Info info, Move move)
{
	if(!move_pseudo_legal(board, info, move))
	{
		return false;
	}

	// This function should check:
	// - the move is pseudo legal
	// - the own king is not set in check

	return true;
}

bool move_pseudo_legal(const Piece board[], Info info, Move move)
{
	// This function should check:
	// - the piece is allowed to move that way
	// - the move path is clear (except for the knight)

	return true;
}