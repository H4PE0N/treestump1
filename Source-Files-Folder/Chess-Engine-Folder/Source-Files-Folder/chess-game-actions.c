
#include "../Header-Files-Folder/engine-include-file.h"

bool move_chess_piece(Piece* board, Info* info, Move move)
{
	if(!move_fully_legal(board, *info, move))
	{
		return false;
	}

	// Execute move (change board and info)

	return true;
}