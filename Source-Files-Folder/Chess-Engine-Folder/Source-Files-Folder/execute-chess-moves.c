
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

	if(!move_inside_board(move)) return false;

	Point startPoint = MOVE_START_MACRO(move);
	Point stopPoint = MOVE_STOP_MACRO(move);


	board[stopPoint] = board[startPoint];
	board[startPoint] = PIECE_NONE;


	*info = ALLOC_INFO_PASSANT(*info, 0);

	return true;
}

// This function is going to execute a castle
// - It has to move both the king and the rook
bool execute_castle_move(Piece* board, Info* info, Move move)
{
	printf("execute_castle_move\n");


	*info = ALLOC_INFO_PASSANT(*info, 0);

	return true;
}

// This function is going to execute a promotion
// - It has to get the promotion (KNIGHT, BISHOP, ROOK, QUEEN)
// and swap the piece at the STOP point in the move
bool execute_promote_move(Piece* board, Info* info, Move move)
{
	printf("execute_promote_move\n");

	if(!move_inside_board(move)) return false;


	Point startPoint = MOVE_START_MACRO(move);
	Point stopPoint = MOVE_STOP_MACRO(move);


	Piece pieceTeam = (board[startPoint] & PIECE_TEAM_MASK);
	Piece pieceType = PIECE_BLANK;


	Move moveFlag = (move & MOVE_FLAG_MASK);


	if(moveFlag == MOVE_FLAG_ROOK) pieceType = PIECE_TYPE_ROOK;

	else if(moveFlag == MOVE_FLAG_BISHOP) pieceType = PIECE_TYPE_BISHOP;

	else if(moveFlag == MOVE_FLAG_KNIGHT) pieceType = PIECE_TYPE_KNIGHT;

	else if(moveFlag == MOVE_FLAG_QUEEN) pieceType = PIECE_TYPE_QUEEN;

	else return false;


	board[stopPoint] = (pieceTeam | pieceType);
	board[startPoint] = PIECE_NONE;


	*info = ALLOC_INFO_PASSANT(*info, 0);

	return true;
}

// This function is going to execute en passant take
// - It has to update the passant point to POINT_NONE
bool execute_passant_move(Piece* board, Info* info, Move move)
{
	printf("execute_passant_move\n");

	if(!move_inside_board(move)) return false;


	Point startPoint = MOVE_START_MACRO(move);
	Point stopPoint = MOVE_STOP_MACRO(move);


	board[stopPoint] = board[startPoint];
	board[startPoint] = PIECE_NONE;


	*info = ALLOC_INFO_PASSANT(*info, 0);

	return true;
}

// This function is going to execute the double jump by a pawn
// - It has to update the passant point
bool execute_double_move(Piece* board, Info* info, Move move)
{
	printf("execute_double_move\n");

	if(!move_inside_board(move)) return false;


	Point startPoint = MOVE_START_MACRO(move);
	Point stopPoint = MOVE_STOP_MACRO(move);


	unsigned short startFile = POINT_FILE_MACRO(startPoint);


	board[stopPoint] = board[startPoint];
	board[startPoint] = PIECE_NONE;


	unsigned short passantFile = (startFile + 1);

	Info infoPassant = PASSANT_INFO_MACRO(passantFile);

	printf("Allocating %d to passant\n", passantFile);

	*info = ALLOC_INFO_PASSANT(*info, infoPassant);

	printf("%d is not allocated!\n", INFO_PASSANT_MACRO(*info));


	return true;
}
