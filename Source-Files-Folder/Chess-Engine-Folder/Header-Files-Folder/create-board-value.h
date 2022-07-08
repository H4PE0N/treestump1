
#ifndef CREATE_BOARD_VALUE_H
#define CREATE_BOARD_VALUE_H

signed short board_state_value(const Piece[], Info);

signed short board_pieces_value(const Piece[]);

signed short check_mate_value(const Piece[], Info);

signed short check_draw_value(const Piece[], Info);


signed short chess_piece_value(Piece);

signed short team_weight_value(signed short, unsigned short);

signed short piece_matrix_value(Piece, Point);

signed short type_matrix_value(Piece, unsigned short, unsigned short);

unsigned short team_matrix_rank(unsigned short, Piece);

#endif
