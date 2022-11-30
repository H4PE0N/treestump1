
#ifndef GAME_SOCKET_DEFINES_H
#define GAME_SOCKET_DEFINES_H

typedef struct sockaddr_in sockaddr_in;
typedef struct sockaddr sockaddr;

#ifndef MSG_NOSIGNAL
#define MSG_NOSIGNAL 0
#endif

extern const unsigned int SOCKET_STR_SIZE;

extern const int BIND_ERROR_CODE;
extern const int SOCKET_ERROR_CODE;
extern const int ACCEPT_ERROR_CODE;
extern const int CONNECT_ERROR_CODE;
extern const int LISTEN_ERROR_CODE;

extern const unsigned short SOCK_LISTEN_AMOUNT;

#endif
