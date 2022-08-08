
#include "../Engine-Logic-Folder/Header-Files-Folder/englog-include-file.h"
#include "../Chess-Engine-Folder/Header-Files-Folder/engine-include-file.h"
#include "../Game-Console-Folder/Header-Files-Folder/console-include-file.h"

bool engine_console_loop(Piece*, Info*);

bool parse_update_string(Piece*, Info*, const char[]);

bool parse_engine_action(Piece*, Info*, const char[]);

bool parse_engine_move(Piece*, Info*, const char[]);

int main(int argc, char* argv[])
{
	Piece* board = malloc(sizeof(Piece) * BOARD_LENGTH);
  memset(board, PIECE_NONE, sizeof(Piece) * BOARD_LENGTH);

	Info info;

	parse_fen_string(board, &info, FEN_START_STRING);

  engine_console_loop(board, &info);

	printf("free(board);\n");
	free(board);

	return false;
}

bool engine_console_loop(Piece* board, Info* info)
{
  char inputString[256];

  while(strcmp(inputString, "quit"))
  {
    if(!print_console_board(board));

    if(!input_stdin_string(inputString, "input -> ")) return false;

    if(!parse_engine_action(board, info, inputString)) return false;
  }
  return true;
}

bool parse_update_string(Piece* board, Info* info, const char string[])
{
	char* valString = create_char_string(256);

  if(parse_token_fenstr(valString, string, "board"))
  {
    if(!parse_fen_string(board, info, valString));
  }
  if(parse_spaced_token(valString, string, "wtime"))
  {
    printf("wtime=[%d]\n", atoi(valString));
  }
  if(parse_spaced_token(valString, string, "btime"))
  {
    printf("btime=[%d]\n", atoi(valString));
  }
  if(parse_spaced_token(valString, string, "winc"))
  {
    printf("winc=[%d]\n", atoi(valString));
  }
  if(parse_spaced_token(valString, string, "binc"))
  {
    printf("binc=[%d]\n", atoi(valString));
  }
  free(valString); return true;
}

bool parse_engine_action(Piece* board, Info* info, const char string[])
{
  if(!strncmp(string, "update", 6))
  {
    return parse_update_string(board, info, string);
  }
  else if(!strncmp(string, "move", 4))
  {
    return parse_engine_move(board, info, string);
  }
  else if(!strncmp(string, "quit", 4))
  {
    return false;
  }
  return false;
}

bool parse_engine_move(Piece* board, Info* info, const char string[])
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





	unsigned short team = INFO_TEAM_MACRO(*info);
	Move engineMove = MOVE_NONE;

	printf("moving depth=%d mtime=%d\n", depth, mtime);

	if(mtime == -1)
	{
		if(!engine_depth_move(&engineMove, board, *info, team, depth)) return false;
	}
	else
	{
		int seconds = mtime / 1000;
		if(!optimal_depth_move(&engineMove, board, *info, team, seconds)) return false;
	}

	char moveString[16];
	memset(moveString, '\n', sizeof(moveString));

	create_string_move(moveString, engineMove);

	printf("move %s\n", moveString);

	if(!move_chess_piece(board, info, engineMove))
	{
		printf("move_chess_piece\n");

		return false;
	}

  return true;
}

// bool parse_sdlcli_action()
// {
//   return false;
// }
//
// bool parse_sdlcli_move()
// {
//   return false;
// }
//
// bool parse_concli_action()
// {
//   return false;
// }
//
// bool parse_concli_move()
// {
//   return false;
// }
