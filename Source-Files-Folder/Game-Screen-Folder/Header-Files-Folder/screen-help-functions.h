
#ifndef SCREEN_HELP_FUNCTIONS_H
#define SCREEN_HELP_FUNCTIONS_H

bool render_board_image(Renderer*, Surface*, Rect, Uint8);

bool load_filename_image(Surface**, char[]);

bool extract_piece_image(Surface**, Piece);

bool extract_piece_file(char**, Piece);

bool render_point_image(Screen, Surface*, Point, Uint8);

bool render_board_move(Screen, Surface*, Move, Uint8);

bool board_point_position(Rect*, Screen, Point);

Point parse_mouse_point(Event, Screen);

#endif
