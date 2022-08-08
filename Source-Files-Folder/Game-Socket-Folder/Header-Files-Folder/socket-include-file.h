
#ifndef SOCKET_INCLUDE_FILE_H
#define SOCKET_INCLUDE_FILE_H

#include <unistd.h>
#include <errno.h>
#include <stdbool.h>
#include <stdlib.h>

#if defined(_WIN32) || defined(_WIN64)
  #include <winsock2.h>
  #include <WS2tcpip.h>

#else
  #include <sys/types.h>
  #include <sys/socket.h>
  #include <arpa/inet.h>
  #include <netinet/in.h>

#endif

typedef struct sockaddr_in sockaddr_in;
typedef struct sockaddr sockaddr;

#include "game-socket-handler.h"
#include "game-socket-actions.h"

#endif
