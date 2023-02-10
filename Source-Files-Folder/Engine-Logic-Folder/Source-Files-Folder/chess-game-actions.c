
#include "../Header-Files-Folder/englog-include-file.h"

bool move_chess_piece(Piece* board, State* state, Move move)
{
	if(!MOVE_INSIDE_BOARD(move)) return false;

	if(!correct_move_flag(&move, board, *state)) return false;

	if(!move_fully_legal(board, *state, move)) return false;

	return execute_chess_move(board, state, move);
}

bool correct_move_flag(Move* move, const Piece board[], State state)
{
	if(!MOVE_INSIDE_BOARD(*move)) return false;

	Piece piece = MOVE_START_PIECE(board, *move);

	Move moveFlag = MOVE_FLAG_NONE;

	if(PIECE_STORE_TYPE(piece, PIECE_TYPE_PAWN))
		moveFlag = extract_pawn_flag(*move, piece, state);

	else if(PIECE_STORE_TYPE(piece, PIECE_TYPE_KING))
		moveFlag = extract_king_flag(*move, piece, state);

	*move = ALLOC_MOVE_FLAG(*move, moveFlag); return true;
}

Move extract_pawn_flag(Move move, Piece piece, State state)
{
	if(double_move_ident(state, move, piece)) return MOVE_FLAG_DOUBLE;

	if(passant_move_ident(state, move, piece)) return MOVE_FLAG_PASSANT;

	if(promote_move_ident(state, move, piece))
		return (MOVE_PROMOTE_FLAG(move) ? MASK_MOVE_FLAG(move) : MOVE_FLAG_QUEEN);

	return MOVE_FLAG_NONE;
}

Move extract_king_flag(Move move, Piece piece, State state)
{
	if(castle_move_ident(state, move, piece)) return MOVE_FLAG_CASTLE;

	return MOVE_FLAG_NONE;
}
