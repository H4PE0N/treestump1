
#include "../Header-Files-Folder/console-include-file.h"

bool console_result_handler(const Piece board[], State state)
{
  print_console_board(board);

  return true;
}

bool console_user_handler(Piece* board, State* state)
{
  Move move = MOVE_NONE;
	if(!input_console_move(&move, board, *state)) return false;

	if(!move_chess_piece(board, state, move))
		return console_user_handler(board, state);

	return true;
}

bool console_engine_handler(Piece* board, State* state, Entry* hashTable)
{
	unsigned short seconds = 2;

	Move engineMove;
	if(!optimal_depth_move(&engineMove, board, *state, hashTable, seconds)) return false;

	if(!move_chess_piece(board, state, engineMove)) return false;

  return true;
}
