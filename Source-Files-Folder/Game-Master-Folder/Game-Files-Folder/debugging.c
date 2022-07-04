
#include "../../Chess-Engine-Folder/Header-Files-Folder/engine-include-file.h"

// "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 1 0"

void print_chess_board(const Piece board[])
{
	for(unsigned short rank = 0; rank < BOARD_RANKS; rank += 1)
	{
		for(unsigned short file = 0; file < BOARD_FILES; file += 1)
		{
			Point point = RANK_POINT_MACRO(rank) | FILE_POINT_MACRO(file);

			Piece piece = board[point];

			unsigned short type = PIECE_TYPE_MACRO(piece);

			char symbol = '.';

			if((piece & PIECE_TEAM_MASK) == PIECE_TEAM_WHITE)
			{
				symbol = WHITE_TYPE_SYMBOLS[type];
			}
			else if((piece & PIECE_TEAM_MASK) == PIECE_TEAM_BLACK)
			{
				symbol = BLACK_TYPE_SYMBOLS[type];
			}

			printf("%c ", symbol);
		}
		printf("\n");
	}
}

int main(int argAmount, char* arguments[])
{
	if(argAmount < 2) return false;

	Piece* board;
	Info info;
	Kings kings;


	char* gameString = arguments[1];

	if(!parse_game_string(&board, &info, &kings, gameString))
	{
		printf("Could not parse game string!\n");

		return false;
	}

	print_chess_board(board);

	for(unsigned short rank = 0; rank < BOARD_RANKS; rank += 1)
	{
		for(unsigned short file = 0; file < BOARD_FILES; file += 1)
		{
			printf("%02d ", (rank * BOARD_FILES) + file);
		}
		printf("\n");
	}

	printf("INFO TEAM: %d\n", INFO_TEAM_MACRO(info));


	// unsigned short startTeam = INFO_TEAM_MACRO(info);

	// Move bestMove;
	//
	// if(create_engine_move(&bestMove, board, info, kings, startTeam, 3))
	// {
	// 	printf("BestMove: [%d -> %d]\n", MOVE_START_MACRO(bestMove), MOVE_STOP_MACRO(bestMove));
	// }


	short depth = 3, amount = 30;

	Move* bestMoves;
	if(amount_engine_moves(&bestMoves, board, info, kings, INFO_TEAM_MACRO(info), depth, amount))
	{
		for(short index = 0; index < amount; index += 1)
		{
			if(bestMoves[index] == MOVE_NONE) printf("#%d -\n", index + 1);

			else printf("#%d %d -> %d\n", index + 1,
				MOVE_START_MACRO(bestMoves[index]),
				MOVE_STOP_MACRO(bestMoves[index])
			);
		}

		free(bestMoves);
	}


	char* fenString;

	if(create_game_string(&fenString, board, info))
	{
		printf("[ %s ]\n", fenString);
		free(fenString);
	}

	printf("Value: %d\n", board_state_value(board, info, kings));


	free(board);

	return 0;
}
