
#ifndef SETUP_BOARD_SCREEN_H
#define SETUP_BOARD_SCREEN_H

bool create_screen_window(Window**, unsigned short, unsigned short, char[]);

bool create_window_surface(Surface**, Window*);

bool create_surface_renderer(Renderer**, Surface*);

bool create_surface_texture(Texture**, Renderer*, Surface*);

bool setup_display_screen(Screen*, char[]);

void free_display_screen(Screen);

#endif
