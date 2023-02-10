
#include "../Header-Files-Folder/console-include-file.h"

const char CONSOLE_MOVE_PROMT[] = "input move -> ";
const char CONSOLE_QUIT_STRING[] = "quit";

bool input_console_move(Move* move, const Piece board[], State state)
{
  Move inputMove = MOVE_NONE;

  char stringMove[256];
  memset(stringMove, '\0', sizeof(stringMove));

  while(!MOVE_INSIDE_BOARD(inputMove))
  {
    input_stdin_string(stringMove, CONSOLE_MOVE_PROMT);

    if(!strcmp(stringMove, CONSOLE_QUIT_STRING)) return false;

    if(!parse_string_move(&inputMove, stringMove)) continue;
  }
  *move = inputMove; return true;
}

bool input_stdin_string(char* string, const char inputPromt[])
{
  fflush(stdin);
  printf("%s", inputPromt);
  char buffer[1024];
  if(fgets(buffer, sizeof(buffer), stdin) == NULL) return false;
  return sscanf(buffer, "%[^\n]%*c", string);
}
