
#include "../Header-Files-Folder/program.h"

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


	print_chess_board(board);


	Move* moveArray;

	if(piece_legal_moves(&moveArray, board, info, kings, 57))
	{
		unsigned short moveAmount = move_array_amount(moveArray);

		for(unsigned short index = 0; index < moveAmount; index += 1)
		{
			printf("MoveArray[%d] = [%d -> %d]\n", index, MOVE_START_MACRO(moveArray[index]), MOVE_STOP_MACRO(moveArray[index]));
		}

		free(moveArray);
	}


	free(board);

	free(moves);

	return 0;
}
