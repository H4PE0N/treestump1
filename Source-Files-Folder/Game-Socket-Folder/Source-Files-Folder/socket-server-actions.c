
#include "../Header-Files-Folder/socket-include-file.h"

bool send_clients_result(const Client clients[], const Piece board[], State state)
{
  if(!send_update_string(clients, board, state)) return false;

  char resultString[SOCK_STRING_SIZE];
  memset(resultString, '\0', sizeof(resultString));

  if(!create_result_string(resultString, board, state)) return false;

  for(int index = 0; index <= 1; index += 1)
  {
    if(!send_socket_string(clients[index].socket, resultString, SOCK_STRING_SIZE)) return false;
  }
  return true;
}

bool create_result_string(char* string, const Piece board[], State state)
{
  uint8_t winningTeam = STATE_WINNING_TEAM(state);

  if(check_mate_ending(board, state))
  {
    sprintf(string, "%s %s %s", SOCK_QUIT_ACTION, SOCK_STATE_TOKEN, TEAM_WORDS[winningTeam]);
  }
  else if(check_draw_ending(board, state))
  {
    sprintf(string, "%s %s %s", SOCK_QUIT_ACTION, SOCK_STATE_TOKEN, SOCK_DRAW_STATE);
  }
  else return false;

  return true;
}

bool parse_player_string(char* name, char* type, const char string[])
{
  char valString[128];
  memset(valString, '\0', sizeof(valString));

  if(parse_spaced_token(valString, string, SOCK_NAME_TOKEN))
  {
    strcpy(name, valString);
  }
  if(parse_spaced_token(valString, string, SOCK_TYPE_TOKEN))
  {
    strcpy(type, valString);
  }
  return true;
}

bool manage_conct_clients(Client* clients, int serverSock, const char sockAddr[], int sockPort)
{
  for(int index = 0; index <= 1; index += 1)
  {
    if(!accept_conct_client(&clients[index].socket, serverSock, sockAddr, sockPort)) return false;

    if(!handle_conct_client(&clients[index])) return false;
  }
  return send_match_string(clients);
}

bool handle_conct_client(Client* client)
{
  char joinString[SOCK_STRING_SIZE];
  memset(joinString, 0, sizeof(joinString));

  if(!recv_socket_string(client->socket, joinString, SOCK_STRING_SIZE)) return false;

  if(strncmp(joinString, SOCK_JOIN_ACTION, strlen(SOCK_JOIN_ACTION))) return false;

  return parse_player_string(client->name, client->type, joinString);
}

bool send_match_string(const Client clients[])
{
  char matchString[64];
  memset(matchString, 0, sizeof(matchString));

  for(int index = 0; index <= 1; index += 1)
  {
    int oppIndex = !(index);

    sprintf(matchString, "%s %s %s %s %s", SOCK_MATCH_ACTION, SOCK_NAME_TOKEN, clients[oppIndex].name, SOCK_TYPE_TOKEN, clients[oppIndex].type);

    if(!send_socket_string(clients[index].socket, matchString, SOCK_STRING_SIZE)) return false;
  }
  return true;
}

bool send_update_string(const Client clients[], const Piece board[], State state)
{
  char updateString[SOCK_STRING_SIZE];
  memset(updateString, '\0', sizeof(updateString));

  if(!create_update_string(updateString, board, state)) return false;

  for(int index = 0; index <= 1; index += 1)
  {
    if(!send_socket_string(clients[index].socket, updateString, SOCK_STRING_SIZE)) return false;
  }
  return true;
}

bool create_update_string(char* updateString, const Piece board[], State state)
{
  char fenString[128];
  memset(fenString, '\0', sizeof(fenString));

  if(!create_fen_string(fenString, board, state)) return false;

  sprintf(updateString, "%s %s \"%s\"", SOCK_UPDATE_ACTION, SOCK_BOARD_TOKEN, fenString);

  return true;
}

bool send_move_string(int clientSock)
{
  char moveAction[SOCK_STRING_SIZE];
  memset(moveAction, '\0', sizeof(moveAction));

  sprintf(moveAction, "%s", SOCK_MOVE_ACTION);

  return send_socket_string(clientSock, moveAction, SOCK_STRING_SIZE);
}

bool demand_client_move(Move* move, int clientSock, const Piece board[], State state)
{
  Move recvMove = MOVE_NONE;

  char moveString[16];
  memset(moveString, 0, sizeof(moveString));

  while(!move_fully_legal(board, state, recvMove))
  {
    if(!recv_move_string(moveString, clientSock, board, state)) return false;

    parse_string_move(&recvMove, board, state, moveString);
  }
  *move = recvMove; return true;
}

bool parse_string_move(Move* move, const Piece board[], State state, const char string[])
{
  if(!string_basic_move(move, string)) return false;

  return correct_move_flag(move, board, state);
}

bool recv_move_string(char* string, int clientSock, const Piece board[], State state)
{
  if(!send_move_string(clientSock)) return false;

  char recvString[SOCK_STRING_SIZE];
  memset(recvString, 0, sizeof(recvString));

  if(!recv_socket_string(clientSock, recvString, SOCK_STRING_SIZE)) return false;

  if(strncmp(recvString, SOCK_MOVE_ACTION, strlen(SOCK_MOVE_ACTION))) return false;

  return parse_spaced_token(string, recvString, SOCK_MOVE_ACTION);
}
