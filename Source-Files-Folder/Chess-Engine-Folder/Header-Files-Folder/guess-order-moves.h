
#ifndef GUESS_ORDER_MOVES_H
#define GUESS_ORDER_MOVES_H

bool guess_moves_scores(int** moveScores, const Move moveArray[], int moveAmount, const Piece board[], Info info);

int guess_move_score(const Piece board[], Info info, Move move);

bool guess_order_moves(Move* moveArray, int moveAmount, const Piece board[], Info info, uint8_t team);

bool ordered_legal_moves(Move** moveArray, int* moveAmount, const Piece board[], Info info, uint8_t team);

#endif
