
#ifndef GUESS_ORDER_MOVES_H
#define GUESS_ORDER_MOVES_H

bool guess_moves_values(signed short** moveValues, const Move moveArray[], short moveAmount, const Piece board[], Info info);

signed short guess_move_value(const Piece board[], Info info, Move move);

bool guess_order_moves(Move* moveArray, short moveAmount, const Piece board[], Info info);

bool ordered_legal_moves(Move** moveArray, const Piece board[], Info info, unsigned short team);

#endif
