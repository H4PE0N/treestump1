
#ifndef GUESS_ORDER_MOVES_H
#define GUESS_ORDER_MOVES_H

bool guess_moves_scores(signed short** moveScores, const Move moveArray[], short moveAmount, const Piece board[], Info info);

signed short guess_move_score(const Piece board[], Info info, Move move);

bool guess_order_moves(Move* moveArray, short moveAmount, const Piece board[], Info info, unsigned short team);

bool ordered_legal_moves(Move** moveArray, short* moveAmount, const Piece board[], Info info, unsigned short team);

#endif
