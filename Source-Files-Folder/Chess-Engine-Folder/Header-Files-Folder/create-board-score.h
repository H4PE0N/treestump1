
#ifndef CREATE_BOARD_SCORE_H
#define CREATE_BOARD_SCORE_H

int board_state_score(const Piece board[], Info info);

int board_pieces_score(const Piece board[]);

int check_mate_score(const Piece board[], Info info);

int check_draw_score(const Piece board[], Info info);


int chess_piece_score(Piece piece);

int piece_matrix_score(Piece piece, Point point);

int type_matrix_score(Piece pieceType, uint8_t rank, uint8_t file);

uint8_t team_matrix_rank(uint8_t rank, Piece pieceTeam);

#endif
