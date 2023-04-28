
#include "../Header-Files-Folder/socket-include-file.h"

const unsigned int SOCK_STRING_SIZE = 1024;

const int BIND_ERROR_CODE = -1;
const int SOCKET_ERROR_CODE = -1;
const int ACCEPT_ERROR_CODE = -1;
const int CONNECT_ERROR_CODE = -1;
const int LISTEN_ERROR_CODE = -1;

const unsigned short SOCK_LISTEN_AMOUNT = 5;

const char SOCK_JOIN_ACTION[] = "join";
const char SOCK_QUIT_ACTION[] = "quit";
const char SOCK_UPDATE_ACTION[] = "update";
const char SOCK_MATCH_ACTION[] = "match";
const char SOCK_MOVE_ACTION[] = "move";

const char DEFAULT_ADDR[] = "192.168.1.113";
const int DEFAULT_PORT = 5555;

const char SOCK_NAME_TOKEN[] = "name";
const char SOCK_TYPE_TOKEN[] = "type";
const char SOCK_BOARD_TOKEN[] = "board";
const char SOCK_STATE_TOKEN[] = "state";
const char SOCK_ADDR_TOKEN[] = "address";
const char SOCK_PORT_TOKEN[] = "port";

const char SOCK_DRAW_STATE[] = "draw";

const char CLIENT_TYPE_PLAYER[] = "player";
const char CLIENT_TYPE_ENGINE[] = "engine";
