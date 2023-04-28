
#include "../Chess-Engine-Folder/Header-Files-Folder/engine-include-file.h"
#include "../Game-Socket-Folder/Header-Files-Folder/socket-include-file.h"
#include "../Engine-Logic-Folder/Header-Files-Folder/englog-include-file.h"
#include "../Game-Console-Folder/Header-Files-Folder/console-include-file.h"

bool server_console_loop(const Client clients[], Piece* board, State* state);

bool setup_console_server(int socket, Piece* board, State* state, Client* clients);

// Prevent momory leaks by handling the returns
int main(int argc, char* argv[])
{
  if(!init_socket_drivers()) return true;

  int serverSock;
  if(!create_socket_struct(&serverSock, AF_INET, SOCK_STREAM, 0)) return false;

  Piece* board = malloc(sizeof(Piece) * BOARD_POINTS);
  memset(board, PIECE_NONE, sizeof(Piece) * BOARD_POINTS);

  State state;

  Client clients[2];

  if(setup_console_server(serverSock, board, &state, clients))
  {
    if(server_console_loop(clients, board, &state))
    {
      send_clients_result(clients, board, state);
    }
  }

  close_socket_desc(serverSock); free(board);
  printf("close_socket_desc(serverSock); free(board);\n");

  return false;
}

bool setup_console_server(int serverSock, Piece* board, State* state, Client* clients)
{
  // #############################################################
  if(!parse_fen_string(board, state, FEN_START_STRING)) return false;

  char string[256];
  memset(string, 0, sizeof(string));

  input_stdin_string(string, UPDATE_BOARD_PROMPT);

	if(!parse_update_string(board, state, string)) return false;
  // #############################################################

  // #############################################################
  char sockAddr[128]; int sockPort = 0;
  memset(sockAddr, 0, sizeof(sockAddr));

  if(!input_socket_setup(sockAddr, &sockPort)) return false;

  if(!ready_server_socket(serverSock, sockAddr, sockPort)) return false;

  printf(CREATED_SERVER_PRINT, sockAddr, sockPort);

  if(!manage_conct_clients(clients, serverSock, sockAddr, sockPort)) return false;
  // #############################################################

  return true;
}

bool server_console_loop(const Client clients[], Piece* board, State* state)
{
  while(game_still_running(board, *state))
  {
    if(!print_console_board(board)) return false;

    if(!print_console_state(*state)) return false;

    if(!send_update_string(clients, board, *state)) return false;

    int moveIndex = (STATE_CURRENT_MACRO(*state) == TEAM_WHITE) ? 0 : 1;

    Move recvMove = MOVE_NONE;
    if(!demand_client_move(&recvMove, clients[moveIndex].socket, board, *state)) return false;

    if(!move_chess_piece(board, state, recvMove)) return false;
  }
  return true;
}
