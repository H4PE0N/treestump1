
#include "../Header-Files-Folder/game-screen-includer.h"

bool input_screen_move(Move* move, Screen screen, const Piece board[], Info info, Kings kings, const Move moves[])
{
	Move inputMove = MOVE_NONE;
	Event event;

	while(!move_inside_board(inputMove))
	{
		if(!display_chess_board(screen, board, info, kings, moves, -1)) return false;

		if(!SDL_WaitEvent(&event)) continue;

		if(event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_q))
		{
		  return false;
		}

		screen_move_parser(&inputMove, screen, board, info, kings, moves, event);
	}

	*move = inputMove;

	return true;
}

bool screen_move_parser(Move* move, Screen screen, const Piece board[], Info info, Kings kings, const Move moves[], Event event)
{
	if(event.type == SDL_MOUSEBUTTONDOWN)
	{
		Point startPoint = parse_mouse_point(event, screen);

		if(!display_chess_board(screen, board, info, kings, moves, startPoint)) return false;


		Event upEvent;

		while(upEvent.type != SDL_MOUSEBUTTONUP)
		{
			SDL_WaitEvent(&upEvent);
		}

		Point stopPoint = parse_mouse_point(upEvent, screen);


		*move = (START_MOVE_MACRO(startPoint) | STOP_MOVE_MACRO(stopPoint));

		return true;
	}

	return false;
}
