
#ifndef HANDLER_FIELD_STATE_H
#define HANDLER_FIELD_STATE_H

#define TEAM_PASSANT_RANK(TEAM) ((TEAM == TEAM_WHITE) ? (WHITE_PAWN_RANK + WHITE_MOVE_VALUE) : (BLACK_PAWN_RANK + BLACK_MOVE_VALUE))

Point passant_pawn_point(State state);

bool current_team_move(State state, uint8_t team);

void switch_current_team(State* state);

void increase_state_turns(State* state);

void increase_state_counter(State* state);

void alloc_passant_point(State* state, Move move);

#endif
