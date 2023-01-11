
#include "../Header-Files-Folder/console-include-file.h"

bool console_result_handler(const Piece board[], Info info)
{
  print_console_board(board);

  return true;
}

bool console_user_handler(Piece* board, Info* info)
{
  Move move = MOVE_NONE;
	if(!input_console_move(&move, board, *info)) return false;

	if(!move_chess_piece(board, info, move))
		return console_user_handler(board, info);

	return true;
}

bool console_engine_handler(Piece* board, Info* info, Entry* hashTable)
{
	unsigned short seconds = 2;

	Move engineMove;
	if(!optimal_depth_move(&engineMove, board, *info, hashTable, seconds)) return false;

	if(!move_chess_piece(board, info, engineMove)) return false;

  return true;
}
