
#include "../Chess-Engine-Folder/Header-Files-Folder/engine-include-file.h"
#include "../Game-Console-Folder/Header-Files-Folder/console-include-file.h"

bool console_single_game(Piece*, Info*, bool);

int main(int argc, char* argv[])
{
	char* fenString = (argc >= 2) ? argv[1] : (char*) FEN_START_STRING;

  Piece* board; Info info;
	if(!parse_create_board(&board, &info, fenString))
	{
		printf("Could not parse game string!\n");
    return false;
	}

	if(console_single_game(board, &info, true))
	{
		console_result_handler(board, info);
	}

	printf("free(board);\n");
	free(board);

	return false;
}

bool console_single_game(Piece* board, Info* info, bool starting)
{
	Info userTeam = (starting) ? INFO_TEAM_WHITE : INFO_TEAM_BLACK;
	Info engineTeam = info_team_enemy(userTeam);
	if(engineTeam == INFO_TEAM_NONE) return false;

	while(game_still_running(board, *info))
	{
		Info infoTeam = (*info & INFO_TEAM_MASK);
		if(infoTeam == INFO_TEAM_NONE) return false;

		if(!print_console_board(board)) return false;

		if(infoTeam == userTeam)
		{
			if(!console_user_handler(board, info)) return false;
		}
		else if(infoTeam == engineTeam)
		{
			if(!console_engine_handler(board, info)) return false;
		}
		else return false;
	}
	return true;
}
