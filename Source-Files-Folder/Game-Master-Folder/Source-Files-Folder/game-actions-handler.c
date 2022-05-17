
#include "../Header-Files-Folder/master-include-file.h"

bool screen_single_game(Piece* board, Info* info, Kings* kings, Move* moves, Screen screen)
{
	while(game_still_running(board, *info, *kings))
	{

		Info infoTeam = (*info & INFO_TEAM_MASK);

		if(!display_chess_board(screen, board, *info, *kings, moves, -1))
		{
			printf("if(!display_chess_board(screen, board, *info, -1))\n");

			return false;
		}

		printf("[%d] is moving!\n", (unsigned short) infoTeam);

		printf("\n");

		if(infoTeam == INFO_TEAM_WHITE)
		{
			if(!screen_user_handler(board, info, kings, moves, screen))
			{
				return false;
			}
		}
		else if(infoTeam == INFO_TEAM_BLACK)
		{
			if(!screen_computer_handler(board, info, kings, moves, screen))
			{
				return false;
			}
		}
		else return false;
	}

	return true;
}

bool screen_multi_game(Piece* board, Info* info, Kings* kings, Move* moves, Screen screen)
{
	char whiteMoveString[10];
	char blackMoveString[10];

	while(game_still_running(board, *info, *kings))
	{
		Info infoCopy = *info;
		Kings kingsCopy = *kings;

		Piece* boardCopy = malloc(sizeof(Piece) * BOARD_LENGTH);
		memcpy(boardCopy, board, sizeof(Piece) * BOARD_LENGTH);



		Info infoTeam = (*info & INFO_TEAM_MASK);

		if(infoTeam == INFO_TEAM_WHITE)
		{
			strcpy(whiteMoveString, "");
			strcpy(blackMoveString, "");
		}


		if(!display_chess_board(screen, board, *info, *kings, moves, -1))
		{
			printf("if(!display_chess_board(screen, board, *info, -1))\n");

			free(boardCopy);

			return false;
		}

		if(!screen_user_handler(board, info, kings, moves, screen))
		{
			printf("if(!screen_user_handler(board, info, kings, moves, screen))\n");

			free(boardCopy);

			return false;
		}


		unsigned short moveAmount = move_array_amount(moves);

		unsigned short teamCopy = INFO_TEAM_MACRO(infoCopy);
		unsigned short turnsCopy = INFO_TURNS_MACRO(infoCopy);

		if(teamCopy == TEAM_WHITE)
		{
			if(!create_move_string(whiteMoveString, boardCopy, infoCopy, kingsCopy, moves[moveAmount - 1]))
			{
				printf("if(!create_move_string(whiteMoveString, boardCopy, infoCopy, kingsCopy, moves[moveAmount - 1]))\n");
			}
		}
		else if(teamCopy == TEAM_BLACK)
		{
			if(!create_move_string(blackMoveString, boardCopy, infoCopy, kingsCopy, moves[moveAmount - 1]))
			{
				printf("if(!create_move_string(blackMoveString, boardCopy, infoCopy, kingsCopy, moves[moveAmount - 1]))\n");
			}
		}

		free(boardCopy);



		printf("%d. %s %s\n", turnsCopy, whiteMoveString, blackMoveString);
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
		if(!display_chess_board(screen, board, *info, *kings, moves, -1))
		{
			return false;
		}

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
	if(!display_result_board(screen, board, info, kings))
	{
		printf("Could not display result board!\n");
	}

	Event event;

	while(event.type != SDL_QUIT && !(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_q))
	{
		SDL_WaitEvent(&event);

		SDL_Delay(100);
	}

	return true;
}
