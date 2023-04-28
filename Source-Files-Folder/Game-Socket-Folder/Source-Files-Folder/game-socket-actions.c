
#include "../Header-Files-Folder/socket-include-file.h"

bool recv_socket_string(int socket, char* string, int length)
{
  return (recv(socket, string, length, 0) > 0);
}

bool send_socket_string(int socket, char string[], int length)
{
  return (send(socket, string, length, MSG_NOSIGNAL) > 0);
}

bool parse_socket_setup(char* sockAddr, int* sockPort, const char string[])
{
  char valString[128];
  memset(valString, '\0', sizeof(valString));

  if(parse_spaced_token(valString, string, SOCK_ADDR_TOKEN))
  {
    sockAddr = strcpy(sockAddr, valString);
  }
  if(parse_spaced_token(valString, string, SOCK_PORT_TOKEN))
  {
    *sockPort = atoi(valString);
  }
  return true;
}

bool input_socket_setup(char* sockAddr, int* sockPort)
{
  char setupString[256];
  memset(setupString, 0, sizeof(setupString));

  input_stdin_string(setupString, SOCKET_SETUP_PROMPT);

  if(!parse_socket_setup(sockAddr, sockPort, setupString)) return false;

  socket_setup_blanks(sockAddr, sockPort); return true;
}

void socket_setup_blanks(char* sockAddr, int* sockPort)
{
  if(strlen(sockAddr) <= 0) sockAddr = strcpy(sockAddr, DEFAULT_ADDR);

  if(*sockPort <= 0) *sockPort = DEFAULT_PORT;
}

bool send_joining_string(int socket, const char name[], const char type[])
{
  char joinString[64];
  memset(joinString, 0, sizeof(joinString));

  sprintf(joinString, "%s %s %s %s %s", SOCK_JOIN_ACTION, SOCK_NAME_TOKEN, name, SOCK_TYPE_TOKEN, type);

  return send_socket_string(socket, joinString, SOCK_STRING_SIZE);
}

bool recv_match_opponent(char* name, char* type, int socket)
{
  char matchString[SOCK_STRING_SIZE];
  memset(matchString, 0, sizeof(matchString));

  if(!recv_socket_string(socket, matchString, SOCK_STRING_SIZE)) return false;

  printf("server: (%s)\n", matchString);

  return parse_player_string(name, type, matchString);
}
