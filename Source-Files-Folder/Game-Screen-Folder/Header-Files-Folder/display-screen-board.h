
#ifndef DISPLAY_SCREEN_BOARD_H
#define DISPLAY_SCREEN_BOARD_H

bool display_chess_board(Screen, const Piece[], Info, const Move[], bool);

bool display_move_board(Screen, const Piece[], Info, const Move[], Point, bool);

bool display_result_board(Screen, const Piece[], Info, bool);

bool display_promote_board(Screen, unsigned short);

bool display_mark_board(Screen, const Piece[], Info, const Move[], const Point[], bool);

#endif
