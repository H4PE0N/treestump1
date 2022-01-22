
#ifndef CREATE_BOARD_VALUE_H
#define CREATE_BOARD_VALUE_H

signed short team_state_value(const Piece[], Info, Kings, unsigned short);

signed short team_pieces_value(const Piece[], unsigned short);

signed short piece_matrix_value(Piece, Point);

signed short check_mate_value(const Piece[], Info, Kings, unsigned short);

signed short check_draw_value(const Piece[], Info, Kings, unsigned short);

signed short board_state_value(const Piece[], Info, Kings, unsigned short);

#endif
