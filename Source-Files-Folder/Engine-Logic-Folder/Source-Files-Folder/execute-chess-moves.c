
#include "../Header-Files-Folder/englog-include-file.h"

// This function is going to just move the pieces around,
// based on what action (flag) the move has
// This function is not going to check any validation
bool execute_chess_move(Piece* board, Info* info, Move move)
{
	if(MOVE_PROMOTE_FLAG(move))
		return execute_promote_move(board, info, move);

	if(MOVE_STORE_FLAG(move, MOVE_FLAG_CASTLE))
		return execute_castle_move(board, info, move);

	if(MOVE_STORE_FLAG(move, MOVE_FLAG_PASSANT))
		return execute_passant_move(board, info, move);

	if(MOVE_STORE_FLAG(move, MOVE_FLAG_DOUBLE))
		return execute_double_move(board, info, move);

	return execute_normal_move(board, info, move);
}

// This function is going to execute all normal moves
// - It just moves the piece to a specific point
bool execute_normal_move(Piece* board, Info* info, Move move)
{
	if(!move_inside_board(move)) return false;

	moved_reset_castle(info, board, move);

	if(!execute_board_move(board, move)) return false;

	*info = CLEAR_INFO_PASSANT(*info);

	increase_info_turns(info); switch_current_team(info);

	return true;
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

// This function is going to execute a castle
// - It has to move both the king and the rook
bool execute_castle_move(Piece* board, Info* info, Move kingMove)
{
	Point startRook = castle_rook_point(kingMove);
	Point stopRook = castle_middle_point(kingMove);

	if((startRook == POINT_NONE) || (stopRook == POINT_NONE)) return false;

	Piece kingPiece = move_start_piece(kingMove, board);


	if(!execute_board_move(board, kingMove)) return false;
	if(!execute_start_stop(board, startRook, stopRook)) return false;


	if(!reset_king_ability(info, kingPiece)) return false;

	*info = CLEAR_INFO_PASSANT(*info);

	increase_info_turns(info); switch_current_team(info);

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
	board[MOVE_STOP_MACRO(move)] = move_start_piece(move, board);
	board[MOVE_START_MACRO(move)] = PIECE_NONE;

	return true;
}

bool execute_start_stop(Piece* board, Point startPoint, Point stopPoint)
{
	board[stopPoint] = board[startPoint];
	board[startPoint] = PIECE_NONE;

	return true;
}

// This function is going to execute a promotion
// - It has to get the promotion (KNIGHT, BISHOP, ROOK, QUEEN)
// and swap the piece at the STOP point in the move
bool execute_promote_move(Piece* board, Info* info, Move move)
{
	if(!move_inside_board(move)) return false;

	Point startPoint = MOVE_START_MACRO(move);
	Point stopPoint = MOVE_STOP_MACRO(move);

	Piece promotePiece = move_promote_piece(move);
	if(promotePiece == PIECE_NONE) return false;


	board[stopPoint] = promotePiece;
	board[startPoint] = PIECE_NONE;


	*info = CLEAR_INFO_PASSANT(*info);

	increase_info_turns(info); switch_current_team(info);

	return true;
}

Point pawn_passant_point(Move move)
{
	if(!move_inside_board(move)) return POINT_NONE;

	unsigned short pawnRank = MOVE_START_RANK(move);
	unsigned short pawnFile = MOVE_STOP_FILE(move);

	return RANK_FILE_POINT(pawnRank, pawnFile);
}

// This function is going to execute en passant take
// - It has to update the passant point to POINT_NONE
bool execute_passant_move(Piece* board, Info* info, Move move)
{
	if(!move_inside_board(move)) return false;

	Point startPoint = MOVE_START_MACRO(move);
	Point stopPoint = MOVE_STOP_MACRO(move);

	Point pawnPoint = pawn_passant_point(move);


	board[stopPoint] = board[startPoint];
	board[startPoint] = PIECE_NONE;
	board[pawnPoint] = PIECE_NONE;


	*info = CLEAR_INFO_PASSANT(*info);

	increase_info_turns(info); switch_current_team(info);

	return true;
}

// This function is going to execute the double jump by a pawn
// - It has to update the passant point
bool execute_double_move(Piece* board, Info* info, Move move)
{
	if(!move_inside_board(move)) return false;

	Point startPoint = MOVE_START_MACRO(move);
	Point stopPoint = MOVE_STOP_MACRO(move);


	board[stopPoint] = board[startPoint];
	board[startPoint] = PIECE_NONE;


	unsigned short startFile = POINT_FILE_MACRO(startPoint);
	Info infoPassant = PASSANT_INFO_MACRO((startFile + 1));

	*info = ALLOC_INFO_PASSANT(*info, infoPassant);

	increase_info_turns(info); switch_current_team(info);

	return true;
}
