
#ifndef GUESS_ORDER_MOVES_H
#define GUESS_ORDER_MOVES_H

bool guess_moves_scores(int** moveScores, const Move moveArray[], int moveAmount, const Piece board[], State state);

int guess_move_score(const Piece board[], State state, Move move);

bool guess_order_moves(Move* moveArray, int moveAmount, const Piece board[], State state, uint8_t team);

bool ordered_legal_moves(Move** moveArray, int* moveAmount, const Piece board[], State state, uint8_t team);

#endif
