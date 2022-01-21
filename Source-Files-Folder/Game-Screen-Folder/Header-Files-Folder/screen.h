
#ifndef SCREEN_H
#define SCREEN_H

bool create_screen_window(Window**, unsigned short, unsigned short, char[]);

bool create_window_surface(Surface**, Window*);

bool create_surface_renderer(Renderer**, Surface*);

bool create_surface_texture(Texture**, Renderer*, Surface*);

bool setup_display_screen(Screen*, char[]);

void free_display_screen(Screen);

bool render_surface_texture(Renderer*, Surface*, Rect);

bool render_move_squares(Screen, const Piece[], Info, Kings, Point);

bool render_board_moves(Screen, const Move[]);

bool render_check_squares(Screen, const Piece[], Info, Kings);

bool render_board_pieces(Screen, const Piece[]);

bool render_chess_board(Screen, const Piece[], Info, Kings, const Move[], Point);

bool extract_piece_image(Surface**, Piece);

bool extract_piece_file(char**, Piece);

bool board_point_position(Rect*, Screen, Point);

bool render_board_piece(Screen, Piece, Point);

bool load_filename_image(Surface**, char[]);

bool render_check_square(Screen, const Piece[], Info, Point);

bool render_point_image(Screen, Surface*, Point, Uint8);

bool render_board_image(Renderer*, Surface*, Rect, Uint8);

bool render_board_move(Screen, Surface*, Move, Uint8);

bool input_promote_move(Move*, Screen, Piece);

Point parse_mouse_point(Event, Screen);

#endif
