
#include "../Chess-Engine-Folder/Header-Files-Folder/engine-include-file.h"
#include "../Game-Screen-Folder/Header-Files-Folder/screen-include-file.h"
#include "../Engine-Logic-Folder/Header-Files-Folder/englog-include-file.h"

bool screen_single_game(Piece*, State*, Entry* hashTable, Move*, Screen*, bool);

int main(int argc, char* argv[])
{
	Screen screen;
	if(!setup_screen_struct(&screen, "single-screen", 800, 800))
	{
		printf("Could not setup screen!\n");
    return false;
	}


	srand(time(NULL));

	if(!extract_score_matrixs(TYPE_SCORE_MATRIX)) return false;

	create_zobrist_keys(&ZOBRIST_KEYS);

	char* fenString = (argc >= 2) ? argv[1] : (char*) FEN_START_STRING;

	Piece* board; State state;
	if(!parse_create_board(&board, &state, fenString)) return false;

	Entry* hashTable = create_hash_table(HASH_TABLE_SIZE);


	Move* moves = create_move_array(256);

	if(screen_single_game(board, &state, hashTable, moves, &screen, true))
	{
		screen_result_handler(&screen, board, state);
	}


	printf("free(hashTable);\n"); free(hashTable);

	printf("free(board);\n"); free(board);

	printf("free(moves);\n"); free(moves);

	printf("free(screen);\n"); free_screen_struct(screen);

	return false;
}

bool screen_single_game(Piece* board, State* state, Entry* hashTable, Move* moves, Screen* screen, bool starting)
{
	uint8_t userTeam = (starting) ? TEAM_WHITE : TEAM_BLACK;

	char fenString[256];

	while(game_still_running(board, *state))
	{
		memset(fenString, '\0', 256);
		if(create_fen_string(fenString, board, *state)) printf("\"%s\"\n", fenString);

		uint8_t currentTeam = STATE_CURRENT_MACRO(*state);

		if(!display_chess_board(*screen, board, *state, moves)) return false;

		if(currentTeam == userTeam)
		{
			if(!screen_user_handler(board, state, moves, screen)) return false;
		}
		else if(!screen_engine_handler(board, state, hashTable, moves, *screen)) return false;
	}
	return true;
}
