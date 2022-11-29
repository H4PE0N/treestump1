
#ifndef AMOUNT_ENGINE_MOVES_H
#define AMOUNT_ENGINE_MOVES_H

bool amount_engine_moves(Move** moveArray, const Piece board[], Info info, unsigned short team, short depth, short amount);

void paste_engine_moves(Move** moveArray, short amount, const Move engineMoves[], short engineAmount);

bool sorted_engine_moves(Move** moveArray, short* moveAmount, const Piece board[], Info info, unsigned short team, short depth);

bool move_array_values(short** moveValues, const Piece board[], Info info, unsigned short team, short depth, const Move moveArray[], short moveAmount);

short* create_short_array(unsigned short length);

#endif
