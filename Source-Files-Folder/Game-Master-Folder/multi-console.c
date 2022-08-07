
#include "../Chess-Engine-Folder/Header-Files-Folder/engine-include-file.h"
#include "../Game-Console-Folder/Header-Files-Folder/console-include-file.h"

bool console_multi_game(Piece*, Info*);

int main(int argc, char* argv[])
{
	char* fenString = (argc >= 2) ? argv[1] : (char*) FEN_START_STRING;

  Piece* board; Info info;
	if(!parse_game_string(&board, &info, fenString))
	{
		printf("Could not parse game string!\n");
    return false;
	}

	if(console_multi_game(board, &info))
	{
		console_result_handler(board, info);
	}

	printf("free(board);\n");
	free(board);

	return false;
}

bool console_multi_game(Piece* board, Info* info)
{
	while(game_still_running(board, *info))
	{
		if(!print_console_board(board, *info)) return false;

		if(!console_user_handler(board, info)) return false;
	}
	return true;
}
