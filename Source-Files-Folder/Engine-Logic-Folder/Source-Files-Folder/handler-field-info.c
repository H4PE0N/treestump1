
#include "../Header-Files-Folder/englog-include-file.h"

Point passant_pawn_point(Info info)
{
	uint8_t passantFile = INFO_PASSANT_MACRO(info);
	if(passantFile == 0) return POINT_NONE;

	uint8_t currentTeam = INFO_TEAM_MACRO(info);
	if(currentTeam == TEAM_NONE) return POINT_NONE;

	uint8_t enemyTeam = NORMAL_TEAM_ENEMY(currentTeam);

	uint8_t pawnRank = TEAM_PASSANT_RANK(enemyTeam);

	return RANK_FILE_POINT(pawnRank, (passantFile - 1));
}

bool current_team_move(Info info, uint8_t team)
{
	if(!NORMAL_TEAM_EXISTS(team)) return false;

	return NORMAL_TEAMS_TEAM(INFO_TEAM_MACRO(info), team);
}

void increase_info_turns(Info* info)
{
	uint8_t turns = INFO_TURNS_MACRO(*info);

	*info = ALLOC_TURNS_INFO(*info, (turns + 1));
}

void increase_info_counter(Info* info)
{
	uint8_t counter = INFO_COUNTER_MACRO(*info);

	*info = ALLOC_COUNTER_INFO(*info, (counter + 1));
}

void alloc_passant_point(Info* info, Move move)
{
	uint8_t startFile = MOVE_START_FILE(move);

	*info = ALLOC_PASSANT_INFO(*info, (startFile + 1));
}

void switch_current_team(Info* info)
{
	Info infoEnemy = INFO_TEAM_ENEMY(MASK_INFO_TEAM(*info));

	*info = ALLOC_INFO_TEAM(*info, infoEnemy);
}
