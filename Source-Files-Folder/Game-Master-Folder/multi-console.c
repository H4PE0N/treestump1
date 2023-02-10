
#include "../Engine-Logic-Folder/Header-Files-Folder/englog-include-file.h"
#include "../Game-Console-Folder/Header-Files-Folder/console-include-file.h"

bool console_multi_game(Piece*, State*);

int main(int argc, char* argv[])
{
	char* fenString = (argc >= 2) ? argv[1] : (char*) FEN_START_STRING;

  Piece* board; State state;
	if(!parse_create_board(&board, &state, fenString))
	{
		printf("Could not parse game string!\n");
    return false;
	}

	if(console_multi_game(board, &state))
	{
		console_result_handler(board, state);
	}

	printf("free(board);\n");
	free(board);

	return false;
}

bool console_multi_game(Piece* board, State* state)
{
	while(game_still_running(board, *state))
	{
		if(!print_console_board(board)) return false;

		if(!console_user_handler(board, state)) return false;
	}
	return true;
}
