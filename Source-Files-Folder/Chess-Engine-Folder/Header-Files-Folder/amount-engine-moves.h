
#ifndef AMOUNT_ENGINE_MOVES_H
#define AMOUNT_ENGINE_MOVES_H

bool amount_engine_moves(Move**, const Piece[], Info, unsigned short, short, short);

void paste_engine_moves(Move**, short, const Move[], short);

bool sorted_engine_moves(Move**, const Piece[], Info, unsigned short, short);

bool move_array_values(short**, const Piece[], Info, unsigned short, short, const Move[], short);

short* create_short_array(unsigned short);

#endif
