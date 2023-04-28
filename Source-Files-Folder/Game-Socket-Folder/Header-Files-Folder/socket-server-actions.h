
#ifndef SOCKET_SERVER_ACTIONS_H
#define SOCKET_SERVER_ACTIONS_H

bool demand_client_move(Move* move, int clientSock, const Piece board[], State state);

bool manage_conct_clients(Client* clients, int serverSock, const char sockAddr[], int sockPort);

bool handle_conct_client(Client* client);

bool send_update_string(const Client clients[], const Piece board[], State state);

bool create_update_string(char* updateString, const Piece board[], State state);

bool send_move_string(int clientSock);

bool send_match_string(const Client clients[]);

bool send_clients_result(const Client clients[], const Piece board[], State state);

bool create_result_string(char* string, const Piece board[], State state);

bool parse_player_string(char* name, char* type, const char string[]);

bool parse_string_move(Move* move, const Piece board[], State state, const char string[]);

bool recv_move_string(char* string, int clientSock, const Piece board[], State state);

#endif
