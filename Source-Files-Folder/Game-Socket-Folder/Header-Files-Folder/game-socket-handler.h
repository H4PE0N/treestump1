
#ifndef GAME_SOCKET_HANDLER_H
#define GAME_SOCKET_HANDLER_H

bool create_server_socket(int* serverSock, const char sockAddr[], int sockPort);

bool server_socket_listen(int serverSock, int backlog);

bool bind_server_socket(int serverSock, const char sockAddr[], int sockPort);

bool create_socket_struct(int* sockDesc, int domain, int sockType, int protocol);

bool accept_conct_client(int* clientSock, int serverSock, const char sockAddr[], int sockPort);

bool create_address_struct(sockaddr_in* addrStruct, const char sockAddr[], int sockPort);

bool create_client_socket(int* clientSock, const char sockAddr[], int sockPort);

bool connect_client_socket(int clientSock, const char sockAddr[], int sockPort);

void close_socket_desc(int sockDesc);

bool init_socket_drivers();

#endif
