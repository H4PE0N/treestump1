
#include "../Header-Files-Folder/engine-include-file.h"

bool move_pattern_valid(Move move, Piece piece)
{
	Piece pieceType = (piece & PIECE_TYPE_MASK);
	unsigned short team = PIECE_TEAM_MACRO(piece);

	if(pieceType == PIECE_TYPE_NONE) return false;

	else if(pieceType == PIECE_TYPE_PAWN)
	{
		return pawn_pattern_handler(move, team);
	}
	else if(pieceType == PIECE_TYPE_KNIGHT)
	{
		return knight_pattern_handler(move, team);
	}
	else if(pieceType == PIECE_TYPE_BISHOP)
	{
		return bishop_pattern_handler(move, team);
	}
	else if(pieceType == PIECE_TYPE_ROOK)
	{
		return rook_pattern_handler(move, team);
	}
	else if(pieceType == PIECE_TYPE_QUEEN)
	{
		return queen_pattern_handler(move, team);
	}
	else if(pieceType == PIECE_TYPE_KING)
	{
		return king_pattern_handler(move, team);
	}
	else return false;
}


// ###########################################################################################################


bool pawn_pattern_handler(Move move, unsigned short team)
{
	Move moveFlag = (move & MOVE_FLAG_MASK);

	if(moveFlag == MOVE_FLAG_DOUBLE)
	{
		return double_pattern_valid(move, team);
	}
	else if(moveFlag == MOVE_FLAG_PASSANT)
	{
		return passant_pattern_valid(move, team);
	}
	else if(moveFlag == MOVE_FLAG_KNIGHT || moveFlag == MOVE_FLAG_BISHOP || moveFlag == MOVE_FLAG_ROOK || moveFlag == MOVE_FLAG_QUEEN)
	{
		return promote_pattern_valid(move, team);
	}
	else if(moveFlag == MOVE_FLAG_NONE)
	{
		return pawn_pattern_valid(move, team);
	}
	else return false;
}

bool knight_pattern_handler(Move move, unsigned short team)
{
	Move moveFlag = (move & MOVE_FLAG_MASK);

	if(moveFlag == MOVE_FLAG_NONE)
	{
		return knight_pattern_valid(move, team);
	}
	else return false;
}

bool bishop_pattern_handler(Move move, unsigned short team)
{
	Move moveFlag = (move & MOVE_FLAG_MASK);

	if(moveFlag == MOVE_FLAG_NONE)
	{
		return bishop_pattern_valid(move, team);
	}

	else return false;
}

bool rook_pattern_handler(Move move, unsigned short team)
{
	Move moveFlag = (move & MOVE_FLAG_MASK);

	if(moveFlag == MOVE_FLAG_NONE)
	{
		return rook_pattern_valid(move, team);
	}

	else return false;
}

bool queen_pattern_handler(Move move, unsigned short team)
{
	Move moveFlag = (move & MOVE_FLAG_MASK);

	if(moveFlag == MOVE_FLAG_NONE)
	{
		return queen_pattern_valid(move, team);
	}
	else return false;
}

bool king_pattern_handler(Move move, unsigned short team)
{
	Move moveFlag = (move & MOVE_FLAG_MASK);

	if(moveFlag == MOVE_FLAG_CASTLE)
	{
		return castle_pattern_valid(move, team);
	}
	else if(moveFlag == MOVE_FLAG_NONE)
	{
		return king_pattern_valid(move, team);
	}
	else return false;
}


// ###########################################################################################################


bool pawn_pattern_valid(Move move, unsigned short team)
{
	unsigned short fileOffset = ABS_SHORT_NUMBER(move_file_offset(move, team));
	signed short rankOffset = move_rank_offset(move, team);

	if(fileOffset == 1 && rankOffset == 1) return true;

	else if(fileOffset == 0 && rankOffset == 1) return true;

	else return false;
}

bool knight_pattern_valid(Move move, unsigned short team)
{
	unsigned short fileOffset = ABS_SHORT_NUMBER(move_file_offset(move, team));
	unsigned short rankOffset = ABS_SHORT_NUMBER(move_rank_offset(move, team));

	if(fileOffset == 1 && rankOffset == 2) return true;

	else if(fileOffset == 2 && rankOffset == 1) return true;

	else return false;
}

bool bishop_pattern_valid(Move move, unsigned short team)
{
	unsigned short fileOffset = ABS_SHORT_NUMBER(move_file_offset(move, team));
	unsigned short rankOffset = ABS_SHORT_NUMBER(move_rank_offset(move, team));

	if(fileOffset == rankOffset) return true;

	else return false;
}

bool rook_pattern_valid(Move move, unsigned short team)
{
	unsigned short fileOffset = ABS_SHORT_NUMBER(move_file_offset(move, team));
	unsigned short rankOffset = ABS_SHORT_NUMBER(move_rank_offset(move, team));

	if(fileOffset == 0 || rankOffset == 0) return true;

	else return false;
}

bool queen_pattern_valid(Move move, unsigned short team)
{
	unsigned short fileOffset = ABS_SHORT_NUMBER(move_file_offset(move, team));
	unsigned short rankOffset = ABS_SHORT_NUMBER(move_rank_offset(move, team));

	if(fileOffset == rankOffset) return true;

	else if(fileOffset == 0 || rankOffset == 0) return true;

	else return false;
}

bool king_pattern_valid(Move move, unsigned short team)
{
	unsigned short fileOffset = ABS_SHORT_NUMBER(move_file_offset(move, team));
	unsigned short rankOffset = ABS_SHORT_NUMBER(move_rank_offset(move, team));

	if(fileOffset <= 1 && rankOffset <= 1) return true;

	else return false;
}


// ###########################################################################################################


bool castle_pattern_valid(Move move, unsigned short team)
{
	Point startPoint = MOVE_START_MACRO(move);

	unsigned short startFile = POINT_FILE_MACRO(startPoint);
	unsigned short startRank = POINT_RANK_MACRO(startPoint);

	unsigned short fileOffset = ABS_SHORT_NUMBER(move_file_offset(move, team));
	unsigned short rankOffset = ABS_SHORT_NUMBER(move_rank_offset(move, team));


	if(startFile != KING_START_FILE) return false;


	if(team == TEAM_WHITE)
	{
		if(startRank != WHITE_START_RANK) return false;
	}

	else if(team == TEAM_BLACK)
	{
		if(startRank != BLACK_START_RANK) return false;
	}

	else return false;

	// and that it moves only sideways 2 steps

	if(rankOffset != 0) return false;

	if(fileOffset != KING_CASTLE_PAT && fileOffset != QUEEN_CASTLE_PAT) return false;

	return true;
}

bool double_pattern_valid(Move move, unsigned short team)
{
	unsigned short fileOffset = ABS_SHORT_NUMBER(move_file_offset(move, team));
	signed short rankOffset = move_rank_offset(move, team);

	if(fileOffset != 0 || rankOffset != 2) return false;


	unsigned short startRank = POINT_RANK_MACRO(MOVE_START_MACRO(move));


	if(team == TEAM_WHITE && startRank == WHITE_PAWN_RANK) return true;

	else if(team == TEAM_BLACK && startRank == BLACK_PAWN_RANK) return true;

	else return false;
}

bool passant_pattern_valid(Move move, unsigned short team)
{
	unsigned short fileOffset = ABS_SHORT_NUMBER(move_file_offset(move, team));
	signed short rankOffset = move_rank_offset(move, team);

	if(fileOffset == 1 && rankOffset == 1) return true;

	else return false;
}

bool promote_pattern_valid(Move move, unsigned short team)
{
	unsigned short stopRank = POINT_RANK_MACRO(MOVE_STOP_MACRO(move));

	if(team == TEAM_WHITE)
	{
		if(stopRank != BLACK_START_RANK) return false;
	}

	else if(team == TEAM_BLACK)
	{
		if(stopRank != WHITE_START_RANK) return false;
	}

	else return false;


	unsigned short fileOffset = ABS_SHORT_NUMBER(move_file_offset(move, team));
	signed short rankOffset = move_rank_offset(move, team);

	if(fileOffset == 1 && rankOffset == 1) return true;

	else if(fileOffset == 0 && rankOffset == 1) return true;

	else return false;
}
