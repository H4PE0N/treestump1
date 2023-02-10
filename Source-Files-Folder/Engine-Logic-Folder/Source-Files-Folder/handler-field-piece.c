
#include "../Header-Files-Folder/englog-include-file.h"

Piece* copy_chess_board(const Piece board[])
{
	Piece* boardCopy = malloc(sizeof(Piece) * BOARD_POINTS);
	memcpy(boardCopy, board, sizeof(Piece) * BOARD_POINTS);

	return boardCopy;
}