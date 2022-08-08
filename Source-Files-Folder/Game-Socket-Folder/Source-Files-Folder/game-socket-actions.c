
#include "../Header-Files-Folder/socket-include-file.h"

bool recv_socket_string(int sockDesc, char* string, int length)
{
  return recv(sockDesc, string, length, 0) > 0;
}

bool send_socket_string(int sockDesc, char string[], int length)
{
  return send(sockDesc, string, length, MSG_NOSIGNAL) > 0;
}
