
#include "../Engine-Logic-Folder/Header-Files-Folder/englog-include-file.h"
#include "../Game-Screen-Folder/Header-Files-Folder/screen-include-file.h"
// #include "../Game-Socket-Folder/Header-Files-Folder/socket-include-file.h"

bool parse_sdlcli_action(Piece*, Info*, Screen, const char[]);

bool parse_sdlcli_move(Piece*, Info*, Screen, const char[]);

int main(int argc, char* argv[])
{
  return false;
}

bool parse_sdlcli_action(Piece* board, Info* info, Screen screen, const char string[])
{
  if(!strncmp(string, "update", 6))
    return parse_update_string(board, info, string);

  else if(!strncmp(string, "move", 4))
    return parse_sdlcli_move(board, info, screen, string);

  else if(!strncmp(string, "quit", 4)) return false;

  return false;
}

bool parse_sdlcli_move(Piece* board, Info* info, Screen screen, const char string[])
{
  // Move inputMove = MOVE_NONE;
  // if(!input_screen_move(&inputMove, screen, board, *info, moves, inverted)) return false;
  //
  // char moveString[16];
  // memset(moveString, '\0', sizeof(moveString));
  //
  // printf("move %s\n", moveString);

  // send_socket_thing(inputMove)

  return true;
}
