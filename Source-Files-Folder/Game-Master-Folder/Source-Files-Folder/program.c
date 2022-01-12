
#include "../Header-Files-Folder/program.h"

void print_chess_board(const Piece board[])
{
	for(unsigned short rank = 0; rank < BOARD_RANKS; rank += 1)
	{
		for(unsigned short file = 0; file < BOARD_FILES; file += 1)
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

	
	board[25] = PIECE_TEAM_WHITE | PIECE_TYPE_PAWN;
	board[26] = PIECE_TEAM_BLACK | PIECE_TYPE_KNIGHT;
	board[27] = PIECE_TEAM_BLACK | PIECE_TYPE_BISHOP;
	board[33] = PIECE_TEAM_WHITE | PIECE_TYPE_ROOK;
	board[50] = PIECE_TEAM_WHITE | PIECE_TYPE_PAWN;
	board[35] = PIECE_TEAM_WHITE | PIECE_TYPE_KING;


	Info info = INFO_NONE;

	Move move = MOVE_NONE;
	Point start = 50;
	Point stop = 34;

	move |= (start << MOVE_START_SHIFT);
	move |= (stop << MOVE_STOP_SHIFT);

	if(!correct_move_flag(&move, board[start], info))
	{
		printf("Could not correct flag\n");

		free(board);

		return false;
	}
	else
	{
		printf("Corrected flag: %d\n", move & MOVE_FLAG_MASK);
	}

	print_chess_board(board);

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