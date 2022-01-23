
#ifndef RENDER_BOARD_SCREEN_H
#define RENDER_BOARD_SCREEN_H

bool render_move_squares(Screen, const Piece[], Info, Kings, Point);

bool render_latest_move(Screen, const Move[]);

bool render_check_squares(Screen, const Piece[], Info, Kings);

bool render_board_pieces(Screen, const Piece[]);

bool render_chess_board(Screen, const Piece[], Info, Kings, const Move[], Point);

bool render_board_piece(Screen, Piece, Point);

bool render_check_square(Screen, const Piece[], Info, Point);

bool render_board_squares(Screen);

#endif
