
#include "../Header-Files-Folder/master-include-file.h"

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

bool screen_multi_game(Piece* board, Info* info, Kings* kings, Move* moves, Screen screen)
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

		if(!screen_user_handler(board, info, kings, moves, screen))
		{
			printf("Abort! Screen!\n");
			return false;
		}

		if(infoTeam == INFO_TEAM_WHITE) *info = ALLOC_INFO_TEAM(*info, INFO_TEAM_BLACK);

		if(infoTeam == INFO_TEAM_BLACK)  *info = ALLOC_INFO_TEAM(*info, INFO_TEAM_WHITE);
	}

	return true;
}

bool screen_computer_handler(Piece* board, Info* info, Kings* kings, Move* moves, Screen screen)
{
	Move computerMove;

	unsigned short team = INFO_TEAM_MACRO(*info);

	if(!best_computer_move(&computerMove, board, *info, *kings, team, 2))
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
			return false;
		}

		SDL_UpdateWindowSurface(screen.window);

		if(!input_screen_move(&move, screen, board, *info, *kings, moves)) return false;
	}

	// Now a move on the board has been inputted
	Point startPoint = MOVE_START_MACRO(move);
	Point stopPoint = MOVE_STOP_MACRO(move);

	unsigned short stopRank = POINT_RANK_MACRO(stopPoint);

	unsigned short startTeam = PIECE_TEAM_MACRO(board[startPoint]);
	Piece startPieceType = (board[startPoint] & PIECE_TYPE_MASK);


	if(!current_team_move(*info, startTeam))
	{
		return screen_user_handler(board, info, kings, moves, screen);
	}


	if(startPieceType == PIECE_TYPE_PAWN) // This can be a promote move
	{
		if(
			(startTeam == TEAM_WHITE && stopRank == BLACK_START_RANK) ||
			(startTeam == TEAM_BLACK && stopRank == WHITE_START_RANK)
		)
		{
			if(move_fully_legal(board, *info, *kings, move))
			{
				Move promoteMove = MOVE_NONE;
				if(!input_promote_move(&promoteMove, screen, startTeam))
				{
					return screen_user_handler(board, info, kings, moves, screen);
				}
				else if(promoteMove != MOVE_NONE)
				{
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

bool game_result_handler(Screen screen, const Piece board[], Info info, Kings kings)
{
	if(render_result_board(screen, board, info, kings))
	{
		SDL_UpdateWindowSurface(screen.window);
	}
	else printf("Could not render board!\n");



	Event event;

	while(event.type != SDL_QUIT && !(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_q))
	{
		SDL_PollEvent(&event);

		SDL_Delay(100);
	}

	return true;
}
