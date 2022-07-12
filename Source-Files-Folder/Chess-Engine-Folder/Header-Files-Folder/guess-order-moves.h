
#ifndef GUESS_ORDER_MOVES_H
#define GUESS_ORDER_MOVES_H

bool guess_moves_values(signed short**, const Move[], short, const Piece[], Info);

signed short guess_move_value(const Piece[], Info, Move);

bool guess_order_moves(Move*, short, const Piece[], Info);

bool ordered_legal_moves(Move**, const Piece[], Info, unsigned short);

#endif
