
#include "../Header-Files-Folder/socket-include-file.h"

bool create_server_socket(int* serverSock, const char sockAddr[], int sockPort)
{
  int tempSocket;
  if(!create_socket_struct(&tempSocket, AF_INET, SOCK_STREAM, 0)) return false;

  if(!bind_server_socket(tempSocket, sockAddr, sockPort)) return false;

  if(!server_socket_listen(tempSocket, SOCK_LISTEN_AMOUNT)) return false;

  *serverSock = tempSocket; return true;
}

bool server_socket_listen(int serverSock, int backlog)
{
  return (listen(serverSock, backlog) != LISTEN_ERROR_CODE);
}

bool bind_server_socket(int serverSock, const char sockAddr[], int sockPort)
{
  sockaddr_in addrStruct;
  if(!create_address_struct(&addrStruct, sockAddr, sockPort)) return false;

  bool result = bind(serverSock, (sockaddr*) &addrStruct, sizeof(addrStruct));

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

bool create_client_socket(int* clientSock, const char sockAddr[], int sockPort)
{
  int tempSocket;
  if(!create_socket_struct(&tempSocket, AF_INET, SOCK_STREAM, 0)) return false;

  if(!connect_client_socket(tempSocket, sockAddr, sockPort)) return false;

  *clientSock = tempSocket; return true;
}

bool connect_client_socket(int clientSock, const char sockAddr[], int sockPort)
{
  sockaddr_in addrStruct;
  if(!create_address_struct(&addrStruct, sockAddr, sockPort)) return false;

  bool result = connect(clientSock, (sockaddr*) &addrStruct, sizeof(addrStruct));

  return (result != CONNECT_ERROR_CODE);
}

void close_socket_desc(int sockDesc)
{
  #if defined(_WIN32) || defined(_WIN64)
    closesocket(sockDesc); WSACleanup();
  #else
    close(sockDesc);
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
