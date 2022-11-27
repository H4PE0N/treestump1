
#ifndef HANDLER_FIELD_INFO_H
#define HANDLER_FIELD_INFO_H

Point passant_pawn_point(Info info);

bool current_team_move(Info info, unsigned short team);

bool switch_current_team(Info* info);

bool increase_info_turns(Info* info);

short team_passant_rank(short team);

#endif
