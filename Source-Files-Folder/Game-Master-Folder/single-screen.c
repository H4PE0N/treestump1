
#include "../Chess-Engine-Folder/Header-Files-Folder/engine-include-file.h"
#include "../Game-Screen-Folder/Header-Files-Folder/screen-include-file.h"
#include "../Engine-Logic-Folder/Header-Files-Folder/englog-include-file.h"

bool screen_single_game(Piece*, Info*, Move*, Screen, bool*, bool);

int main(int argAmount, char* arguments[])
{
	Screen screen;
	if(!setup_screen_struct(&screen, "single-screen", 800, 800))
	{
		printf("Could not setup screen!\n");
    return false;
	}

	char* fenString = (argAmount >= 2) ? arguments[1] : (char*) FEN_START_STRING;

  Piece* board; Info info;
	if(!parse_create_board(&board, &info, fenString))
	{
		printf("Could not parse game string!\n");
    free_screen_struct(screen); return false;
	}

	Move* moves = create_move_array(256);
	bool inverted = false;

	if(screen_single_game(board, &info, moves, screen, &inverted, true))
	{
		screen_result_handler(screen, board, info, &inverted);
	}

	printf("free(board, moves, screen);\n");
	free(board); free(moves); free_screen_struct(screen);

	return false;
}

bool screen_single_game(Piece* board, Info* info, Move* moves, Screen screen, bool* inverted, bool starting)
{
	Info userTeam = (starting) ? INFO_TEAM_WHITE : INFO_TEAM_BLACK;
	Info engineTeam = info_team_enemy(userTeam);
	if(engineTeam == INFO_TEAM_NONE) return false;

	while(game_still_running(board, *info))
	{
		Info infoTeam = (*info & INFO_TEAM_MASK);
		if(infoTeam == INFO_TEAM_NONE) return false;

		if(!display_chess_board(screen, board, *info, moves, *inverted)) return false;

		if(infoTeam == userTeam)
		{
			if(!screen_user_handler(board, info, moves, screen, inverted)) return false;
		}
		else if(infoTeam == engineTeam)
		{
			if(!screen_engine_handler(board, info, moves, screen)) return false;
		}
		else return false;
	}
	return true;
}
