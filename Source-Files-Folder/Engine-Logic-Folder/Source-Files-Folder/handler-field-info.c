
#include "../Header-Files-Folder/englog-include-file.h"

Point passant_pawn_point(Info info)
{
	unsigned short passantFile = INFO_PASSANT_MACRO(info);
	if(passantFile == 0) return POINT_NONE;


	unsigned short currentTeam = INFO_TEAM_MACRO(info);
	if(currentTeam == TEAM_NONE) return POINT_NONE;

	unsigned short enemyTeam = NORMAL_TEAM_ENEMY(currentTeam);


	unsigned short pawnRank = 0;

	if(enemyTeam == TEAM_WHITE) pawnRank = (WHITE_PAWN_RANK + WHITE_MOVE_VALUE);
	else if(enemyTeam == TEAM_BLACK) pawnRank = (BLACK_PAWN_RANK + BLACK_MOVE_VALUE);

	return RANK_FILE_POINT(pawnRank, (passantFile - 1));
}

bool current_team_move(Info info, unsigned short team)
{
	if(!NORMAL_TEAM_EXISTS(team)) return false;

	return NORMAL_TEAMS_TEAM(INFO_TEAM_MACRO(info), team);
}

bool increase_info_turns(Info* info)
{
	unsigned short turns = INFO_TURNS_MACRO(*info);

	if(INFO_STORE_TEAM(*info, INFO_TEAM_WHITE)) return true;

	if(!INFO_STORE_TEAM(*info, INFO_TEAM_BLACK)) return false;

	*info = ALLOC_TURNS_INFO(*info, (turns + 1)); return true;
}

bool switch_current_team(Info* info)
{
	Info infoEnemy = INFO_TEAM_ENEMY(MASK_INFO_TEAM(*info));

	if(!INFO_TEAM_EXISTS(infoEnemy)) return false;

	*info = ALLOC_INFO_TEAM(*info, infoEnemy); return true;
}
