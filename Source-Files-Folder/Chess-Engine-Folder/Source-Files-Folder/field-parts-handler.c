
#include "../Header-Files-Folder/engine-include-file.h"

bool normal_team_exists(unsigned short team)
{
	return (team == TEAM_WHITE || team == TEAM_BLACK);
}

unsigned short normal_team_enemy(unsigned short team)
{
	if(team == TEAM_WHITE) return TEAM_BLACK;

	else if(team == TEAM_BLACK) return TEAM_WHITE;

	return TEAM_NONE;
}

bool normal_teams_team(unsigned short firstTeam, unsigned short secondTeam)
{
	bool bothWhite = (firstTeam == TEAM_WHITE && secondTeam == TEAM_WHITE);
	bool bothBlack = (firstTeam == TEAM_BLACK && secondTeam == TEAM_BLACK);

	return (bothWhite || bothBlack);
}

bool normal_teams_enemy(unsigned short firstTeam, unsigned short secondTeam)
{
	bool enemyWhite = (firstTeam == TEAM_BLACK && secondTeam == TEAM_WHITE);
	bool enemyBlack = (firstTeam == TEAM_WHITE && secondTeam == TEAM_BLACK);

	return (enemyWhite || enemyBlack);
}
