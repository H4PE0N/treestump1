
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
	// if(engine_depth_move(&bestMove, board, info, kings, startTeam, 3))
	// {
	// 	printf("BestMove: [%d -> %d]\n", MOVE_START_MACRO(bestMove), MOVE_STOP_MACRO(bestMove));
	// }

	unsigned short seconds = 5;

	Move engineMove;
	if(!optimal_depth_move(&engineMove, board, info, kings, INFO_TEAM_MACRO(info), seconds))
	{
		printf("optimal_depth_move failed!\n");
	}

	// char* fenString;
	//
	// if(create_game_string(&fenString, board, info))
	// {
	// 	printf("[ %s ]\n", fenString);
	// 	free(fenString);
	// }
	//
	// printf("Value: %d\n", board_state_value(board, info, kings));


	printf("free(board);\n");

	free(board);

	return 0;
}
