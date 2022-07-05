
#ifndef MOVE_ABILITY_VALID_H
#define MOVE_ABILITY_VALID_H

bool move_ability_valid(Move, Piece, Info);

bool passant_ability_valid(Move, Info);

bool castle_ability_valid(Move, Info, Piece);

#endif
