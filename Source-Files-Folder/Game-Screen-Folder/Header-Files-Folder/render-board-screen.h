
#ifndef RENDER_BOARD_SCREEN_H
#define RENDER_BOARD_SCREEN_H

bool render_chess_board(Screen, const Piece[], Info, Kings, const Move[], bool);

bool render_mark_board(Screen, const Piece[], Info, Kings, const Move[], const Point[], bool);

bool render_move_board(Screen, const Piece[], Info, Kings, const Move[], Point, bool);

bool render_promote_board(Screen, unsigned short);

bool render_result_board(Screen, const Piece[], Info, Kings, bool);

// ####################################################################################

bool render_move_squares(Screen, const Piece[], Info, Kings, Point, bool);

bool render_latest_move(Screen, const Move[], bool);

bool render_engine_moves(Screen, const Move[], bool);

bool render_check_squares(Screen, const Piece[], Info, Kings, bool);

bool render_board_pieces(Screen, const Piece[], bool);

bool render_board_piece(Screen, Piece, Point, bool);

bool render_check_square(Screen, const Piece[], Info, Point, bool);

bool render_board_squares(Screen, bool);

bool render_team_squares(Screen, unsigned short, bool);

bool render_point_image(Screen, Surface*, Point, Uint8, bool);

bool render_board_move(Screen, Surface*, Move, Uint8, bool);

bool render_screen_image(Render*, Surface*, Rect, Uint8);

bool render_input_marks(Screen, const Point[], bool);

#endif
