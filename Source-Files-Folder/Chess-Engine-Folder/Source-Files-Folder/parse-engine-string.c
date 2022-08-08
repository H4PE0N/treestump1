
#include "../Header-Files-Folder/engine-include-file.h"

bool parse_update_string(Piece* board, Info* info, const char string[])
{
	char valString[256];
  memset(valString, '\0', sizeof(valString));

  if(parse_token_fenstr(valString, string, "board"))
  {
    if(!parse_fen_string(board, info, valString)) return false;
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
  return true;
}
