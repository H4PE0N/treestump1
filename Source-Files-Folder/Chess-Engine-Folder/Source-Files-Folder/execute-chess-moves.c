
#include "../Header-Files-Folder/engine-include-file.h"

// This function is going to just move the pieces around,
// based on what action (flag) the move has
// This function is not going to check any validation
bool execute_chess_move(Piece* board, Info* info, Move move)
{
	Move moveFlag = (move & MOVE_FLAG_MASK);

	if(moveFlag == MOVE_FLAG_KNIGHT || moveFlag == MOVE_FLAG_BISHOP || moveFlag == MOVE_FLAG_ROOK || moveFlag == MOVE_FLAG_QUEEN)
	{
		return execute_promote_move(board, info, move);
	}
	else if(moveFlag == MOVE_FLAG_CASTLE)
	{
		return execute_castle_move(board, info, move);
	}
	else if(moveFlag == MOVE_FLAG_PASSANT)
	{
		return execute_passant_move(board, info, move);
	}
	else if(moveFlag == MOVE_FLAG_DOUBLE)
	{
		return execute_double_move(board, info, move);
	}
	else
	{
		return execute_normal_move(board, info, move);
	}
}

// This function is going to execute all normal moves
// - It just moves the piece to a specific point
bool execute_normal_move(Piece* board, Info* info, Move move)
{
	printf("execute_normal_move\n");

	if(!move_inside_board(move))
	{
		return false;
	}

	Point start = MOVE_START_MACRO(move);
	Point stop = MOVE_STOP_MACRO(move);

	board[stop] = board[start];
	board[start] = PIECE_NONE;

	return true;
}

// This function is going to execute a castle
// - It has to move both the king and the rook
bool execute_castle_move(Piece* board, Info* info, Move move)
{
	printf("execute_castle_move\n");

	return true;
}

// This function is going to execute a promotion
// - It has to get the promotion (KNIGHT, BISHOP, ROOK, QUEEN)
// and swap the piece at the STOP point in the move
bool execute_promote_move(Piece* board, Info* info, Move move)
{
	printf("execute_promote_move\n");

	if(!move_inside_board(move))
	{
		return false;
	}

	Point startPoint = MOVE_START_MACRO(move);
	Point stopPoint = MOVE_STOP_MACRO(move);

	board[stopPoint] = ALLOC_PIECE_TYPE(board[startPoint], PIECE_TYPE_QUEEN);
	board[startPoint] = PIECE_NONE;

	return true;
}

// This function is going to execute en passant take
// - It has to update the passant point to POINT_NONE
bool execute_passant_move(Piece* board, Info* info, Move move)
{
	printf("execute_passant_move\n");

	if(!move_inside_board(move))
	{
		return false;
	}

	Point start = MOVE_START_MACRO(move);
	Point stop = MOVE_STOP_MACRO(move);

	board[stop] = board[start];
	board[start] = PIECE_NONE;

	return true;
}

// This function is going to execute the double jump by a pawn
// - It has to update the passant point
bool execute_double_move(Piece* board, Info* info, Move move)
{
	printf("execute_double_move\n");

	// This has to be changed!:

	if(!move_inside_board(move))
	{
		return false;
	}

	Point start = MOVE_START_MACRO(move);
	Point stop = MOVE_STOP_MACRO(move);

	board[stop] = board[start];
	board[start] = PIECE_NONE;

	return true;
}
