
#ifndef CREATE_BOARD_VALUE_H
#define CREATE_BOARD_VALUE_H

signed short board_state_value(const Piece board[], Info info);

signed short board_pieces_value(const Piece board[]);

signed short check_mate_value(const Piece board[], Info info);

signed short check_draw_value(const Piece board[], Info info);


signed short chess_piece_value(Piece piece);

signed short team_weight_value(signed short value, unsigned short team);

signed short piece_matrix_value(Piece piece, Point point);

signed short type_matrix_value(Piece pieceType, unsigned short rank, unsigned short file);

unsigned short team_matrix_rank(unsigned short rank, Piece pieceTeam);

#endif
