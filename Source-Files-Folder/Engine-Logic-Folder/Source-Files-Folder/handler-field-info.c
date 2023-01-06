
#include "../Header-Files-Folder/englog-include-file.h"

Point passant_pawn_point(Info info)
{
	unsigned short passantFile = INFO_PASSANT_MACRO(info);
	if(passantFile == 0) return POINT_NONE;


	unsigned short currentTeam = INFO_TEAM_MACRO(info);
	if(currentTeam == TEAM_NONE) return POINT_NONE;

	unsigned short enemyTeam = NORMAL_TEAM_ENEMY(currentTeam);

	short pawnRank = team_passant_rank(enemyTeam);
	if(pawnRank == SHORT_NONE) return POINT_NONE;

	return RANK_FILE_POINT(pawnRank, (passantFile - 1));
}

short team_passant_rank(short team)
{
	if(team == TEAM_WHITE) return (WHITE_PAWN_RANK + WHITE_MOVE_VALUE);
	if(team == TEAM_BLACK) return (BLACK_PAWN_RANK + BLACK_MOVE_VALUE);

	return SHORT_NONE;
}

bool current_team_move(Info info, unsigned short team)
{
	if(!NORMAL_TEAM_EXISTS(team)) return false;

	return NORMAL_TEAMS_TEAM(INFO_TEAM_MACRO(info), team);
}

void increase_info_turns(Info* info)
{
	unsigned short turns = INFO_TURNS_MACRO(*info);

	*info = ALLOC_TURNS_INFO(*info, (turns + 1));
}

void increase_info_counter(Info* info)
{
	unsigned short counter = INFO_COUNTER_MACRO(*info);

	*info = ALLOC_COUNTER_INFO(*info, (counter + 1));
}

void alloc_passant_point(Info* info, Move move)
{
	unsigned short startFile = MOVE_START_FILE(move);

	*info = ALLOC_PASSANT_INFO(*info, (startFile + 1));
}

void switch_current_team(Info* info)
{
	Info infoEnemy = INFO_TEAM_ENEMY(MASK_INFO_TEAM(*info));

	*info = ALLOC_INFO_TEAM(*info, infoEnemy);
}
