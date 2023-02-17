
#include "../Header-Files-Folder/englog-include-file.h"

bool execute_chess_move(Piece* board, State* state, Move move)
{
	if(!MOVE_INSIDE_BOARD(move)) return false;

	update_state_values(state, board, move);

	if(MOVE_PROMOTE_FLAG(move))
		return execute_promote_move(board, move);

	if(MOVE_STORE_FLAG(move, MOVE_FLAG_CASTLE))
		return execute_castle_move(board, move);

	if(MOVE_STORE_FLAG(move, MOVE_FLAG_PASSANT))
		return execute_passant_move(board, move);

	return execute_board_move(board, move);
}

void update_state_values(State* state, const Piece board[], Move move)
{
	if(STATE_STORE_CURRENT(*state, STATE_TEAM_BLACK))
		increase_state_turns(state);

	switch_current_team(state);

	if((MOVE_START_TYPE(board, move) == TYPE_PAWN) || STOP_PIECE_EXISTS(board, move))
		*state = CLEAR_STATE_CLOCK(*state);

	else increase_state_clock(state);

	if(MOVE_STORE_FLAG(move, MOVE_FLAG_DOUBLE))
		alloc_passant_point(state, move);

	else *state = CLEAR_STATE_PASSANT(*state);

	moved_reset_castle(state, board, move);
}

bool moved_reset_castle(State* state, const Piece board[], Move move)
{
	Point startPoint = MOVE_START_MACRO(move);
	Point stopPoint = MOVE_STOP_MACRO(move);

	if(PIECE_STORE_TYPE(board[startPoint], PIECE_TYPE_KING))
		return reset_king_ability(state, board[startPoint]);

	if(PIECE_STORE_TYPE(board[stopPoint], PIECE_TYPE_ROOK))
		return reset_rook_ability(state, board[stopPoint], stopPoint);

	if(PIECE_STORE_TYPE(board[startPoint], PIECE_TYPE_ROOK))
		return reset_rook_ability(state, board[startPoint], startPoint);

	return false;
}

bool reset_king_ability(State* state, Piece kingPiece)
{
	if(!PIECE_STORE_TYPE(kingPiece, PIECE_TYPE_KING)) return false;

	if(PIECE_TEAM_MACRO(kingPiece) == TEAM_WHITE) *state = CLEAR_WHITE_CASTLE(*state);

	else if(PIECE_TEAM_MACRO(kingPiece) == TEAM_BLACK) *state = CLEAR_BLACK_CASTLE(*state);

	return true;
}

bool reset_rook_ability(State* state, Piece rookPiece, Point rookPoint)
{
	if(!PIECE_STORE_TYPE(rookPiece, PIECE_TYPE_ROOK)) return false;

	if(rookPoint == WROOK_QSIDE_POINT) *state = CLEAR_WHITE_QSIDE(*state);

	else if(rookPoint == WROOK_KSIDE_POINT) *state = CLEAR_WHITE_KSIDE(*state);

	else if(rookPoint == BROOK_QSIDE_POINT) *state = CLEAR_BLACK_QSIDE(*state);

	else if(rookPoint == BROOK_KSIDE_POINT) *state = CLEAR_BLACK_KSIDE(*state);

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
