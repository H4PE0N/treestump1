
#include "../Chess-Engine-Folder/Header-Files-Folder/engine-include-file.h"
#include "../Game-Socket-Folder/Header-Files-Folder/socket-include-file.h"
#include "../Engine-Logic-Folder/Header-Files-Folder/englog-include-file.h"
#include "../Game-Console-Folder/Header-Files-Folder/console-include-file.h"

bool server_console_loop(const int[], Piece*, Info*);

bool accept_conct_clients(int*, int, const char[], int);

bool send_update_string(const int[], const Piece[], Info);

bool send_move_string(int);

bool recv_socket_move(Move*, int, const Piece[], Info);

bool conser_result_handler(const int[], const Piece[], Info);


int create_random_number(int minimum, int maximum)
{
  return (minimum + (rand() % (maximum - minimum + 1)));
}

int main(int argc, char* argv[])
{
  char sockAddr[128];
  memset(sockAddr, '\0', sizeof(sockAddr));

  int sockPort = 5555;

  char fenString[128];
  memset(fenString, '\0', sizeof(fenString));





  char setupString[256];
  input_stdin_string(setupString, "setup -> ");

  char valString[128];
  memset(valString, '\0', sizeof(valString));



  if(parse_token_quotes(valString, setupString, "board"))
  {
    strcpy(fenString, valString);
  }
  else strcpy(fenString, FEN_START_STRING);

  if(parse_spaced_token(valString, setupString, "address"))
  {
    strcpy(sockAddr, valString);
  }
  else strcpy(sockAddr, "192.168.1.113");

  if(parse_spaced_token(valString, setupString, "port"))
  {
    sockPort = atoi(valString);
  }

  if(parse_spaced_token(valString, setupString, "wtime"))
  {
    printf("wtime:(%d)\n", atoi(valString));
  }
  if(parse_spaced_token(valString, setupString, "btime"))
  {
    printf("btime:(%d)\n", atoi(valString));
  }
  if(parse_spaced_token(valString, setupString, "winc"))
  {
    printf("winc:(%d)\n", atoi(valString));
  }
  if(parse_spaced_token(valString, setupString, "binc"))
  {
    printf("binc:(%d)\n", atoi(valString));
  }



  if(!init_socket_drivers()) return true;

  int serverSock;
  if(!create_server_socket(&serverSock, sockAddr, sockPort))
  {
    printf("could not create server\n");
    return true;
  }
  printf("created server:(%s, %d)\n", sockAddr, sockPort);

  int clientSocks[2];
  if(!accept_conct_clients(clientSocks, serverSock, sockAddr, sockPort))
  {
    close_socket_desc(serverSock); return true;
  }

  Piece* board;
  Info info;

  if(!parse_create_board(&board, &info, fenString))
  {
    close_socket_desc(serverSock); return true;
  }


  if(server_console_loop(clientSocks, board, &info))
  {
    conser_result_handler(clientSocks, board, info);
  }


  printf("close_socket_desc(serverSock); free(board);\n");
  close_socket_desc(serverSock); free(board);

  return false;
}

bool conser_result_handler(const int clientSocks[], const Piece board[], Info info)
{
  if(!send_update_string(clientSocks, board, info)) return false;

  unsigned short team = INFO_TEAM_MACRO(info);
	unsigned short winningTeam = NORMAL_TEAM_ENEMY(team);

  char resultString[SOCKET_STR_SIZE];
  memset(resultString, '\0', sizeof(resultString));

  if(check_mate_ending(board, info, team))
  {
    sprintf(resultString, "quit state %s", TEAM_WORDS[winningTeam]);

    for(int index = 0; index < 2; index += 1)
    {
      if(!send_socket_string(clientSocks[index], resultString, SOCKET_STR_SIZE)) return false;
    }
  }
  else if(check_draw_ending(board, info, team))
  {
    sprintf(resultString, "quit state draw");

    for(int index = 0; index < 2; index += 1)
    {
      if(!send_socket_string(clientSocks[index], resultString, SOCKET_STR_SIZE)) return false;
    }
  }
  else return false;

  return true;
}

bool accept_conct_clients(int* clientSocks, int serverSock, const char sockAddr[], int sockPort)
{
  for(int index = 0; index < 2; index += 1)
  {
    if(!accept_conct_client(&clientSocks[index], serverSock, sockAddr, sockPort)) return false;

    char joinString[SOCKET_STR_SIZE];
    if(!recv_socket_string(clientSocks[index], joinString, SOCKET_STR_SIZE)) return false;

    if(!strncmp(joinString, "join", 4))
    {
      char valString[256];
      memset(valString, '\0', sizeof(valString));

      if(parse_spaced_token(valString, joinString, "name"))
      {
        printf("name:[%s]\n", valString);
      }
      if(parse_spaced_token(valString, joinString, "type"))
      {
        printf("type:[%s]\n", valString);
      }
    }
    else return false;
  }
  return true;
}

bool send_update_string(const int clientSocks[], const Piece board[], Info info)
{
  char updateString[SOCKET_STR_SIZE];
  memset(updateString, '\0', sizeof(updateString));

  char fenString[128];
  memset(fenString, '\0', sizeof(fenString));
  if(!create_fen_string(fenString, board, info)) return false;

  sprintf(updateString, "update board \"%s\"", fenString);

  for(int clientIndex = 0; clientIndex < 2; clientIndex += 1)
  {
    if(!send_socket_string(clientSocks[clientIndex], updateString, SOCKET_STR_SIZE)) return false;
  }
  return true;
}

bool send_move_string(int clientSock)
{
  char moveAction[SOCKET_STR_SIZE];
  memset(moveAction, '\0', sizeof(moveAction));

  sprintf(moveAction, "move");

  if(!send_socket_string(clientSock, moveAction, SOCKET_STR_SIZE)) return false;

  return true;
}

bool recv_socket_move(Move* move, int clientSock, const Piece board[], Info info)
{
  Move recvMove = MOVE_NONE;
  while(!move_fully_legal(board, info, recvMove))
  {
    if(!send_move_string(clientSock)) return false;

    char recvString[SOCKET_STR_SIZE];
    if(!recv_socket_string(clientSock, recvString, SOCKET_STR_SIZE)) return false;

    printf("client:(%s)\n", recvString);

    if(!strcmp(recvString, "quit")) return false;

    char moveString[16];
    if(!parse_spaced_token(moveString, recvString, "move")) continue;

    if(!parse_string_move(&recvMove, moveString)) continue;

    if(!correct_move_flag(&recvMove, board, info)) continue;
  }
  *move = recvMove; return true;
}

bool server_console_loop(const int clientSocks[], Piece* board, Info* info)
{
  while(game_still_running(board, *info))
  {
    if(!print_console_board(board)) return false;
    if(!print_console_info(*info)) return false;

    if(!send_update_string(clientSocks, board, *info)) return false;

    int moveIndex = (INFO_TEAM_MACRO(*info) == TEAM_WHITE) ? 0 : 1;

    Move recvMove = MOVE_NONE;
    if(!recv_socket_move(&recvMove, clientSocks[moveIndex], board, *info))
    {
      printf("player #%d quit!\n", moveIndex + 1);
      return false;
    }

    if(!move_chess_piece(board, info, recvMove)) return false;
  }
  return true;
}
