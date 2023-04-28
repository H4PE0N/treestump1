
#ifndef GAME_SOCKET_DEFINES_H
#define GAME_SOCKET_DEFINES_H

typedef struct sockaddr_in sockaddr_in;
typedef struct sockaddr sockaddr;

#ifndef MSG_NOSIGNAL
#define MSG_NOSIGNAL 0
#endif

typedef struct Client
{
  int socket;
  char name[32];
  char type[32];
} Client;

extern const unsigned int SOCK_STRING_SIZE;

extern const int BIND_ERROR_CODE;
extern const int SOCKET_ERROR_CODE;
extern const int ACCEPT_ERROR_CODE;
extern const int CONNECT_ERROR_CODE;
extern const int LISTEN_ERROR_CODE;

extern const unsigned short SOCK_LISTEN_AMOUNT;

extern const char SOCK_JOIN_ACTION[];
extern const char SOCK_QUIT_ACTION[];
extern const char SOCK_UPDATE_ACTION[];
extern const char SOCK_MATCH_ACTION[];
extern const char SOCK_MOVE_ACTION[];

extern const char DEFAULT_ADDR[];
extern const int DEFAULT_PORT;

extern const char SOCK_NAME_TOKEN[];
extern const char SOCK_TYPE_TOKEN[];
extern const char SOCK_ADDR_TOKEN[];
extern const char SOCK_PORT_TOKEN[];
extern const char SOCK_STATE_TOKEN[];
extern const char SOCK_BOARD_TOKEN[];

extern const char SOCK_DRAW_STATE[];

extern const char CLIENT_TYPE_PLAYER[];
extern const char CLIENT_TYPE_ENGINE[];

#endif
