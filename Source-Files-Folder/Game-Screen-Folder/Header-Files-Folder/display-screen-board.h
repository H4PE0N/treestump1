
#ifndef DISPLAY_SCREEN_BOARD_H
#define DISPLAY_SCREEN_BOARD_H

bool display_chess_board(Screen, const Piece[], Info, Kings, const Move[], Point);

bool display_result_board(Screen, const Piece[], Info, Kings);

bool display_promote_board(Screen, unsigned short);

#endif
