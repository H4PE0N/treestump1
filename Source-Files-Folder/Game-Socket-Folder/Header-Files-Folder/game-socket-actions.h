
#ifndef GAME_SOCKET_ACTIONS_H
#define GAME_SOCKET_ACTIONS_H

bool recv_socket_string(int sockDesc, char* string, int length);

bool send_socket_string(int sockDesc, char string[], int length);

#endif
