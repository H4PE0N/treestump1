
#ifndef CREATE_BOARD_SCORE_H
#define CREATE_BOARD_SCORE_H

int board_state_score(const Piece board[], State state);

int board_pieces_score(const Piece board[]);

int chess_piece_score(Piece piece, Point point);

#endif
