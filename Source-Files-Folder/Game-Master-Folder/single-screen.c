
#include "../Chess-Engine-Folder/Header-Files-Folder/engine-include-file.h"
#include "../Game-Screen-Folder/Header-Files-Folder/screen-include-file.h"
#include "../Engine-Logic-Folder/Header-Files-Folder/englog-include-file.h"

bool screen_single_game(Piece*, Info*, Entry* hashTable, Move*, Screen*, bool);

int main(int argc, char* argv[])
{
	Screen screen;
	if(!setup_screen_struct(&screen, "single-screen", 800, 800))
	{
		printf("Could not setup screen!\n");
    return false;
	}

	srand(time(NULL));

	char* fenString = (argc >= 2) ? argv[1] : (char*) FEN_START_STRING;

	if(!extract_score_matrixs(TYPE_SCORE_MATRIX)) return false;

	create_hash_matrix(HASH_MATRIX);

	Piece* board; Info info;
	if(!parse_create_board(&board, &info, fenString)) return false;

	Entry* hashTable = create_hash_table(HASH_TABLE_SIZE);



	Move* moves = create_move_array(256);

	if(screen_single_game(board, &info, hashTable, moves, &screen, true))
	{
		screen_result_handler(&screen, board, info);
	}


	printf("free(hashTable);\n"); free(hashTable);

	printf("free(board, moves, screen);\n");
	free(board); free(moves); free_screen_struct(screen);

	return false;
}

bool screen_single_game(Piece* board, Info* info, Entry* hashTable, Move* moves, Screen* screen, bool starting)
{
	Info userTeam = (starting) ? INFO_TEAM_WHITE : INFO_TEAM_BLACK;
	Info engineTeam = INFO_TEAM_ENEMY(userTeam);
	if(engineTeam == INFO_TEAM_NONE) return false;

	while(game_still_running(board, *info))
	{
		Info infoTeam = (*info & INFO_TEAM_MASK);
		if(infoTeam == INFO_TEAM_NONE) return false;

		if(!display_chess_board(*screen, board, *info, moves)) return false;

		if(infoTeam == userTeam)
		{
			if(!screen_user_handler(board, info, moves, screen)) return false;
		}
		else if(infoTeam == engineTeam)
		{
			if(!screen_engine_handler(board, info, hashTable, moves, *screen)) return false;
		}
		else return false;
	}
	return true;
}
