
#include "../Header-Files-Folder/engine-include-file.h"

bool move_chess_piece(Piece* board, Info* info, Move move)
{
	if(!move_fully_legal(board, *info, move))
	{
		return false;
	}

	if(!execute_chess_move(board, info, move))
	{
		return false;
	}

	return true;
}