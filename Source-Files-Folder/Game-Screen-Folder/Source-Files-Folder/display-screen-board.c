
#include "../Header-Files-Folder/screen-include-file.h"

bool display_move_board(Screen screen, const Piece board[], Info info, Kings kings, const Move moveArray[], Point point, bool inverted)
{
	SDL_RenderClear(screen.render);

	if(!render_move_board(screen, board, info, kings, moveArray, point, inverted)) return false;

	SDL_RenderPresent(screen.render); return true;
}

bool display_result_board(Screen screen, const Piece board[], Info info, Kings kings, bool inverted)
{
	SDL_RenderClear(screen.render);

	if(!render_result_board(screen, board, info, kings, inverted)) return false;

	SDL_RenderPresent(screen.render); return true;
}

bool display_promote_board(Screen screen, unsigned short team)
{
	SDL_RenderClear(screen.render);

	if(!render_promote_board(screen, team)) return false;

	SDL_RenderPresent(screen.render); return true;
}

bool display_mark_board(Screen screen, const Piece board[], Info info, Kings kings, const Move moveArray[], const Point markPoints[], bool inverted)
{
	SDL_RenderClear(screen.render);

	if(!render_mark_board(screen, board, info, kings, moveArray, markPoints, inverted)) return false;

	SDL_RenderPresent(screen.render); return true;
}

bool display_chess_board(Screen screen, const Piece board[], Info info, Kings kings, const Move moveArray[], bool inverted)
{
	SDL_RenderClear(screen.render);

	if(!render_chess_board(screen, board, info, kings, moveArray, inverted)) return false;

	SDL_RenderPresent(screen.render); return true;
}
