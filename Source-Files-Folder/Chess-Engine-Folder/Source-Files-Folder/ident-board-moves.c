
#include "../Header-Files-Folder/engine-include-file.h"

bool castle_move_ident(Info info, Move move, Piece piece)
{
	if(!move_inside_board(move)) return false;
	if(!chess_piece_exists(piece)) return false;

	Piece pieceType = MASK_PIECE_TYPE(piece);

	if(pieceType != PIECE_TYPE_KING) return false;

	signed short movePattern = board_move_pattern(move);

	return (movePattern == KSIDE_FILE_OFFSET || movePattern == QSIDE_FILE_OFFSET);
}

bool passant_move_ident(Info info, Move move, Piece piece)
{
	if(!move_inside_board(move)) return false;
	if(!chess_piece_exists(piece)) return false;

	Point stopPoint = MOVE_STOP_MACRO(move);

	unsigned short team = PIECE_TEAM_MACRO(piece);
	Piece pieceType = MASK_PIECE_TYPE(piece);

	unsigned short stopFile = POINT_FILE_MACRO(stopPoint);
	unsigned short stopRank = POINT_RANK_MACRO(stopPoint);

	unsigned short passantFile = INFO_PASSANT_MACRO(info);

	if(pieceType != PIECE_TYPE_PAWN) return false;
	if((stopFile + 1) != passantFile) return false;

	if(team == TEAM_WHITE && stopRank == (BLACK_PAWN_RANK + BLACK_MOVE_VALUE)) return true;
	if(team == TEAM_BLACK && stopRank == (WHITE_PAWN_RANK + WHITE_MOVE_VALUE)) return true;

	return false;
}

bool promote_move_ident(Info info, Move move, Piece piece)
{
	if(!move_inside_board(move)) return false;
	if(!chess_piece_exists(piece)) return false;

	unsigned short team = PIECE_TEAM_MACRO(piece);
	Piece pieceType = MASK_PIECE_TYPE(piece);

	unsigned short stopRank = MOVE_STOP_RANK(move);

	if(pieceType != PIECE_TYPE_PAWN) return false;

	if(team == TEAM_WHITE && stopRank == BLACK_START_RANK) return true;
	if(team == TEAM_BLACK && stopRank == WHITE_START_RANK) return true;

	return false;
}

bool double_move_ident(Info info, Move move, Piece piece)
{
	if(!move_inside_board(move)) return false;
	if(!chess_piece_exists(piece)) return false;

	unsigned short team = PIECE_TEAM_MACRO(piece);
	Piece pieceType = MASK_PIECE_TYPE(piece);

	unsigned short rankOffset = move_rank_offset(move, team);

	return (pieceType == PIECE_TYPE_PAWN && rankOffset == +2);
}
