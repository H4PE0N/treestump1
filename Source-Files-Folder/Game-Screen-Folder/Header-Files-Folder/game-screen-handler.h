
#ifndef GAME_SCREEN_HANDLER_H
#define GAME_SCREEN_HANDLER_H

bool create_screen_window(Window**, const char[], int width, int height);

bool create_window_render(Render**, Window*);

bool setup_screen_struct(Screen*, const char[], int width, int height);

void free_screen_struct(Screen);

bool init_screen_drivers(Uint32, Uint32);

bool create_surface_texture(Texture**, Render*, Surface*);

#endif
