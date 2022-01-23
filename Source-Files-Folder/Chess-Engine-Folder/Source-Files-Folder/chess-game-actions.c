
#include "../Header-Files-Folder/engine-include-file.h"

bool move_chess_piece(Piece* board, Info* info, Kings* kings, Move move)
{
	Piece startPiece = board[MOVE_START_MACRO(move)];

	unsigned short startTeam = PIECE_TEAM_MACRO(startPiece);

	if(!current_team_move(*info, startTeam)) return false;

	if(!correct_move_flag(&move, startPiece, *info)) return false;

	if(!move_fully_legal(board, *info, *kings, move)) return false;

	if(!execute_chess_move(board, info, kings, move)) return false;

	return true;
}

// This function should give the move its correct flag
// To do that, it checks for patterns, but the move don't have to be legal,
// this function just sets the flag that it would have had to have.
bool correct_move_flag(Move* move, Piece piece, Info info)
{
	if(!move_inside_board(*move)) return false;

	Move moveFlag = (*move & MOVE_FLAG_MASK);

	bool flagIsPassant = (moveFlag == MOVE_FLAG_KNIGHT || moveFlag == MOVE_FLAG_BISHOP || moveFlag == MOVE_FLAG_ROOK || moveFlag == MOVE_FLAG_QUEEN);

	if(double_move_ident(info, *move, piece)) moveFlag = MOVE_FLAG_DOUBLE;

	else if(castle_move_ident(info, *move, piece)) moveFlag = MOVE_FLAG_CASTLE;

	else if(passant_move_ident(info, *move, piece)) moveFlag = MOVE_FLAG_PASSANT;

	else if(promote_move_ident(info, *move, piece))
	{
		if(!flagIsPassant) moveFlag = MOVE_FLAG_QUEEN;
	}

	else moveFlag = MOVE_FLAG_NONE;

	*move = ALLOC_MOVE_FLAG(*move, moveFlag);

	return true;
}
