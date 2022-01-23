
#include "../Header-Files-Folder/screen-program.h"

// "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 1 0"

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
	Kings kings;

	char* gameString = arguments[1];

	if(!parse_game_string(&board, &info, &kings, gameString))
	{
		printf("Could not parse game string!\n");

		return false;
	}

	Move* moves = malloc(sizeof(Move) * 128);

	for(unsigned short index = 0; index < 128; index += 1)
	{
		moves[index] = MOVE_NONE;
	}

	if(screen_single_game(board, &info, &kings, moves, screen))
	{
		if(!render_chess_board(screen, board, info, kings, moves, -1))
		{
			printf("if(!render_chess_board(screen, board, *info, -1))\n");

			return false;
		}

		SDL_UpdateWindowSurface(screen.window);

		unsigned short winnerTeam = normal_team_enemy(INFO_TEAM_MACRO(info));

		printf("Winner is: [%d]\n", winnerTeam);

		SDL_Delay(20000);
	}

	printf("free(board);\nfree(moves);\nfree_display_screen(screen);\n");

	free(board);
	free(moves);
	free_display_screen(screen);

	return 0;
}

bool screen_single_game(Piece* board, Info* info, Kings* kings, Move* moves, Screen screen)
{
	while(game_still_running(board, *info, *kings))
	{

		Info infoTeam = (*info & INFO_TEAM_MASK);

		if(!render_chess_board(screen, board, *info, *kings, moves, -1))
		{
			printf("if(!render_chess_board(screen, board, *info, -1))\n");

			return false;
		}

		SDL_UpdateWindowSurface(screen.window);


		printf("[%d] is moving!\n", (unsigned short) infoTeam);

		printf("\nWhite King (%d-%d)\n", (unsigned short) POINT_RANK_MACRO(KINGS_WHITE_MACRO(*kings)), (unsigned short) POINT_FILE_MACRO(KINGS_WHITE_MACRO(*kings)));
		printf("Black King (%d-%d)\n\n", (unsigned short) POINT_RANK_MACRO(KINGS_BLACK_MACRO(*kings)), (unsigned short) POINT_FILE_MACRO(KINGS_BLACK_MACRO(*kings)));

		printf("Castles: ");

		for(unsigned short index = 0; index < 4; index += 1)
		{
			printf("%d", ( ((*info & INFO_CASTLES_MASK) >> 2) & (1 << index)) >> index);
		}

		printf("\n");

		if(infoTeam == INFO_TEAM_WHITE)
		{
			if(!screen_user_handler(board, info, kings, moves, screen))
			{
				printf("Abort! Screen!\n");
				return false;
			}
		}
		else if(infoTeam == INFO_TEAM_BLACK)
		{
			if(!screen_computer_handler(board, info, kings, moves, screen))
			{
				printf("Abort! Screen!\n");
				return false;
			}
		}
		else return false;


		if(infoTeam == INFO_TEAM_WHITE) *info = ALLOC_INFO_TEAM(*info, INFO_TEAM_BLACK);

		if(infoTeam == INFO_TEAM_BLACK)  *info = ALLOC_INFO_TEAM(*info, INFO_TEAM_WHITE);


	}

	return true;
}

bool screen_computer_handler(Piece* board, Info* info, Kings* kings, Move* moves, Screen screen)
{
	Move computerMove;

	unsigned short team = INFO_TEAM_MACRO(*info);

	if(!best_computer_move(&computerMove, board, *info, *kings, team, 3))
	{
		printf("bot could not find move!\n");
		return false;
	}

	if(!move_chess_piece(board, info, kings, computerMove))
	{
		return screen_computer_handler(board, info, kings, moves, screen);
	}

	unsigned short movesAmount = move_array_amount(moves);

	moves[movesAmount] = computerMove;

	return true;
}

bool screen_user_handler(Piece* board, Info* info, Kings* kings, Move* moves, Screen screen)
{
	Move move = MOVE_NONE;

	while(!move_inside_board(move))
	{
		if(!render_chess_board(screen, board, *info, *kings, moves, -1))
		{
			printf("if(!render_chess_board(screen, board, *info, -1))\n");

			return false;
		}

		SDL_UpdateWindowSurface(screen.window);

		if(!input_screen_move(&move, screen, board, *info, *kings, moves)) return false;
	}

	// Now a move on the board has been inputted
	Point startPoint = MOVE_START_MACRO(move);
	Point stopPoint = MOVE_STOP_MACRO(move);

	unsigned short stopRank = POINT_RANK_MACRO(stopPoint);

	Piece startTeam = (board[startPoint] & PIECE_TEAM_MASK);
	Piece startType = (board[startPoint] & PIECE_TYPE_MASK);


	if(!current_team_move(*info, startTeam))
	{
		return screen_user_handler(board, info, kings, moves, screen);
	}


	if(startType == PIECE_TYPE_PAWN) // This can be a promote move
	{
		if(
			(startTeam == PIECE_TEAM_WHITE && stopRank == BLACK_START_RANK) ||
			(startTeam == PIECE_TEAM_BLACK && stopRank == WHITE_START_RANK)
		)
		{
			if(move_fully_legal(board, *info, *kings, move))
			{

				printf("INputting promote move!\n");

				Move promoteMove = MOVE_NONE;
				if(!input_promote_move(&promoteMove, screen, startTeam))
				{
					return screen_user_handler(board, info, kings, moves, screen);
				}
				else if(promoteMove != MOVE_NONE)
				{
					printf("move = ALLOC_MOVE_FLAG(move, promoteMove);\n");
					move = ALLOC_MOVE_FLAG(move, promoteMove);
				}
			}
		}
	}

	if(!move_chess_piece(board, info, kings, move))
	{
		return screen_user_handler(board, info, kings, moves, screen);
	}

	unsigned short movesAmount = move_array_amount(moves);
	moves[movesAmount] = move;

	return true;
}

bool input_screen_move(Move* move, Screen screen, const Piece board[], Info info, Kings kings, const Move moves[])
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
		else if(!screen_move_parser(&inputMove, screen, board, info, kings, moves, event)) continue;
	}

	*move = inputMove;

	return true;
}

bool screen_move_parser(Move* move, Screen screen, const Piece board[], Info info, Kings kings, const Move moves[], Event event)
{

	if(event.type == SDL_MOUSEBUTTONDOWN)
	{
		Point startPoint = parse_mouse_point(event, screen);


		if(!render_chess_board(screen, board, info, kings, moves, startPoint)) return false;

		SDL_UpdateWindowSurface(screen.window);


		Event upEvent;

		while(upEvent.type != SDL_MOUSEBUTTONUP)
		{
			SDL_PollEvent(&upEvent);
		}

		Point stopPoint = parse_mouse_point(upEvent, screen);


		*move = START_MOVE_MACRO(startPoint) | STOP_MOVE_MACRO(stopPoint);

		return true;
	}

	return false;
}
