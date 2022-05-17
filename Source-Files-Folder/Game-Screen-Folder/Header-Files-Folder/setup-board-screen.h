
#ifndef SETUP_BOARD_SCREEN_H
#define SETUP_BOARD_SCREEN_H

bool create_screen_window(Window**, const char[], unsigned short, unsigned short);

bool create_window_render(Render**, Window*);

bool setup_screen_struct(Screen*, const char[], unsigned short, unsigned short);

void free_screen_struct(Screen);

#endif
