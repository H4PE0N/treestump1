
#include "../Engine-Logic-Folder/Header-Files-Folder/englog-include-file.h"
#include "../Chess-Engine-Folder/Header-Files-Folder/engine-include-file.h"
#include "../Game-Console-Folder/Header-Files-Folder/console-include-file.h"

bool engine_console_loop(Piece*, Info*);

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
