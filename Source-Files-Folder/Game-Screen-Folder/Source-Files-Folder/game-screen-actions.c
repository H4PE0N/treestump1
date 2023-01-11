
#include "../Header-Files-Folder/screen-include-file.h"

bool screen_engine_handler(Piece* board, Info* info, Move* moves, Screen screen)
{
	unsigned short seconds = 10;

	Move computerMove;
	if(!optimal_depth_move(&computerMove, board, *info, seconds)) return false;

	if(!move_chess_piece(board, info, computerMove)) return false;

	int movesAmount = move_array_amount(moves);
	moves[movesAmount] = computerMove;

	return true;
}

bool screen_user_handler(Piece* board, Info* info, Move* moves, Screen* screen)
{
	Move move = MOVE_NONE;
	if(!input_screen_move(&move, screen, board, *info, moves)) return false;

	if(!move_chess_piece(board, info, move))
		return screen_user_handler(board, info, moves, screen);

	int movesAmount = move_array_amount(moves);
	moves[movesAmount] = move;

	return true;
}

bool screen_result_handler(Screen* screen, const Piece board[], Info info)
{
	if(!display_result_board(*screen, board, info))
	{
		printf("Could not display result board!\n");
	}

	Event event;
	while(!parse_quit_input(event))
	{ SDL_WaitEvent(&event); SDL_Delay(100); }

	return true;
}
