
#include "../Engine-Logic-Folder/Header-Files-Folder/englog-include-file.h"
#include "../Game-Console-Folder/Header-Files-Folder/console-include-file.h"
#include "../Game-Socket-Folder/Header-Files-Folder/socket-include-file.h"

bool parse_concli_move(int clientSock, Piece* board, State state, const char string[]);

bool parse_concli_action(int clientSock, Piece* board, State* state, const char string[]);

bool client_console_loop(int clientSock, Piece* board, State* state);

bool setup_console_client(int socket, Piece* board, State* state);

// Prevent momory leaks by handling the returns
int main(int argc, char* argv[])
{
  if(!init_socket_drivers()) return true;

  int clientSock;
  if(!create_socket_struct(&clientSock, AF_INET, SOCK_STREAM, 0)) return false;

  Piece* board = malloc(sizeof(Piece) * BOARD_POINTS);
  memset(board, PIECE_NONE, sizeof(Piece) * BOARD_POINTS);

  State state;


  if(setup_console_client(clientSock, board, &state))
  {
    client_console_loop(clientSock, board, &state);
  }

  close_socket_desc(clientSock); free(board);
  printf("close_socket_desc(clientSock); free(board);\n");

  return false;
}

bool setup_console_client(int clientSock, Piece* board, State* state)
{
  // #############################################################
  char sockAddr[128]; int sockPort = 0;
  memset(sockAddr, 0, sizeof(sockAddr));

  if(!input_socket_setup(sockAddr, &sockPort)) return false;

  if(!ready_client_socket(clientSock, sockAddr, sockPort)) return false;
  // #############################################################

  // #############################################################
  char name[64]; memset(name, 0, sizeof(name));
  if(!force_input_string(name, INPUT_NAME_PROMPT)) return false;

  if(!send_joining_string(clientSock, name, CLIENT_TYPE_PLAYER)) return false;
  // #############################################################

  // #############################################################
  char oppName[256]; char oppType[256];
  memset(oppName, 0, sizeof(oppName));
  memset(oppType, 0, sizeof(oppType));

  if(!recv_match_opponent(oppName, oppType, clientSock)) return false;

  printf(MATCH_AGAINST_PRINT, oppType, oppName);
  // #############################################################

  return true;
}

bool client_console_loop(int clientSock, Piece* board, State* state)
{
  char recvString[SOCK_STRING_SIZE];
  memset(recvString, 0, sizeof(recvString));

  while(recv_socket_string(clientSock, recvString, SOCK_STRING_SIZE))
  {
    if(!parse_concli_action(clientSock, board, state, recvString)) return false;

    if(!print_console_board(board)) return false;

    if(!print_console_state(*state)) return false;
  }
  return true;
}

bool parse_concli_action(int clientSock, Piece* board, State* state, const char string[])
{
  if(!strncmp(string, SOCK_UPDATE_ACTION, 6))
    return parse_update_string(board, state, string);

  else if(!strncmp(string, SOCK_MOVE_ACTION, 4))
    return parse_concli_move(clientSock, board, *state, string);

  else if(!strncmp(string, SOCK_QUIT_ACTION, 4)) return false;

  return false;
}

bool parse_concli_move(int clientSock, Piece* board, State state, const char string[])
{
  Move inputMove = MOVE_NONE;
  if(!input_console_move(&inputMove, board, state)) return false;

  char moveString[16];
  if(!create_string_move(moveString, inputMove)) return false;

  char moveSend[SOCK_STRING_SIZE];
  sprintf(moveSend, "%s %s", SOCK_MOVE_ACTION, moveString);

  return send_socket_string(clientSock, moveSend, SOCK_STRING_SIZE);
}
