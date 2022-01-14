
#ifndef SCREEN_H
#define SCREEN_H

bool create_screen_window(Window**, short, short, char[]);

bool create_window_surface(Surface**, Window*);

bool create_surface_renderer(Renderer**, Surface*);

bool create_surface_texture(Texture**, Renderer*, Surface*);

bool setup_display_screen(Screen*, char[]);

void free_display_screen(Screen);

bool render_surface_texture(Renderer*, Surface*, Rect);

bool render_move_squares(Screen, const Piece[], Info, Point);

bool render_board_move(Screen, Move, Surface*);

bool render_check_squares(Screen, const Piece[], Info);

bool render_board_pieces(Screen, const Piece[]);					

bool render_chess_board(Screen, const Piece[], Info, Point);

bool extract_piece_image(Surface**, Piece);

bool extract_piece_file(char**, Piece);

bool board_point_position(Rect*, Screen, Point);

bool render_board_piece(Screen, Piece, Point);

bool load_filename_image(Surface**, char[]);

#endif