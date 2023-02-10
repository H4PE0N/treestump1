
#ifndef MOVE_ABILITY_VALID_H
#define MOVE_ABILITY_VALID_H

bool move_ability_valid(Move move, State state);

bool passant_ability_valid(Move move, State state);

bool castle_ability_valid(Move move, State state);

#endif
