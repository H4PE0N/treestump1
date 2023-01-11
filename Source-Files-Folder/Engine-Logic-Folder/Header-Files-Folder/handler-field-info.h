
#ifndef HANDLER_FIELD_INFO_H
#define HANDLER_FIELD_INFO_H

#define TEAM_PASSANT_RANK(TEAM) ((TEAM == TEAM_WHITE) ? (WHITE_PAWN_RANK + WHITE_MOVE_VALUE) : (BLACK_PAWN_RANK + BLACK_MOVE_VALUE))

Point passant_pawn_point(Info info);

bool current_team_move(Info info, uint8_t team);

void switch_current_team(Info* info);

void increase_info_turns(Info* info);

void increase_info_counter(Info* info);

void alloc_passant_point(Info* info, Move move);

#endif
