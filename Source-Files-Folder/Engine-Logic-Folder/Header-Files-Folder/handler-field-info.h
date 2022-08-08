
#ifndef HANDLER_FIELD_INFO_H
#define HANDLER_FIELD_INFO_H

bool info_team_exists(Info);

Info info_team_enemy(Info);

Point passant_pawn_point(Info);

bool current_team_move(Info, unsigned short);

bool switch_current_team(Info*);

bool increase_info_turns(Info*);

#endif
