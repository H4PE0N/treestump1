
#include "../Header-Files-Folder/englog-include-file.h"

bool execute_chess_move(Piece* board, Info* info, Move move)
{
	if(!MOVE_INSIDE_BOARD(move)) return false;

	update_info_values(info, board, move);

	if(MOVE_PROMOTE_FLAG(move))
		return execute_promote_move(board, move);

	if(MOVE_STORE_FLAG(move, MOVE_FLAG_CASTLE))
		return execute_castle_move(board, move);

	if(MOVE_STORE_FLAG(move, MOVE_FLAG_PASSANT))
		return execute_passant_move(board, move);

	return execute_board_move(board, move);
}

void update_info_values(Info* info, const Piece board[], Move move)
{
	if(INFO_STORE_TEAM(*info, INFO_TEAM_BLACK))
		increase_info_turns(info);

	switch_current_team(info);

	if((START_PIECE_TYPE(board, move) == PIECE_TYPE_PAWN) || STOP_PIECE_EXISTS(board, move))
		*info = CLEAR_INFO_COUNTER(*info);

	else increase_info_counter(info);

	if(MOVE_STORE_FLAG(move, MOVE_FLAG_DOUBLE))
		alloc_passant_point(info, move);

	else *info = CLEAR_INFO_PASSANT(*info);

	moved_reset_castle(info, board, move);
}

bool moved_reset_castle(Info* info, const Piece board[], Move move)
{
	Point startPoint = MOVE_START_MACRO(move);
	Point stopPoint = MOVE_STOP_MACRO(move);

	if(PIECE_STORE_TYPE(board[startPoint], PIECE_TYPE_KING))
		return reset_king_ability(info, board[startPoint]);

	if(PIECE_STORE_TYPE(board[stopPoint], PIECE_TYPE_ROOK))
		return reset_rook_ability(info, board[stopPoint], stopPoint);

	if(PIECE_STORE_TYPE(board[startPoint], PIECE_TYPE_ROOK))
		return reset_rook_ability(info, board[startPoint], startPoint);

	return false;
}

bool reset_king_ability(Info* info, Piece kingPiece)
{
	if(!PIECE_STORE_TYPE(kingPiece, PIECE_TYPE_KING)) return false;

	if(PIECE_TEAM_MACRO(kingPiece) == TEAM_WHITE) *info = CLEAR_WHITE_CASTLE(*info);

	else if(PIECE_TEAM_MACRO(kingPiece) == TEAM_BLACK) *info = CLEAR_BLACK_CASTLE(*info);

	return true;
}

bool reset_rook_ability(Info* info, Piece rookPiece, Point rookPoint)
{
	if(!PIECE_STORE_TYPE(rookPiece, PIECE_TYPE_ROOK)) return false;

	if(rookPoint == WROOK_QSIDE_POINT) *info = CLEAR_WHITE_QSIDE(*info);

	else if(rookPoint == WROOK_KSIDE_POINT) *info = CLEAR_WHITE_KSIDE(*info);

	else if(rookPoint == BROOK_QSIDE_POINT) *info = CLEAR_BLACK_QSIDE(*info);

	else if(rookPoint == BROOK_KSIDE_POINT) *info = CLEAR_BLACK_KSIDE(*info);

	return true;
}

Piece promote_piece_type(Move move)
{
	if(MOVE_STORE_FLAG(move, MOVE_FLAG_ROOK)) return PIECE_TYPE_ROOK;

	if(MOVE_STORE_FLAG(move, MOVE_FLAG_BISHOP)) return PIECE_TYPE_BISHOP;

	if(MOVE_STORE_FLAG(move, MOVE_FLAG_KNIGHT)) return PIECE_TYPE_KNIGHT;

	if(MOVE_STORE_FLAG(move, MOVE_FLAG_QUEEN)) return PIECE_TYPE_QUEEN;

	return PIECE_TYPE_NONE;
}

Piece promote_piece_team(Move move)
{
	if(MOVE_STOP_RANK(move) == WHITE_START_RANK) return PIECE_TEAM_BLACK;

	if(MOVE_STOP_RANK(move) == BLACK_START_RANK) return PIECE_TEAM_WHITE;

	return PIECE_TEAM_NONE;
}

Piece move_promote_piece(Move move)
{
	Piece pieceTeam = promote_piece_team(move);
	Piece pieceType = promote_piece_type(move);

	if((pieceType == PIECE_TYPE_NONE) || (pieceTeam == PIECE_TEAM_NONE)) return PIECE_NONE;

	return (pieceTeam | pieceType);
}

bool execute_board_move(Piece* board, Move move)
{
	Point startPoint = MOVE_START_MACRO(move);
	Point stopPoint = MOVE_STOP_MACRO(move);

	board[stopPoint] = board[startPoint];
	board[startPoint] = PIECE_NONE;

	return true;
}

bool execute_passant_move(Piece* board, Move move)
{
	Point startPoint = MOVE_START_MACRO(move);
	Point stopPoint = MOVE_STOP_MACRO(move);

	Point pawnPoint = PAWN_PASSANT_POINT(move);

	board[stopPoint] = board[startPoint];
	board[startPoint] = PIECE_NONE;
	board[pawnPoint] = PIECE_NONE;

	return true;
}

bool execute_promote_move(Piece* board, Move move)
{
	Point startPoint = MOVE_START_MACRO(move);
	Point stopPoint = MOVE_STOP_MACRO(move);

	Piece promotePiece = move_promote_piece(move);
	if(promotePiece == PIECE_NONE) return false;

	board[stopPoint] = promotePiece;
	board[startPoint] = PIECE_NONE;

	return true;
}

bool execute_castle_move(Piece* board, Move move)
{
	Point startRook = castle_rook_point(move);
	Point stopRook = castle_middle_point(move);

	if((startRook == POINT_NONE) || (stopRook == POINT_NONE)) return false;

	Point startPoint = MOVE_START_MACRO(move);
	Point stopPoint = MOVE_STOP_MACRO(move);

	board[stopPoint] = board[startPoint];
	board[startPoint] = PIECE_NONE;

	board[stopRook] = board[startRook];
	board[startRook] = PIECE_NONE;

	return true;
}
