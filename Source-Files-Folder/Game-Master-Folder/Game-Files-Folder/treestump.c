
#include "../Header-Files-Folder/master-include-file.h"

const char MULTI_KEYWORD[] = "multi";
const char SINGLE_KEYWORD[] = "single";
const char CHEAT_KEYWORD[] = "cheat";

int main(int argAmount, char* arguments[])
{
	if(argAmount < 2) return false;

	Screen screen;

	if(!setup_screen_struct(&screen, "treestump", 800, 800))
	{
		printf("Could not setup screen!\n");

		return false;
	}

	Piece* board;
	Info info;

	char* gameString = (argAmount >= 3) ? arguments[2] : (char*) FEN_START_STRING;

	if(!parse_game_string(&board, &info, gameString))
	{
		printf("Could not parse game string!\n");

		return false;
	}

	Move* moves = create_move_array(256);

	bool inverted = false;

	if(strcmp(arguments[1], MULTI_KEYWORD) == 0)
	{
		if(screen_multi_game(board, &info, moves, screen, &inverted))
		{
			if(!game_result_handler(screen, board, info, &inverted))
			{
				printf("if(!game_result_handler(screen, board, info))\n");
			}
		}
	}
	else if(strcmp(arguments[1], SINGLE_KEYWORD) == 0)
	{
		if(screen_single_game(board, &info, moves, screen, &inverted, true))
		{
			if(!game_result_handler(screen, board, info, &inverted))
			{
				printf("if(!game_result_handler(screen, board, info))\n");
			}
		}
	}
	else if(strcmp(arguments[1], CHEAT_KEYWORD) == 0)
	{
		if(screen_cheat_game(board, &info, moves, screen, &inverted))
		{
			if(!game_result_handler(screen, board, info, &inverted))
			{
				printf("if(!game_result_handler(screen, board, info))\n");
			}
		}
	}

	printf("free(board, moves, screen);\n");

	free(board);
	free(moves);
	free_screen_struct(screen);

	return 0;
}
