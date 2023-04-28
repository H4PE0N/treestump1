
#include "../Header-Files-Folder/console-include-file.h"

bool input_console_move(Move* move, const Piece board[], State state)
{
  Move inputMove = MOVE_NONE;

  char stringMove[256];
  memset(stringMove, 0, sizeof(stringMove));

  while(!MOVE_INSIDE_BOARD(inputMove))
  {
    input_stdin_string(stringMove, INPUT_MOVE_PROMPT);

    if(!strcmp(stringMove, CONS_QUIT_ACTION)) return false;

    if(!string_basic_move(&inputMove, stringMove)) continue;
  }
  *move = inputMove; return true;
}

bool input_stdin_string(char* string, const char prompt[])
{
  fflush(stdin);
  printf("%s", prompt);
  char buffer[1024];
  if(fgets(buffer, sizeof(buffer), stdin) == NULL) return false;
  return sscanf(buffer, "%[^\n]%*c", string);
}

char* force_input_string(char* string, const char prompt[])
{
  char inputString[256];
  memset(inputString, 0, sizeof(inputString));

  while(!input_stdin_string(inputString, prompt));

  strcpy(string, inputString); return string;
}
