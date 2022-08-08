
#include "../Engine-Logic-Folder/Header-Files-Folder/englog-include-file.h"
#include "../Game-Screen-Folder/Header-Files-Folder/screen-include-file.h"
#include "../Game-Socket-Folder/Header-Files-Folder/socket-include-file.h"

bool parse_sdlcli_action(int, Screen, Piece*, Info*, const char[]);

bool parse_sdlcli_move(int, Screen, const Piece[], Info, const char[]);

bool client_screen_loop(int, Screen, Piece*, Info*);


int main(int argc, char* argv[])
{
  if(!init_socket_drivers()) return true;

  char sockAddr[] = "192.168.1.113";
  int sockPort = 5555;

  int clientSock;
  if(!create_client_socket(&clientSock, sockAddr, sockPort)) return true;


  Screen screen;
	if(!setup_screen_struct(&screen, "client-screen", 800, 800))
	{
    close_socket_desc(clientSock);
		printf("Could not setup screen!\n");
    return false;
	}


  Piece* board = malloc(sizeof(Piece) * BOARD_LENGTH);
  memset(board, PIECE_NONE, sizeof(Piece) * BOARD_LENGTH);
  Info info;


  if(!client_screen_loop(clientSock, screen, board, &info));


  printf("close_socket_desc(clientSock); free(board); free_screen_struct(screen);\n");
  close_socket_desc(clientSock); free(board); free_screen_struct(screen);

  return false;
}

bool client_screen_loop(int clientSock, Screen screen, Piece* board, Info* info)
{
  char recvString[256];

  Move moves[16];
  memset(moves, MOVE_NONE, sizeof(Move) * 16);

  while(recv_socket_string(clientSock, recvString, sizeof(recvString)))
  {
    printf("server -> %s\n", recvString);

    if(!parse_sdlcli_action(clientSock, screen, board, info, recvString)) return false;

    if(!display_chess_board(screen, board, *info, moves, false)) return false;
  }
  return true;
}

bool parse_sdlcli_action(int clientSock, Screen screen, Piece* board, Info* info, const char string[])
{
  if(!strncmp(string, "update", 6))
    return parse_update_string(board, info, string);

  else if(!strncmp(string, "move", 4))
    return parse_sdlcli_move(clientSock, screen, board, *info, string);

  else if(!strncmp(string, "quit", 4)) return false;

  return false;
}

bool parse_sdlcli_move(int clientSock, Screen screen, const Piece board[], Info info, const char string[])
{
  Move moves[16];
  memset(moves, MOVE_NONE, sizeof(Move) * 16);
  bool inverted = false;

  Move inputMove = MOVE_NONE;
  if(!input_screen_move(&inputMove, screen, board, info, moves, &inverted)) return false;

  char moveString[16];
  if(!create_string_move(moveString, inputMove)) return false;

  char moveSend[256];
  sprintf(moveSend, "move %s", moveString);

  if(!send_socket_string(clientSock, moveSend, sizeof(moveSend))) return false;

  return true;
}
