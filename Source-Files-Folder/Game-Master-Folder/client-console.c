
#include "../Engine-Logic-Folder/Header-Files-Folder/englog-include-file.h"
#include "../Game-Console-Folder/Header-Files-Folder/console-include-file.h"
#include "../Game-Socket-Folder/Header-Files-Folder/socket-include-file.h"

bool parse_concli_move(int, Piece*, Info, const char[]);

bool parse_concli_action(int, Piece*, Info*, const char[]);

bool client_console_loop(int, Piece*, Info*);


int main(int argc, char* argv[])
{
  if(!init_socket_drivers()) return true;

  char sockAddr[] = "192.168.1.113";
  int sockPort = 5555;

  int clientSock;
  if(!create_client_socket(&clientSock, sockAddr, sockPort)) return true;


  Piece* board = malloc(sizeof(Piece) * BOARD_LENGTH);
  memset(board, PIECE_NONE, sizeof(Piece) * BOARD_LENGTH);
  Info info;


  if(!client_console_loop(clientSock, board, &info));


  printf("close_socket_desc(clientSock); free(board); \n");
  close_socket_desc(clientSock); free(board);

  return false;
}

bool client_console_loop(int clientSock, Piece* board, Info* info)
{
  char recvString[256];

  while(recv_socket_string(clientSock, recvString, sizeof(recvString)))
  {
    printf("server -> %s\n", recvString);

    if(!parse_concli_action(clientSock, board, info, recvString))
    {
      return false;
    }
    print_console_board(board);
  }
  return true;
}

bool parse_concli_action(int clientSock, Piece* board, Info* info, const char string[])
{
  if(!strncmp(string, "update", 6))
    return parse_update_string(board, info, string);

  else if(!strncmp(string, "move", 4))
    return parse_concli_move(clientSock, board, *info, string);

  else if(!strncmp(string, "quit", 4)) return false;

  return false;
}

bool parse_concli_move(int clientSock, Piece* board, Info info, const char string[])
{
  Move inputMove = MOVE_NONE;
  if(!input_console_move(&inputMove, board, info));

  char moveString[16];
  if(!create_string_move(moveString, inputMove)) return false;

  char moveSend[256];
  sprintf(moveSend, "move %s", moveString);

  if(!send_socket_string(clientSock, moveSend, sizeof(moveSend))) return false;

  return true;
}
