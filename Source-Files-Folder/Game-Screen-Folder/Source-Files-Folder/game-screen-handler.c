
#include "../Header-Files-Folder/screen-include-file.h"

bool setup_screen_struct(Screen* screen, const char title[], unsigned short width, unsigned short height)
{
	if(!init_screen_drivers(SDL_INIT_VIDEO, IMG_INIT_PNG)) return false;

	screen->width = width; screen->height = height;

	if(!create_screen_window(&screen->window, title, screen->height, screen->width))
	{
		SDL_Quit(); IMG_Quit(); return false;
	}

	if(!create_window_render(&screen->render, screen->window))
	{
		SDL_DestroyWindow(screen->window);

		SDL_Quit(); IMG_Quit(); return false;
	}

	return true;
}

bool init_screen_drivers(Uint32 sdlFlags, Uint32 imgFlags)
{
	if(SDL_Init(sdlFlags) != 0) return false;

	if(IMG_Init(imgFlags) == 0) { SDL_Quit(); return false; }

	return true;
}

bool create_screen_window(Window** window, const char title[], unsigned short height, unsigned short width)
{
	*window = SDL_CreateWindow(title, WINDOW_CENTER, WINDOW_CENTER, width, height, WINDOW_SHOWN | WINDOW_RESIZE | WINDOW_OPENGL);

	SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl");

	return (*window != NULL);
}

bool create_window_render(Render** render, Window* window)
{
	*render = SDL_CreateRenderer(window, -1, 0);

	return (*render != NULL);
}

bool create_surface_texture(Texture** texture, Render* render, Surface* surface)
{
  *texture = SDL_CreateTextureFromSurface(render, surface);

	return (texture != NULL);
}

void free_screen_struct(Screen screen)
{
	SDL_DestroyRenderer(screen.render);

	SDL_DestroyWindow(screen.window);

	SDL_Quit(); IMG_Quit();
}
