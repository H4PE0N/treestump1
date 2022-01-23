
#include "../Header-Files-Folder/game-screen-includer.h"

bool setup_display_screen(Screen* screen, char title[])
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

	if(!create_screen_window(&screen->window, screen->height, screen->width, title))
	{
		SDL_Quit();

		return false;
	}

	if(!create_window_surface(&screen->surface, screen->window))
	{
		SDL_DestroyWindow(screen->window);

		SDL_Quit();

		return false;
	}

	if(!create_surface_renderer(&screen->renderer, screen->surface))
	{
		SDL_FreeSurface(screen->surface);

		SDL_DestroyWindow(screen->window);

		SDL_Quit();

		return false;
	}

	return true;
}

bool create_surface_texture(Texture** texture, Renderer* renderer, Surface* surface)
{
  *texture = SDL_CreateTextureFromSurface(renderer, surface);

	return (texture != NULL);
}

bool create_surface_renderer(Renderer** renderer, Surface* surface)
{
  *renderer = SDL_CreateSoftwareRenderer(surface);

	return (*renderer != NULL);
}

bool create_window_surface(Surface** surface, Window* window)
{
  *surface = SDL_GetWindowSurface(window);

	return (*surface != NULL);
}

bool create_screen_window(Window** window, unsigned short height, unsigned short width, char title[])
{
  *window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, 0);

	return (*window != NULL);
}

void free_display_screen(Screen screen)
{
	SDL_DestroyRenderer(screen.renderer);

	SDL_FreeSurface(screen.surface);

	SDL_DestroyWindow(screen.window);

	SDL_Quit();
}
