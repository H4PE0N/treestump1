
#include "../Engine-Logic-Folder/Header-Files-Folder/englog-include-file.h"
#include "../Chess-Engine-Folder/Header-Files-Folder/engine-include-file.h"
#include "../Game-Console-Folder/Header-Files-Folder/console-include-file.h"

bool engine_console_loop(Piece*, State*, Entry* hashTable);

bool parse_coneng_action(Piece*, State*, Entry* hashTable, const char[]);

bool parse_coneng_move(Piece*, State*, Entry* hashTable, const char[]);


int main(int argc, char* argv[])
{
	srand(time(NULL));

	char* fenString = (argc >= 2) ? argv[1] : (char*) FEN_START_STRING;

	if(!extract_score_matrixs(TYPE_SCORE_MATRIX)) return false;

	create_zobrist_keys(&ZOBRIST_KEYS);

	Piece* board; State state;
	if(!parse_create_board(&board, &state, fenString)) return false;

	Entry* hashTable = create_hash_table(HASH_TABLE_SIZE);


  engine_console_loop(board, &state, hashTable);


  printf("free(hashTable);\n"); free(hashTable);

	printf("free(board);\n"); free(board);

	return false;
}

bool engine_console_loop(Piece* board, State* state, Entry* hashTable)
{
  char inputString[256];

  while(strcmp(inputString, "quit"))
  {
    if(!print_console_board(board));

    if(!input_stdin_string(inputString, "input -> ")) return false;

    if(!parse_coneng_action(board, state, hashTable, inputString)) return false;
  }
  return true;
}

bool parse_coneng_action(Piece* board, State* state, Entry* hashTable, const char string[])
{
  if(!strncmp(string, "update", 6))
    return parse_update_string(board, state, string);

  else if(!strncmp(string, "move", 4))
    return parse_coneng_move(board, state, hashTable, string);

  else if(!strncmp(string, "quit", 4)) return false;

  return false;
}

bool parse_coneng_move(Piece* board, State* state, Entry* hashTable, const char string[])
{
	int depth = -1, mtime = -1;

	char* valString = create_char_string(256);

  if(parse_spaced_token(valString, string, "depth"))
  {
		depth = atoi(valString);
    printf("detph=[%d]\n", depth);
  }
  if(parse_spaced_token(valString, string, "mtime"))
  {
		mtime = atoi(valString);
    printf("mtime=[%d]\n", mtime);
  }
  free(valString);







	if(depth == -1)
	{
		depth = 4;
	}





	Move engineMove = MOVE_NONE;

	printf("moving depth=%d mtime=%d\n", depth, mtime);



	long startTime = clock();

	if(mtime == -1)
	{
		if(!engine_depth_move(&engineMove, board, *state, hashTable, depth)) return false;
	}
	else
	{
		int seconds = mtime / 1000;
		if(!optimal_depth_move(&engineMove, board, *state, hashTable, seconds)) return false;
	}

	double time = time_passed_since(startTime);



	char moveString[16];
	memset(moveString, '\n', sizeof(moveString));

	create_string_move(moveString, engineMove);

	printf("move %s time %.2f\n", moveString, time);

	if(!move_chess_piece(board, state, engineMove))
	{
		printf("move_chess_piece\n");

		return false;
	}

  return true;
}
