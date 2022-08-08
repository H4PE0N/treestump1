
#include "../Chess-Engine-Folder/Header-Files-Folder/engine-include-file.h"
#include "../Game-Socket-Folder/Header-Files-Folder/socket-include-file.h"
#include "../Engine-Logic-Folder/Header-Files-Folder/englog-include-file.h"
#include "../Game-Console-Folder/Header-Files-Folder/console-include-file.h"

bool server_console_loop(int, const int[], Piece*, Info*);

bool accept_conct_clients(int*, int, const char[], int);

bool send_update_string(const int[], const Piece[], Info);

bool send_move_string(int);

bool recv_socket_move(Move*, int, const Piece[], Info);


int create_random_number(int minimum, int maximum)
{
  return (minimum + (rand() % (maximum - minimum + 1)));
}

int main(int argc, char* argv[])
{
  if(!init_socket_drivers()) return true;

  char sockAddr[] = "192.168.1.113";
  int sockPort = 5555;

  printf("sockAddr [%s] sockPort [%d]\n", sockAddr, sockPort);

  int serverSock;
  if(!create_server_socket(&serverSock, sockAddr, sockPort))
  {
    printf("could not create server\n");

    return true;
  }

  printf("accept clients..\n");

  int clientSocks[2];
  if(!accept_conct_clients(clientSocks, serverSock, sockAddr, sockPort))
  {
    close_socket_desc(serverSock); return true;
  }

  printf("create board...\n");

  Piece* board;
  Info info;

  if(!parse_create_board(&board, &info, FEN_START_STRING))
  {
    close_socket_desc(serverSock); return true;
  }


  if(!server_console_loop(serverSock, clientSocks, board, &info));


  printf("close_socket_desc(serverSock); free(board);\n");
  close_socket_desc(serverSock); free(board);

  return false;
}

bool accept_conct_clients(int* clientSocks, int serverSock, const char sockAddr[], int sockPort)
{
  for(int index = 0; index < 2; index += 1)
  {
    if(!accept_conct_client(&clientSocks[index], serverSock, sockAddr, sockPort)) return false;
  }
  return true;
}

bool send_update_string(const int clientSocks[], const Piece board[], Info info)
{
  char updateString[256];
  memset(updateString, '\0', sizeof(updateString));

  char fenString[128];
  memset(fenString, '\0', sizeof(fenString));
  if(!create_fen_string(fenString, board, info)) return false;

  sprintf(updateString, "update board \"%s\"", fenString);

  for(int clientIndex = 0; clientIndex < 2; clientIndex += 1)
  {
    if(!send_socket_string(clientSocks[clientIndex], updateString, sizeof(updateString))) return false;
  }
  return true;
}

bool send_move_string(int clientSock)
{
  char moveAction[256];
  memset(moveAction, '\0', sizeof(moveAction));

  sprintf(moveAction, "move");

  if(!send_socket_string(clientSock, moveAction, sizeof(moveAction))) return false;

  return true;
}

bool recv_socket_move(Move* move, int clientSock, const Piece board[], Info info)
{
  Move recvMove = MOVE_NONE;
  while(!move_fully_legal(board, info, recvMove))
  {
    if(!send_move_string(clientSock)) return false;

    char recvString[256];
    if(!recv_socket_string(clientSock, recvString, sizeof(recvString))) return false;

    printf("client -> %s\n", recvString);

    if(!strcmp(recvString, "quit")) return false;

    char moveString[16];
    if(!parse_spaced_token(moveString, recvString, "move")) continue;

    printf("parsing -> [%s]\n", moveString);

    if(!parse_string_move(&recvMove, moveString)) continue;

    if(!correct_move_flag(&recvMove, board, info)) continue;
  }
  *move = recvMove; return true;
}

bool server_console_loop(int serverSock, const int clientSocks[], Piece* board, Info* info)
{
  while(game_still_running(board, *info))
  {
    if(!print_console_board(board)) return false;

    if(!send_update_string(clientSocks, board, *info)) return false;

    int moveIndex = (INFO_TEAM_MACRO(*info) == TEAM_WHITE) ? 0 : 1;

    Move recvMove = MOVE_NONE;
    if(!recv_socket_move(&recvMove, clientSocks[moveIndex], board, *info)) return false;

    if(!move_chess_piece(board, info, recvMove)) return false;
  }
  return true;
}
