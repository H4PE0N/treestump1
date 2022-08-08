
#include "../Header-Files-Folder/socket-include-file.h"

bool create_server_socket(int* serverSock, const char sockAddr[], int sockPort)
{
  int tempSocket;
  if(!create_socket_struct(&tempSocket, AF_INET, SOCK_STREAM, 0)) return false;

  if(!bind_server_socket(tempSocket, sockAddr, sockPort)) return false;

  if(!server_socket_listen(tempSocket, 5)) return false;

  *serverSock = tempSocket; return true;
}

bool server_socket_listen(int serverSock, int backlog)
{
  return listen(serverSock, backlog) != -1;
}

bool bind_server_socket(int serverSock, const char sockAddr[], int sockPort)
{
  sockaddr_in addrStruct;
  if(!create_address_struct(&addrStruct, sockAddr, sockPort)) return false;

  return bind(serverSock, (sockaddr*) &addrStruct, sizeof(addrStruct)) != -1;
}

bool create_socket_struct(int* sockDesc, int domain, int sockType, int protocol)
{
  return (*sockDesc = socket(domain, sockType, protocol)) != -1;
}

bool accept_conct_client(int* clientSock, int serverSock, const char sockAddr[], int sockPort)
{
  sockaddr_in addrStruct;
  if(!create_address_struct(&addrStruct, sockAddr, sockPort)) return false;

  int addrSize = sizeof(addrStruct);

  int tempSocket = accept(serverSock, (sockaddr*) &addrStruct, (socklen_t*) &addrSize);
  if(tempSocket == -1) return false;

  *clientSock = tempSocket; return true;
}

bool create_address_struct(sockaddr_in* addrStruct, const char sockAddr[], int sockPort)
{
  sockaddr_in tempAddr;

  tempAddr.sin_family = AF_INET; tempAddr.sin_port = htons(sockPort);

  tempAddr.sin_addr.s_addr = inet_addr(sockAddr);

  //if(inet_pton(AF_INET, sockAddr, &tempAddr.sin_addr) != 1) return false;

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

  return connect(clientSock, (sockaddr*) &addrStruct, sizeof(addrStruct)) != -1;
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
  #endif

  return true;
}
