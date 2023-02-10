
#include "../Header-Files-Folder/screen-include-file.h"

bool display_move_board(Screen screen, const Piece board[], State state, const Move moveArray[], Point point)
{
	SDL_RenderClear(screen.render);

	if(!render_move_board(screen, board, state, moveArray, point)) return false;

	SDL_RenderPresent(screen.render); return true;
}

bool display_result_board(Screen screen, const Piece board[], State state)
{
	SDL_RenderClear(screen.render);

	if(!render_result_board(screen, board, state)) return false;

	SDL_RenderPresent(screen.render); return true;
}

bool display_promote_board(Screen screen, unsigned short team)
{
	SDL_RenderClear(screen.render);

	if(!render_promote_board(screen, team)) return false;

	SDL_RenderPresent(screen.render); return true;
}

bool display_mark_board(Screen screen, const Piece board[], State state, const Move moveArray[], const Point markPoints[])
{
	SDL_RenderClear(screen.render);

	if(!render_mark_board(screen, board, state, moveArray, markPoints)) return false;

	SDL_RenderPresent(screen.render); return true;
}

bool display_chess_board(Screen screen, const Piece board[], State state, const Move moveArray[])
{
	SDL_RenderClear(screen.render);

	if(!render_chess_board(screen, board, state, moveArray)) return false;

	SDL_RenderPresent(screen.render); return true;
}
