
#ifndef HANDLER_FIELD_INFO_H
#define HANDLER_FIELD_INFO_H

bool info_team_exists(Info infoTeam);

Info info_team_enemy(Info infoTeam);

Point passant_pawn_point(Info info);

bool current_team_move(Info info, unsigned short team);

bool switch_current_team(Info* info);

bool increase_info_turns(Info* info);

#endif
