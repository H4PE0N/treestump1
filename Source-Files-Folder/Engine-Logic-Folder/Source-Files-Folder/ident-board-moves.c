
#include "../Header-Files-Folder/englog-include-file.h"

bool castle_move_ident(State state, Move move, Piece piece)
{
	if(!MOVE_INSIDE_BOARD(move) || !CHESS_PIECE_EXISTS(piece)) return false;

	if(MASK_PIECE_TYPE(piece) != PIECE_TYPE_KING) return false;

	int8_t movePattern = BOARD_MOVE_PATTERN(move);

	return ((movePattern == KSIDE_FILE_OFFSET) || (movePattern == QSIDE_FILE_OFFSET));
}

bool passant_move_ident(State state, Move move, Piece piece)
{
	if(!MOVE_INSIDE_BOARD(move) || !CHESS_PIECE_EXISTS(piece)) return false;

	Point stopPoint = MOVE_STOP_MACRO(move);

	uint8_t team = PIECE_TEAM_MACRO(piece);
	uint8_t stopRank = POINT_RANK_MACRO(stopPoint);

	if(MASK_PIECE_TYPE(piece) != PIECE_TYPE_PAWN) return false;
	if((POINT_FILE_MACRO(stopPoint) + 1) != STATE_PASSANT_MACRO(state)) return false;

	if((team == TEAM_WHITE) && (stopRank == (BLACK_PAWN_RANK + BLACK_MOVE_VALUE))) return true;
	if((team == TEAM_BLACK) && (stopRank == (WHITE_PAWN_RANK + WHITE_MOVE_VALUE))) return true;

	return false;
}

bool promote_move_ident(State state, Move move, Piece piece)
{
	if(!MOVE_INSIDE_BOARD(move) || !CHESS_PIECE_EXISTS(piece)) return false;

	uint8_t team = PIECE_TEAM_MACRO(piece);
	uint8_t stopRank = MOVE_STOP_RANK(move);

	if(MASK_PIECE_TYPE(piece) != PIECE_TYPE_PAWN) return false;

	if((team == TEAM_WHITE) && (stopRank == BLACK_START_RANK)) return true;
	if((team == TEAM_BLACK) && (stopRank == WHITE_START_RANK)) return true;

	return false;
}

bool double_move_ident(State state, Move move, Piece piece)
{
	if(!MOVE_INSIDE_BOARD(move) || !CHESS_PIECE_EXISTS(piece)) return false;

	uint8_t team = PIECE_TEAM_MACRO(piece);
	Piece pieceType = MASK_PIECE_TYPE(piece);

	int8_t rankOffset = move_rank_offset(move, team);

	return ((pieceType == PIECE_TYPE_PAWN) && (rankOffset == 2));
}
