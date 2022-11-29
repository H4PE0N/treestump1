
#include "../Header-Files-Folder/englog-include-file.h"

// This function is going to check if the move-pattern
// fits inside the board (pawn-takes, castling, pawn double jump)
// - the stop piece can't be of same team
// - the stop piece must be empty if the pawn moves forward
// - it must be a rook in the corner, if it is castle
// - the move path is clear (except for the knight)
bool move_pattern_fits(const Piece board[], Move move)
{
	if(!MOVE_INSIDE_BOARD(move)) return false;

	if(MOVE_STORE_FLAG(move, MOVE_FLAG_CASTLE))
		return castle_pattern_fits(board, move);

	if(MOVE_STORE_FLAG(move, MOVE_FLAG_PASSANT))
		return passant_pattern_fits(board, move);

	if(START_PIECE_TYPE(board, move) == PIECE_TYPE_PAWN)
		return pawn_pattern_fits(board, move);

	return normal_pattern_fits(board, move);
}

bool normal_pattern_fits(const Piece board[], Move move)
{
	if(!MOVE_INSIDE_BOARD(move)) return false;

	if(MOVE_POINTS_TEAM(board, move)) return false;

	return clear_moving_path(board, move);
}

bool passant_pattern_fits(const Piece board[], Move move)
{
	if(!MOVE_INSIDE_BOARD(move)) return false;

	Point startPoint = MOVE_START_MACRO(move);
	Point passantPoint = pawn_passant_point(move);

	if(POINT_PIECE_TYPE(board, startPoint) != PIECE_TYPE_PAWN) return false;
	if(POINT_PIECE_TYPE(board, passantPoint) != PIECE_TYPE_PAWN) return false;

	if(!BOARD_POINTS_ENEMY(board, startPoint, passantPoint)) return false;

	return !STOP_PIECE_EXISTS(board, move);
}

// - King is moving
// - Rook in the corner
// - Clear moving path
bool castle_pattern_fits(const Piece board[], Move castleMove)
{
	if(!MOVE_INSIDE_BOARD(castleMove)) return false;

	unsigned short startTeam = MOVE_START_TEAM(board, castleMove);

	if(START_PIECE_TYPE(board, castleMove) != PIECE_TYPE_KING) return false;

	Point rookPoint = castle_rook_point(castleMove);
	if(rookPoint == POINT_NONE) return false;

	Piece rookPieceType = POINT_PIECE_TYPE(board, rookPoint);
	unsigned short rookTeam = BOARD_POINT_TEAM(board, rookPoint);

	if(!((rookPieceType == PIECE_TYPE_ROOK) && (rookTeam == startTeam))) return false;

	Move kingRookMove = ALLOC_MOVE_STOP(castleMove, rookPoint);

	return clear_moving_path(board, kingRookMove);
}

Point castle_rook_point(Move castleMove)
{
	if(!MOVE_INSIDE_BOARD(castleMove)) return POINT_NONE;

	unsigned short kingPoint = MOVE_START_MACRO(castleMove);
	signed short movePattern = BOARD_MOVE_PATTERN(castleMove);

	if((kingPoint == WHITE_KING_POINT) && (movePattern == KSIDE_FILE_OFFSET))
		return WROOK_KSIDE_POINT;

	if((kingPoint == WHITE_KING_POINT) && (movePattern == QSIDE_FILE_OFFSET))
		return WROOK_QSIDE_POINT;

	if((kingPoint == BLACK_KING_POINT) && (movePattern == KSIDE_FILE_OFFSET))
		return BROOK_KSIDE_POINT;

	if((kingPoint == BLACK_KING_POINT) && (movePattern == QSIDE_FILE_OFFSET))
		return BROOK_QSIDE_POINT;

	return POINT_NONE;
}

bool pawn_pattern_fits(const Piece board[], Move move)
{
	if(!MOVE_INSIDE_BOARD(move)) return false;

	if(START_PIECE_TYPE(board, move) != PIECE_TYPE_PAWN) return false;

	Point startPoint = MOVE_START_MACRO(move);
	Point stopPoint = MOVE_STOP_MACRO(move);

	unsigned short startTeam = BOARD_POINT_TEAM(board, startPoint);
	unsigned short stopTeam = BOARD_POINT_TEAM(board, stopPoint);

	unsigned short fileOffset = abs(move_file_offset(move, startTeam));
	signed short rankOffset = move_rank_offset(move, startTeam);

	if((fileOffset == 0) && ((rankOffset == 1) || (rankOffset == 2)))
	{
		if(BOARD_POINT_EXISTS(board, stopPoint)) return false;
	}
	else if((fileOffset == 1) && (rankOffset == 1))
	{
		if(!NORMAL_TEAMS_ENEMY(startTeam, stopTeam)) return false;
	}
	return clear_moving_path(board, move);
}

bool clear_moving_path(const Piece board[], Move move)
{
	if(!MOVE_INSIDE_BOARD(move)) return false;

	if(START_PIECE_TYPE(board, move) == PIECE_TYPE_KNIGHT) return true;

	short rankFactor, fileFactor, moveSteps;
	if(!moving_path_values(&rankFactor, &fileFactor, &moveSteps, move)) return false;

	Point startPoint = MOVE_START_MACRO(move);
	Point stopPoint = MOVE_STOP_MACRO(move);

	short startRank = POINT_RANK_MACRO(startPoint);
	short startFile = POINT_FILE_MACRO(startPoint);

	for(short index = 0; index <= moveSteps; index += 1)
	{
		short currentFile = (startFile + index * fileFactor);
		short currentRank = (startRank + index * rankFactor);

		Point point = RANK_FILE_POINT(currentRank, currentFile);

		if((point == startPoint) || (point == stopPoint)) continue;

		if(BOARD_POINT_EXISTS(board, point)) return false;
	}
	return true;
}

bool moving_path_values(signed short* rankFactor, signed short* fileFactor, short* moveSteps, Move move)
{
	short rankOffset = normal_rank_offset(move);
	short fileOffset = normal_file_offset(move);

	short absRankOffset = abs(rankOffset);
	short absFileOffset = abs(fileOffset);

	bool moveStraight = ((absRankOffset == 0) || (absFileOffset == 0));
	bool moveDiagonal = (absRankOffset == absFileOffset);

	if(!(moveStraight || moveDiagonal)) return false;

	*fileFactor = MOVE_OFFSET_FACTOR(fileOffset);
	*rankFactor = MOVE_OFFSET_FACTOR(rankOffset);

	*moveSteps = MAX_NUMBER_VALUE(absRankOffset, absFileOffset);

	return true;
}
