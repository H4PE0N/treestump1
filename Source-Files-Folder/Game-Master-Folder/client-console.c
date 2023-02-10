
#include "../Engine-Logic-Folder/Header-Files-Folder/englog-include-file.h"
#include "../Game-Console-Folder/Header-Files-Folder/console-include-file.h"
#include "../Game-Socket-Folder/Header-Files-Folder/socket-include-file.h"

bool parse_concli_move(int, Piece*, State, const char[]);

bool parse_concli_action(int, Piece*, State*, const char[]);

bool client_console_loop(int, Piece*, State*);


int main(int argc, char* argv[])
{
  char sockAddr[128];
  memset(sockAddr, '\0', sizeof(sockAddr));

  int sockPort = 5555;


  char setupString[256];
  input_stdin_string(setupString, "setup -> ");

  char valString[128];
  memset(valString, '\0', sizeof(valString));


  if(parse_spaced_token(valString, setupString, "address"))
  {
    strcpy(sockAddr, valString);
  }
  else strcpy(sockAddr, "192.168.1.113");

  if(parse_spaced_token(valString, setupString, "port"))
  {
    sockPort = atoi(valString);
  }





  if(!init_socket_drivers()) return true;

  int clientSock;
  if(!create_client_socket(&clientSock, sockAddr, sockPort)) return true;

  char joinString[256] = "join name HampusFridholm type player";
  send_socket_string(clientSock, joinString, SOCKET_STR_SIZE);


  Piece* board = malloc(sizeof(Piece) * BOARD_POINTS);
  memset(board, PIECE_NONE, sizeof(Piece) * BOARD_POINTS);
  State state;


  if(!client_console_loop(clientSock, board, &state));


  printf("close_socket_desc(clientSock); free(board); \n");
  close_socket_desc(clientSock); free(board);

  return false;
}

bool client_console_loop(int clientSock, Piece* board, State* state)
{
  char recvString[SOCKET_STR_SIZE];

  while(recv_socket_string(clientSock, recvString, SOCKET_STR_SIZE))
  {
    printf("server:(%s)\n", recvString);

    if(!parse_concli_action(clientSock, board, state, recvString))
    {
      return false;
    }
    print_console_board(board);
    print_console_state(*state);
  }
  return true;
}

bool parse_concli_action(int clientSock, Piece* board, State* state, const char string[])
{
  if(!strncmp(string, "update", 6))
    return parse_update_string(board, state, string);

  else if(!strncmp(string, "move", 4))
    return parse_concli_move(clientSock, board, *state, string);

  else if(!strncmp(string, "quit", 4)) return false;

  return false;
}

bool parse_concli_move(int clientSock, Piece* board, State state, const char string[])
{
  Move inputMove = MOVE_NONE;
  if(!input_console_move(&inputMove, board, state));

  char moveString[16];
  if(!create_string_move(moveString, inputMove)) return false;

  char moveSend[SOCKET_STR_SIZE];
  sprintf(moveSend, "move %s", moveString);

  if(!send_socket_string(clientSock, moveSend, SOCKET_STR_SIZE)) return false;

  return true;
}
