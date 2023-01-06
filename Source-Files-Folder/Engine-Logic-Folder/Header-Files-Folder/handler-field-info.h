
#ifndef HANDLER_FIELD_INFO_H
#define HANDLER_FIELD_INFO_H

Point passant_pawn_point(Info info);

bool current_team_move(Info info, unsigned short team);

void switch_current_team(Info* info);

void increase_info_turns(Info* info);

void increase_info_counter(Info* info);

void alloc_passant_point(Info* info, Move move);

short team_passant_rank(short team);

#endif
