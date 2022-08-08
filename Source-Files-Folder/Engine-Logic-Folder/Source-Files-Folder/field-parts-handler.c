
#include "../Header-Files-Folder/englog-include-file.h"

bool normal_team_exists(unsigned short team)
{
	return (team == TEAM_WHITE || team == TEAM_BLACK);
}

unsigned short normal_team_enemy(unsigned short team)
{
	if(team == TEAM_WHITE) return TEAM_BLACK;
	if(team == TEAM_BLACK) return TEAM_WHITE;

	return TEAM_NONE;
}

bool normal_teams_team(unsigned short team1, unsigned short team2)
{
	bool bothWhite = (team1 == TEAM_WHITE && team2 == TEAM_WHITE);
	bool bothBlack = (team1 == TEAM_BLACK && team2 == TEAM_BLACK);

	return (bothWhite || bothBlack);
}

bool normal_teams_enemy(unsigned short team1, unsigned short team2)
{
	bool enemyWhite = (team1 == TEAM_BLACK && team2 == TEAM_WHITE);
	bool enemyBlack = (team1 == TEAM_WHITE && team2 == TEAM_BLACK);

	return (enemyWhite || enemyBlack);
}
