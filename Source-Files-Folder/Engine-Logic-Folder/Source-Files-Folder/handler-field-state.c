
#include "../Header-Files-Folder/englog-include-file.h"

Point passant_pawn_point(State state)
{
	uint8_t passantFile = STATE_PASSANT_MACRO(state);
	if(passantFile == 0) return POINT_NONE;

	uint8_t currentTeam = STATE_CURRENT_MACRO(state);
	if(currentTeam == TEAM_NONE) return POINT_NONE;

	uint8_t enemyTeam = NORMAL_TEAM_ENEMY(currentTeam);

	uint8_t pawnRank = TEAM_PASSANT_RANK(enemyTeam);

	return RANK_FILE_POINT(pawnRank, (passantFile - 1));
}

bool current_team_move(State state, uint8_t team)
{
	if(!NORMAL_TEAM_EXISTS(team)) return false;

	return NORMAL_TEAMS_TEAM(STATE_CURRENT_MACRO(state), team);
}

void increase_state_turns(State* state)
{
	uint8_t turns = STATE_TURNS_MACRO(*state);

	*state = ALLOC_TURNS_STATE(*state, (turns + 1));
}

void increase_state_clock(State* state)
{
	uint8_t clock = STATE_CLOCK_MACRO(*state);

	*state = ALLOC_CLOCK_STATE(*state, (clock + 1));
}

void alloc_passant_point(State* state, Move move)
{
	uint8_t startFile = MOVE_START_FILE(move);

	*state = ALLOC_PASSANT_STATE(*state, (startFile + 1));
}

void switch_current_team(State* state)
{
	State stateEnemy = STATE_TEAM_ENEMY(MASK_STATE_CURRENT(*state));

	*state = ALLOC_STATE_CURRENT(*state, stateEnemy);
}
