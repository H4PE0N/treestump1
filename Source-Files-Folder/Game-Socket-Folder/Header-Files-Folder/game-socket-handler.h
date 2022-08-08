
#ifndef GAME_SOCKET_HANDLER_H
#define GAME_SOCKET_HANDLER_H

bool create_server_socket(int*, const char[], int);

bool server_socket_listen(int, int);

bool bind_server_socket(int, const char[], int);

bool create_socket_struct(int*, int, int, int);

bool accept_conct_client(int*, int, const char[], int);

bool create_address_struct(sockaddr_in*, const char[], int);

bool create_client_socket(int*, const char[], int);

bool connect_client_socket(int, const char[], int);

void close_socket_desc(int);

bool init_socket_drivers();

#endif
