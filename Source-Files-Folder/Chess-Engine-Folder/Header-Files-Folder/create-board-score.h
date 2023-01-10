
#ifndef CREATE_BOARD_SCORE_H
#define CREATE_BOARD_SCORE_H

signed short board_state_score(const Piece board[], Info info);

signed short board_pieces_score(const Piece board[]);

signed short check_mate_score(const Piece board[], Info info);

signed short check_draw_score(const Piece board[], Info info);


signed short chess_piece_score(Piece piece);

signed short team_weight_score(signed short score, unsigned short team);

signed short piece_matrix_score(Piece piece, Point point);

signed short type_matrix_score(Piece pieceType, unsigned short rank, unsigned short file);

unsigned short team_matrix_rank(unsigned short rank, Piece pieceTeam);

#endif
