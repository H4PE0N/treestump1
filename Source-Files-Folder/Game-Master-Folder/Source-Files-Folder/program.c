
#include "../Header-Files-Folder/program.h"

void print_chess_board(const Piece board[])
{
	for(unsigned short file = 0; file < BOARD_FILES; file += 1)
	{
		for(unsigned short rank = 0; rank < BOARD_RANKS; rank += 1)
		{
			Point point = (rank << POINT_RANK_SHIFT) | (file << POINT_FILE_SHIFT);

			Piece piece = board[point];

			Type type = (piece & PIECE_TYPE_MASK) >> PIECE_TYPE_SHIFT;

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
	Piece* board = malloc(sizeof(Piece) * BOARD_LENGTH);

	for(unsigned short index = 0; index < BOARD_LENGTH; index += 1)
	{
		board[index] = PIECE_TEAM_NONE | PIECE_TYPE_NONE;
	}

	board[56] = PIECE_TEAM_BLACK | PIECE_TYPE_PAWN;

	Info info = INFO_NONE;

	Move move = MOVE_NONE;

	if(!move_chess_piece(board, &info, move))
	{
		printf("Could not move!\n");
	}
	else
	{
		printf("Moved chess piece!\n");
	}

	print_chess_board(board);

	free(board);
	
	return 0;
}