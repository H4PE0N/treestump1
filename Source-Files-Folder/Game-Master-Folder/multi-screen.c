
#include "../Engine-Logic-Folder/Header-Files-Folder/englog-include-file.h"
#include "../Game-Screen-Folder/Header-Files-Folder/screen-include-file.h"

bool screen_multi_game(Piece*, Info*, Move*, Screen*);

int main(int argAmount, char* arguments[])
{
	Screen screen;
	if(!setup_screen_struct(&screen, "multi-screen", 800, 800))
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

	if(screen_multi_game(board, &info, moves, &screen))
	{
		screen_result_handler(&screen, board, info);
	}

	printf("free(board, moves, screen);\n");
	free(board); free(moves); free_screen_struct(screen);

	return false;
}

bool screen_multi_game(Piece* board, Info* info, Move* moves, Screen* screen)
{
	while(game_still_running(board, *info))
	{
		Info infoTeam = (*info & INFO_TEAM_MASK);
		if(infoTeam == INFO_TEAM_NONE) return false;

		if(!display_chess_board(*screen, board, *info, moves)) return false;

		if(!screen_user_handler(board, info, moves, screen)) return false;
	}
	return true;
}
