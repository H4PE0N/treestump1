
#ifndef SOCKET_INCLUDE_FILE_H
#define SOCKET_INCLUDE_FILE_H

#include <unistd.h>
#include <errno.h>
#include <stdbool.h>
#include <stdlib.h>

#include "../../Engine-Logic-Folder/Header-Files-Folder/englog-include-file.h"
#include "../../Chess-Engine-Folder/Header-Files-Folder/engine-include-file.h"
#include "../../Game-Console-Folder/Header-Files-Folder/console-include-file.h"

#if defined(_WIN32) || defined(_WIN64)
#include <winsock2.h>
#include <WS2tcpip.h>

#else
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#endif

#include "game-socket-defines.h"
#include "game-socket-handler.h"
#include "game-socket-actions.h"
#include "socket-server-actions.h"

#endif
