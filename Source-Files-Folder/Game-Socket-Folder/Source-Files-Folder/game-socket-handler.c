
#include "../Header-Files-Folder/socket-include-file.h"

// Protect socket with tempSocket before return
bool create_server_socket(int* socket, const char sockAddr[], int sockPort)
{
  if(!create_socket_struct(socket, AF_INET, SOCK_STREAM, 0)) return false;

  if(ready_server_socket(*socket, sockAddr, sockPort)) return true;

  close_socket_desc(*socket); return false;
}

bool ready_server_socket(int socket, const char sockAddr[], int sockPort)
{
  if(!bind_server_socket(socket, sockAddr, sockPort)) return false;

  return server_socket_listen(socket, SOCK_LISTEN_AMOUNT);
}

bool server_socket_listen(int socket, int backlog)
{
  return (listen(socket, backlog) != LISTEN_ERROR_CODE);
}

bool bind_server_socket(int socket, const char sockAddr[], int sockPort)
{
  sockaddr_in addrStruct;
  if(!create_address_struct(&addrStruct, sockAddr, sockPort)) return false;

  bool result = bind(socket, (sockaddr*) &addrStruct, sizeof(addrStruct));

  return (result != BIND_ERROR_CODE);
}

bool create_socket_struct(int* sockDesc, int domain, int sockType, int protocol)
{
  int tempSocket = socket(domain, sockType, protocol);

  if(tempSocket == SOCKET_ERROR_CODE) return false;

  *sockDesc = tempSocket; return true;
}

bool accept_conct_client(int* clientSock, int serverSock, const char sockAddr[], int sockPort)
{
  sockaddr_in addrStruct;
  if(!create_address_struct(&addrStruct, sockAddr, sockPort)) return false;

  int addrSize = sizeof(addrStruct);

  int tempSocket = accept(serverSock, (sockaddr*) &addrStruct, (socklen_t*) &addrSize);
  if(tempSocket == ACCEPT_ERROR_CODE) return false;

  *clientSock = tempSocket; return true;
}

bool create_address_struct(sockaddr_in* addrStruct, const char sockAddr[], int sockPort)
{
  sockaddr_in tempAddr;

  tempAddr.sin_family = AF_INET; tempAddr.sin_port = htons(sockPort);

  tempAddr.sin_addr.s_addr = inet_addr(sockAddr);

  *addrStruct = tempAddr; return true;
}

// Protect socket with tempSocket before return
bool create_client_socket(int* socket, const char sockAddr[], int sockPort)
{
  if(!create_socket_struct(socket, AF_INET, SOCK_STREAM, 0)) return false;

  if(ready_client_socket(*socket, sockAddr, sockPort)) return true;

  close_socket_desc(*socket); return false;
}

bool ready_client_socket(int socket, const char sockAddr[], int sockPort)
{
  return connect_client_socket(socket, sockAddr, sockPort);
}

bool connect_client_socket(int socket, const char sockAddr[], int sockPort)
{
  sockaddr_in addrStruct;
  if(!create_address_struct(&addrStruct, sockAddr, sockPort)) return false;

  bool result = connect(socket, (sockaddr*) &addrStruct, sizeof(addrStruct));

  return (result != CONNECT_ERROR_CODE);
}

int close_socket_desc(int socket)
{
  #if defined(_WIN32) || defined(_WIN64)
    closesocket(socket); WSACleanup();
  #else
    return close(socket);
  #endif
}

bool init_socket_drivers()
{
  #if defined(_WIN32) || defined(_WIN64)
    WSADATA WSAData;
    return (WSAStartup(MAKEWORD(2, 2), &WSAData) == 0);
  #else
    return true;
  #endif
}
