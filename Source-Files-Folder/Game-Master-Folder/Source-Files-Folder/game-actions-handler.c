
#include "../Header-Files-Folder/master-include-file.h"

bool screen_single_game(Piece* board, Info* info, Move* moves, Screen screen, bool* inverted, bool starting)
{
	Info userTeam = (starting) ? INFO_TEAM_WHITE : INFO_TEAM_BLACK;
	Info engineTeam = info_team_enemy(userTeam);
	if(engineTeam == INFO_TEAM_NONE) return false;

	while(game_still_running(board, *info))
	{
		Info infoTeam = (*info & INFO_TEAM_MASK);
		if(infoTeam == INFO_TEAM_NONE) return false;

		if(!display_chess_board(screen, board, *info, moves, *inverted)) return false;

		if(infoTeam == userTeam)
		{
			if(!screen_user_handler(board, info, moves, screen, inverted)) return false;
		}
		else if(infoTeam == engineTeam)
		{
			if(!screen_computer_handler(board, info, moves, screen)) return false;
		}
		else return false;
	}
	return true;
}

bool screen_cheat_game(Piece* board, Info* info, Move* moves, Screen screen, bool* inverted)
{
	while(game_still_running(board, *info))
	{
		Info infoTeam = (*info & INFO_TEAM_MASK);
		if(infoTeam == INFO_TEAM_NONE) return false;

		if(!display_chess_board(screen, board, *info, moves, *inverted)) return false;

		if(!screen_cheat_handler(board, info, moves, screen, inverted)) return false;
	}
	return true;
}

bool screen_cheat_handler(Piece* board, Info* info, Move* moves, Screen screen, bool* inverted)
{
	Move move = MOVE_NONE;


	short depth = 4, amount = 3;

	Move* bestMoves;
	if(amount_engine_moves(&bestMoves, board, *info, INFO_TEAM_MACRO(*info), depth, amount))
	{
		for(short index = 0; index < amount; index += 1)
		{

			if(bestMoves[index] == MOVE_NONE) printf("#%d\n", index + 1);

			else printf("#%d %d -> %d\n", index + 1,
				MOVE_START_MACRO(bestMoves[index]),
				MOVE_STOP_MACRO(bestMoves[index])
			);
		}

		free(bestMoves);
	}

	if(!input_screen_move(&move, screen, board, *info, moves, inverted)) return false;


	if(!move_chess_piece(board, info, move))
	{
		return screen_cheat_handler(board, info, moves, screen, inverted);
	}

	unsigned short movesAmount = move_array_amount(moves);
	moves[movesAmount] = move;

	return true;
}

bool screen_multi_game(Piece* board, Info* info, Move* moves, Screen screen, bool* inverted)
{
	char whiteMoveString[10];
	char blackMoveString[10];

	while(game_still_running(board, *info))
	{
		Info infoCopy = *info;

		Piece* boardCopy = malloc(sizeof(Piece) * BOARD_LENGTH);
		memcpy(boardCopy, board, sizeof(Piece) * BOARD_LENGTH);



		Info infoTeam = (*info & INFO_TEAM_MASK);

		if(infoTeam == INFO_TEAM_WHITE)
		{
			strcpy(whiteMoveString, "");
			strcpy(blackMoveString, "");
		}


		if(!display_chess_board(screen, board, *info, moves, *inverted))
		{
			free(boardCopy);

			return false;
		}

		if(!screen_user_handler(board, info, moves, screen, inverted))
		{
			printf("if(!screen_user_handler(board, info, moves, screen))\n");

			free(boardCopy);

			return false;
		}


		unsigned short moveAmount = move_array_amount(moves);

		unsigned short teamCopy = INFO_TEAM_MACRO(infoCopy);
		unsigned short turnsCopy = INFO_TURNS_MACRO(infoCopy);

		if(teamCopy == TEAM_WHITE)
		{
			if(!create_move_string(whiteMoveString, boardCopy, infoCopy, moves[moveAmount - 1]))
			{
				printf("if(!create_move_string(whiteMoveString, boardCopy, infoCopy, moves[moveAmount - 1]))\n");
			}
		}
		else if(teamCopy == TEAM_BLACK)
		{
			if(!create_move_string(blackMoveString, boardCopy, infoCopy, moves[moveAmount - 1]))
			{
				printf("if(!create_move_string(blackMoveString, boardCopy, infoCopy, moves[moveAmount - 1]))\n");
			}
		}

		free(boardCopy);



		printf("%d. %s %s\n", turnsCopy, whiteMoveString, blackMoveString);
	}

	return true;
}

bool screen_computer_handler(Piece* board, Info* info, Move* moves, Screen screen)
{
	unsigned short team = INFO_TEAM_MACRO(*info);

	unsigned short seconds = 3;

	printf("-------------------------\n");

	Move computerMove;
	if(!optimal_depth_move(&computerMove, board, *info, team, seconds)) return false;

	if(!move_chess_piece(board, info, computerMove))
	{
		return screen_computer_handler(board, info, moves, screen);
	}

	unsigned short movesAmount = move_array_amount(moves);
	moves[movesAmount] = computerMove;

	return true;
}

bool screen_user_handler(Piece* board, Info* info, Move* moves, Screen screen, bool* inverted)
{
	Move move = MOVE_NONE;

	if(!input_screen_move(&move, screen, board, *info, moves, inverted)) return false;


	if(!move_chess_piece(board, info, move))
	{
		return screen_user_handler(board, info, moves, screen, inverted);
	}

	unsigned short movesAmount = move_array_amount(moves);
	moves[movesAmount] = move;

	return true;
}

bool game_result_handler(Screen screen, const Piece board[], Info info, bool* inverted)
{
	if(!display_result_board(screen, board, info, *inverted))
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
