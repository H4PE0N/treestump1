
#ifndef GAME_SOCKET_ACTIONS_H
#define GAME_SOCKET_ACTIONS_H

bool recv_socket_string(int socket, char* string, int length);

bool send_socket_string(int socket, char string[], int length);

bool parse_socket_setup(char* sockAddr, int* sockPort, const char string[]);

bool input_socket_setup(char* sockAddr, int* sockPort);

void socket_setup_blanks(char* sockAddr, int* sockPort);

bool send_joining_string(int socket, const char name[], const char type[]);

bool recv_match_opponent(char* name, char* type, int socket);

#endif
