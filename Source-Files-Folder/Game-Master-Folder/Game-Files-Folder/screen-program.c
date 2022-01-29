
#include "../Header-Files-Folder/master-include-file.h"

const char MULTI_KEYWORD[] = "multi";
const char SINGLE_KEYWORD[] = "single";

int main(int argAmount, char* arguments[])
{
	if(argAmount < 2) return false;

	if(strcmp(arguments[1], MULTI_KEYWORD) != 0 && strcmp(arguments[1], SINGLE_KEYWORD) != 0) return false;


	Screen screen;

	screen.width = 800;
	screen.height = 800;

	if(!setup_display_screen(&screen, "treestump\0"))
	{
		printf("Could not setup screen!\n");

		return false;
	}

	Piece* board;
	Info info;
	Kings kings;

	char* gameString = (argAmount >= 3) ? arguments[2] : (char*) DEFAULT_STRING;

	if(!parse_game_string(&board, &info, &kings, gameString))
	{
		printf("Could not parse game string!\n");

		return false;
	}

	Move* moves = create_move_array(256);

	if(strcmp(arguments[1], MULTI_KEYWORD) == 0)
	{
		if(screen_multi_game(board, &info, &kings, moves, screen))
		{
			if(!game_result_handler(screen, board, info, kings))
			{
				printf("if(!game_result_handler(screen, board, info, kings))\n");
			}
		}
	}
	else if(strcmp(arguments[1], SINGLE_KEYWORD) == 0)
	{
		if(screen_single_game(board, &info, &kings, moves, screen))
		{
			if(!game_result_handler(screen, board, info, kings))
			{
				printf("if(!game_result_handler(screen, board, info, kings))\n");
			}
		}
	}

	printf("free(board);\nfree(moves);\nfree_display_screen(screen);\n");

	free(board);
	free(moves);
	free_display_screen(screen);

	return 0;
}
