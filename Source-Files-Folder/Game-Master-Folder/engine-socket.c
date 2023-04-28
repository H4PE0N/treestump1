
#include "../Engine-Logic-Folder/Header-Files-Folder/englog-include-file.h"
#include "../Chess-Engine-Folder/Header-Files-Folder/engine-include-file.h"
#include "../Game-Console-Folder/Header-Files-Folder/console-include-file.h"
#include "../Game-Socket-Folder/Header-Files-Folder/socket-include-file.h"

bool engine_console_loop(int, Piece*, State*);

bool parse_soceng_action(int, Piece*, State*, const char[]);

bool parse_soceng_move(int, const Piece[], State, const char[]);


int main(int argc, char* argv[])
{
  if(!init_socket_drivers()) return true;

  char sockAddr[] = "192.168.1.113";
  int sockPort = 5555;

  int clientSock;
  if(!create_client_socket(&clientSock, sockAddr, sockPort)) return true;

  char joinString[256] = "join name treestump type engine";
  send_socket_string(clientSock, joinString, SOCK_STRING_SIZE);


  Piece* board = malloc(sizeof(Piece) * BOARD_POINTS);
  memset(board, PIECE_NONE, sizeof(Piece) * BOARD_POINTS);
  State state;


  if(!engine_console_loop(clientSock, board, &state));


  printf("close_socket_desc(clientSock); free(board); \n");
  close_socket_desc(clientSock); free(board);

  return false;
}

bool engine_console_loop(int clientSock, Piece* board, State* state)
{
  char recvString[SOCK_STRING_SIZE];

  while(recv_socket_string(clientSock, recvString, SOCK_STRING_SIZE))
  {
    printf("server -> %s\n", recvString);

    if(!parse_soceng_action(clientSock, board, state, recvString))
    {
      return false;
    }
    print_console_board(board);
  }
  return true;
}

bool parse_soceng_action(int clientSock, Piece* board, State* state, const char string[])
{
  if(!strncmp(string, "update", 6))
    return parse_update_string(board, state, string);

  else if(!strncmp(string, "move", 4))
    return parse_soceng_move(clientSock, board, *state, string);

  else if(!strncmp(string, "quit", 4)) return false;

  return false;
}

bool parse_soceng_move(int clientSock, const Piece board[], State state, const char string[])
{
	int depth = -1, mtime = -1;

	char* valString = create_char_string(256);

  if(parse_spaced_token(valString, string, "depth"))
  {
		depth = atoi(valString);
    printf("detph=[%d]\n", depth);
  }
  if(parse_spaced_token(valString, string, "mtime"))
  {
		mtime = atoi(valString);
    printf("mtime=[%d]\n", mtime);
  }
  free(valString);







	if(depth == -1 && mtime == -1)
	{
		mtime = 2000;
	}





	unsigned short team = STATE_CURRENT_MACRO(state);
	Move engineMove = MOVE_NONE;

	printf("moving depth=%d mtime=%d\n", depth, mtime);

	if(mtime == -1)
	{
		if(!engine_depth_move(&engineMove, board, state, team, depth)) return false;
	}
	else
	{
		int seconds = mtime / 1000;
		if(!optimal_depth_move(&engineMove, board, state, team, seconds)) return false;
	}



  char moveString[16];
  if(!create_string_move(moveString, engineMove)) return false;

  char moveSend[SOCK_STRING_SIZE];
  sprintf(moveSend, "move %s", moveString);

  if(!send_socket_string(clientSock, moveSend, SOCK_STRING_SIZE)) return false;



  return true;
}
