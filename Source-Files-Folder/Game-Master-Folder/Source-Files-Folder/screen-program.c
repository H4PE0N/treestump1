
#include "../Header-Files-Folder/screen-program.h"

void print_chess_board(const Piece board[])
{
	for(unsigned short rank = 0; rank < BOARD_RANKS; rank += 1)
	{
		for(unsigned short file = 0; file < BOARD_FILES; file += 1)
		{
			Point point = (rank << POINT_RANK_SHIFT) | (file << POINT_FILE_SHIFT);

			Piece piece = board[point];

			unsigned short type = (piece & PIECE_TYPE_MASK) >> PIECE_TYPE_SHIFT;

			char symbol = '.';

			if((piece & PIECE_TEAM_MASK) == PIECE_TEAM_WHITE)
			{
				symbol = WHITE_SYMBOLS[type];
			}
			else if((piece & PIECE_TEAM_MASK) == PIECE_TEAM_BLACK)
			{
				symbol = BLACK_SYMBOLS[type];
			}

			printf("%c ", symbol);
		}
		printf("\n");
	}
}

int main(int argAmount, char* arguments[])
{
	if(argAmount < 2) return false;

	Screen screen;

	screen.width = 800;
	screen.height = 800;

	if(!setup_display_screen(&screen, "treestump\0"))
	{
		printf("Could not setup screen!\n");

		return false;
	}

	Piece* board;
	Info info;

	char* gameString = arguments[1];

	if(!parse_game_string(&board, &info, gameString))
	{
		printf("Could not parse game string!\n");

		return false;
	}

	for(unsigned short index = 0; index < 16; index += 1)
	{
		for(int rank = 0; rank < 8; rank += 1)
		{
			for(int file = 0; file < 8; file++)
			{
				int point = rank * 8 + file;
				printf("%02d ", PIECE_TEAM_MACRO(board[point]));
			}
			printf("\n");
		}

		Info infoTeam = (info & INFO_TEAM_MASK);


		printf("[%d] is moving!\n", infoTeam);

		if(!screen_user_handler(board, &info, screen))
		{
			printf("Abort! Screen!\n");
			break;
		}

		info &= INFO_TEAM_NONE; // Zero'ing the team bits;

		if(infoTeam == INFO_TEAM_WHITE) info |= INFO_TEAM_BLACK;

		if(infoTeam == INFO_TEAM_BLACK) info |= INFO_TEAM_WHITE;

	}

	printf("free(board); free_display_screen(screen);\n");
	free(board);

	free_display_screen(screen);

	return 0;
}

bool screen_user_handler(Piece* board, Info* info, Screen screen)
{
	Move move = MOVE_NONE;

	while(!move_inside_board(move))
	{
		if(!render_chess_board(screen, board, *info, -1))
		{
			printf("if(!render_chess_board(screen, board, *info, -1))\n");

			return false;
		}

		SDL_UpdateWindowSurface(screen.window);

		if(!input_screen_move(&move, screen, board, *info)) return false;
	}

	Point startPoint = MOVE_START_MACRO(move);

	if(!correct_move_flag(&move, board[startPoint], *info))
	{
		return screen_user_handler(board, info, screen);
	}

	if(!move_chess_piece(board, info, move))
	{
		return screen_user_handler(board, info, screen);
	}

	return true;
}

bool input_screen_move(Move* move, Screen screen, const Piece board[], Info info)
{
	Move inputMove = MOVE_NONE;
	Event event;

	while(!move_inside_board(inputMove))
	{
		if(!SDL_PollEvent(&event)) continue;

		if(event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_q))
		{
			printf("Quitting inpu!\n");
		  return false;
		}
		else if(!screen_move_parser(&inputMove, screen, board, info, event)) continue;
	}

	*move = inputMove;

	return true;
}

bool screen_move_parser(Move* move, Screen screen, const Piece board[], Info info, Event event)
{

	if(event.type == SDL_MOUSEBUTTONDOWN)
	{
		Point startPoint = parse_mouse_point(event, screen);


		if(!render_chess_board(screen, board, info, startPoint)) return false;

		SDL_UpdateWindowSurface(screen.window);


		Event upEvent;

		while(upEvent.type != SDL_MOUSEBUTTONUP)
		{
			SDL_PollEvent(&upEvent);
		}

		Point stopPoint = parse_mouse_point(upEvent, screen);

		*move = 0;
		*move |= (startPoint << MOVE_START_SHIFT) & MOVE_START_MASK;
		*move |= (stopPoint << MOVE_STOP_SHIFT) & MOVE_STOP_MASK;

		return true;
	}

	return false;
}

Point parse_mouse_point(Event event, Screen screen)
{
  	float squareWidth = (screen.width / BOARD_FILES);
	float squareHeight = (screen.height / BOARD_RANKS);

	unsigned short file = (unsigned short) floor( (float) event.motion.x / squareWidth);
	unsigned short rank = (unsigned short) floor( (float) event.motion.y / squareHeight);

	if(!NUMBER_IN_BOUNDS(file, 0, BOARD_FILES)) return POINT_NONE;

	if(!NUMBER_IN_BOUNDS(rank, 0, BOARD_RANKS)) return POINT_NONE;

	Point point = 0;
	point |= (file << POINT_FILE_SHIFT) & POINT_FILE_MASK;
	point |= (rank << POINT_RANK_SHIFT) & POINT_RANK_MASK;

	return point;
}
