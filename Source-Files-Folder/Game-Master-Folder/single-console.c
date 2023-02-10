
#include "../Chess-Engine-Folder/Header-Files-Folder/engine-include-file.h"
#include "../Game-Console-Folder/Header-Files-Folder/console-include-file.h"
#include "../Engine-Logic-Folder/Header-Files-Folder/englog-include-file.h"

bool console_single_game(Piece*, State*, bool);

int main(int argc, char* argv[])
{
	char* fenString = (argc >= 2) ? argv[1] : (char*) FEN_START_STRING;

  Piece* board; State state;
	if(!parse_create_board(&board, &state, fenString))
	{
		printf("Could not parse game string!\n");
    return false;
	}

	if(console_single_game(board, &state, true))
	{
		console_result_handler(board, state);
	}

	printf("free(board);\n");
	free(board);

	return false;
}

bool console_single_game(Piece* board, State* state, bool starting)
{
	State userTeam = (starting) ? STATE_TEAM_WHITE : STATE_TEAM_BLACK;
	State engineTeam = state_team_enemy(userTeam);
	if(engineTeam == STATE_TEAM_NONE) return false;

	while(game_still_running(board, *state))
	{
		State stateTeam = (*state & STATE_CURRENT_MASK);
		if(stateTeam == STATE_TEAM_NONE) return false;

		if(!print_console_board(board)) return false;

		if(stateTeam == userTeam)
		{
			if(!console_user_handler(board, state)) return false;
		}
		else if(stateTeam == engineTeam)
		{
			if(!console_engine_handler(board, state)) return false;
		}
		else return false;
	}
	return true;
}
