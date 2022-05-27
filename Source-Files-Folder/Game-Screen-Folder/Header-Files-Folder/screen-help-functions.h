
#ifndef SCREEN_HELP_FUNCTIONS_H
#define SCREEN_HELP_FUNCTIONS_H

bool extract_path_image(Surface**, const char[]);

bool extract_file_image(Surface**, const char[]);

bool extract_piece_image(Surface**, Piece);

bool extract_piece_path(char**, Piece);

bool board_point_position(Rect*, Screen, Point);

Point parse_mouse_point(Event, Screen);

bool create_surface_texture(Texture**, Render*, Surface*);

bool extract_team_square(Surface**, unsigned short);

bool parse_quit_input(Event);

#endif
