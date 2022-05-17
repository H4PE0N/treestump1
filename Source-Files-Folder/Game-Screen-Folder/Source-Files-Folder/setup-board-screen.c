
#include "../Header-Files-Folder/game-screen-includer.h"

bool setup_screen_struct(Screen* screen, const char title[], unsigned short width, unsigned short height)
{
	if(SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		return false;
	}

	if(IMG_Init(IMG_INIT_PNG) == 0)
	{
		SDL_Quit();

		return false;
	}

	screen->width = width;
	screen->height = height;

	if(!create_screen_window(&screen->window, title, screen->height, screen->width))
	{
		SDL_Quit();

		return false;
	}

	if(!create_window_render(&screen->render, screen->window))
	{
		SDL_DestroyWindow(screen->window);

		SDL_Quit();

		return false;
	}

	return true;
}

bool create_screen_window(Window** window, const char title[], unsigned short height, unsigned short width)
{
	*window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

	SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl");

	return (*window != NULL);
}

bool create_window_render(Render** render, Window* window)
{
	*render = SDL_CreateRenderer(window, -1, 0);

	return (*render != NULL);
}

void free_screen_struct(Screen screen)
{
	SDL_DestroyRenderer(screen.render);

	SDL_DestroyWindow(screen.window);

	SDL_Quit();
}
