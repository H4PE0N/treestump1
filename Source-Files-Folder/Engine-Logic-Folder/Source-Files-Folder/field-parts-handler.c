
#include "../Header-Files-Folder/englog-include-file.h"

bool normal_team_exists(unsigned short team)
{
	return ((team == TEAM_WHITE) || (team == TEAM_BLACK));
}

unsigned short normal_team_enemy(unsigned short team)
{
	if(team == TEAM_WHITE) return TEAM_BLACK;
	if(team == TEAM_BLACK) return TEAM_WHITE;

	return TEAM_NONE;
}

bool normal_teams_team(unsigned short team1, unsigned short team2)
{
	if((team1 == TEAM_WHITE) && (team2 == TEAM_WHITE)) return true;
	if((team1 == TEAM_BLACK) && (team2 == TEAM_BLACK)) return true;

	return false;
}

bool normal_teams_enemy(unsigned short team1, unsigned short team2)
{
	if((team1 == TEAM_BLACK) && (team2 == TEAM_WHITE)) return true;
	if((team1 == TEAM_WHITE) && (team2 == TEAM_BLACK)) return true;

	return false;
}
