
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

	Move move = MOVE_BLANK;
	Point start = 59;
	Point stop = 32;

	move |= (start << MOVE_START_SHIFT);
	move |= (stop << MOVE_STOP_SHIFT);

	if(!correct_move_flag(&move, board[start], info))
	{
		printf("Could not correct flag\n");

		free(board);

		return false;
	}

	print_chess_board(board);

	if(!move_chess_piece(board, &info, &kings, move))
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
