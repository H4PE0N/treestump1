
#include "../Header-Files-Folder/engine-include-file.h"

bool castle_move_ident(Info info, Move move, Piece piece)
{
	Piece pieceType = (piece & PIECE_TYPE_MASK);
	unsigned short team = PIECE_TEAM_MACRO(piece);

	unsigned short fileOffset = ABS_SHORT_NUMBER(move_file_offset(move, team));

	if(pieceType != PIECE_TYPE_KING) return false;

	if(fileOffset == KING_CASTLE_PAT || fileOffset == QUEEN_CASTLE_PAT) return true;

	return false;
}

bool passant_move_ident(Info info, Move move, Piece piece)
{
	Point stopPoint = MOVE_STOP_MACRO(move);

	Piece pieceTeam = (piece & PIECE_TEAM_MASK);
	Piece pieceType = (piece & PIECE_TYPE_MASK);

	unsigned short stopFile = POINT_FILE_MACRO(stopPoint);
	unsigned short stopRank = POINT_RANK_MACRO(stopPoint);

	unsigned short passantFile = INFO_PASSANT_MACRO(info);

	if(pieceType != PIECE_TYPE_PAWN) return false;

	if((stopFile + 1) != passantFile) return false;

	// Piece is pawn, and stopFile is passant file

	if(pieceTeam == PIECE_TEAM_WHITE && stopRank == (BLACK_PAWN_RANK + BLACK_MOVE_VALUE) ) return true;

	if(pieceTeam == PIECE_TEAM_BLACK && stopRank == (WHITE_PAWN_RANK + WHITE_MOVE_VALUE) ) return true;

	return false;
}

bool promote_move_ident(Info info, Move move, Piece piece)
{
	Point stopPoint = MOVE_STOP_MACRO(move);

	Piece pieceTeam = (piece & PIECE_TEAM_MASK);
	Piece pieceType = (piece & PIECE_TYPE_MASK);

	unsigned short stopRank = POINT_RANK_MACRO(stopPoint);

	if(pieceType != PIECE_TYPE_PAWN) return false;

	if(pieceTeam == PIECE_TEAM_WHITE && stopRank == BLACK_START_RANK) return true;

	if(pieceTeam == PIECE_TEAM_BLACK && stopRank == WHITE_START_RANK) return true;

	return false;
}

bool double_move_ident(Info info, Move move, Piece piece)
{
	unsigned short team = PIECE_TEAM_MACRO(piece);
	Piece pieceType = (piece & PIECE_TYPE_MASK);

	unsigned short rankOffset = move_rank_offset(move, team);

	if(pieceType == PIECE_TYPE_PAWN && rankOffset == 2) return true;

	return false;
}
