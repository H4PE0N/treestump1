
#include "../Header-Files-Folder/game-screen-includer.h"

bool display_chess_board(Screen screen, const Piece board[], Info info, Kings kings, const Move moveArray[], Point point)
{
	SDL_RenderClear(screen.render);

	if(!render_chess_board(screen, board, info, kings, moveArray, point)) return false;

	SDL_RenderPresent(screen.render);

	return true;
}

bool display_result_board(Screen screen, const Piece board[], Info info, Kings kings)
{
	SDL_RenderClear(screen.render);

	if(!render_result_board(screen, board, info, kings)) return false;

	SDL_RenderPresent(screen.render);

	return true;
}

bool display_promote_board(Screen screen, unsigned short team)
{
	SDL_RenderClear(screen.render);

	if(!render_promote_board(screen, team)) return false;

	SDL_RenderPresent(screen.render);

	return true;
}

bool display_input_board(Screen screen, const Piece board[], Info info, Kings kings, const Move moveArray[], const Point markPoints[], Point point)
{
	SDL_RenderClear(screen.render);

	if(!render_chess_board(screen, board, info, kings, moveArray, point)) return false;

	if(!render_input_marks(screen, markPoints)) return false;

	SDL_RenderPresent(screen.render);

	return true;
}
