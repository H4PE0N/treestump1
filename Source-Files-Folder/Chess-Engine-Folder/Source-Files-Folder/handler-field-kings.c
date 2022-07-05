
#include "../Header-Files-Folder/engine-include-file.h"

Point team_king_point(Kings kings, unsigned short team)
{
	if(team == TEAM_WHITE) return KINGS_WHITE_MACRO(kings);

	else if(team == TEAM_BLACK) return KINGS_BLACK_MACRO(kings);

	return POINT_NONE;
}
