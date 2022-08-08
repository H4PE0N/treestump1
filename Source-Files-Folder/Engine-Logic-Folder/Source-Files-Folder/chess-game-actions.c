
#include "../Header-Files-Folder/englog-include-file.h"

bool move_chess_piece(Piece* board, Info* info, Move move)
{
	if(!move_inside_board(move)) return false;

	Piece startPiece = move_start_piece(move, board);
	unsigned short startTeam = PIECE_TEAM_MACRO(startPiece);

	if(!current_team_move(*info, startTeam)) return false;

	if(!correct_move_flag(&move, startPiece, *info)) return false;

	if(!move_fully_legal(board, *info, move)) return false;

	return execute_chess_move(board, info, move);
}

bool correct_move_flag(Move* move, Piece piece, Info info)
{
	if(!move_inside_board(*move)) return false;

	Move moveFlag = MOVE_FLAG_NONE;

	if(PIECE_STORE_TYPE(piece, PIECE_TYPE_PAWN))
		moveFlag = extract_pawn_flag(*move, piece, info);

	else if(PIECE_STORE_TYPE(piece, PIECE_TYPE_KING))
		moveFlag = extract_king_flag(*move, piece, info);

	*move = ALLOC_MOVE_FLAG(*move, moveFlag); return true;
}

Move extract_pawn_flag(Move move, Piece piece, Info info)
{
	if(double_move_ident(info, move, piece)) return MOVE_FLAG_DOUBLE;

	if(passant_move_ident(info, move, piece)) return MOVE_FLAG_PASSANT;

	if(promote_move_ident(info, move, piece))
		return (MOVE_PROMOTE_FLAG(move) ? MASK_MOVE_FLAG(move) : MOVE_FLAG_QUEEN);

	return MOVE_FLAG_NONE;
}

Move extract_king_flag(Move move, Piece piece, Info info)
{
	if(castle_move_ident(info, move, piece)) return MOVE_FLAG_CASTLE;

	return MOVE_FLAG_NONE;
}
