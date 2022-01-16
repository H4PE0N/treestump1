
#include "../Header-Files-Folder/engine-include-file.h"

bool move_chess_piece(Piece* board, Info* info, Move move)
{
	if(!move_fully_legal(board, *info, move))
	{
		return false;
	}

	if(!execute_chess_move(board, info, move))
	{
		return false;
	}

	return true;
}

// This function creates memory for an array of legal moves
// The memory has to be freed after use!! OBS!
// This function is trash, make it more specific for the pieces:
bool piece_legal_moves(Move** moveArray, const Piece board[], Info info, Point startPoint)
{
	if(!point_inside_board(startPoint)) return false;


	*moveArray = malloc(sizeof(Move) * 64);
	memset(*moveArray, MOVE_NONE, 64);


	Piece startPiece = board[startPoint];


	unsigned short moveAmount = 0;


	for(unsigned short stopPoint = 0; stopPoint < BOARD_LENGTH; stopPoint += 1)
	{
		Move currentMove = START_MOVE_MACRO(startPoint) | STOP_MOVE_MACRO(stopPoint);

		if(!correct_move_flag(&currentMove, startPiece, info)) continue;

		if(move_fully_legal(board, info, currentMove))
		{
			(*moveArray)[moveAmount] = currentMove;

			moveAmount += 1;
		}
	}

	return true;
}
