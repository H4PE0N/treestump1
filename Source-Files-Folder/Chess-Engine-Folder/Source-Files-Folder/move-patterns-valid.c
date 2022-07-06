
#include "../Header-Files-Folder/engine-include-file.h"

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

	return (fileOffset == rankOffset);
}

bool rook_pattern_valid(Move move, unsigned short team)
{
	unsigned short fileOffset = ABS_SHORT_NUMBER(move_file_offset(move, team));
	unsigned short rankOffset = ABS_SHORT_NUMBER(move_rank_offset(move, team));

	return (fileOffset == 0 || rankOffset == 0);
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

	return (fileOffset <= 1 && rankOffset <= 1);
}

bool castle_pattern_valid(Move move, unsigned short team)
{
	unsigned short startFile = MOVE_START_FILE(move);
	unsigned short startRank = MOVE_START_RANK(move);

	unsigned short fileOffset = ABS_SHORT_NUMBER(move_file_offset(move, team));
	unsigned short rankOffset = ABS_SHORT_NUMBER(move_rank_offset(move, team));

	if(startFile != KING_START_FILE) return false;

	if(team == TEAM_WHITE && startRank != WHITE_START_RANK) return false;

	else if(team == TEAM_BLACK && startRank != BLACK_START_RANK) return false;

	else return false;

	return (rankOffset == 0 && (fileOffset == KING_CASTLE_PAT || fileOffset == QUEEN_CASTLE_PAT));
}

bool double_pattern_valid(Move move, unsigned short team)
{
	unsigned short fileOffset = ABS_SHORT_NUMBER(move_file_offset(move, team));
	signed short rankOffset = move_rank_offset(move, team);

	if(fileOffset != 0 || rankOffset != 2) return false;

	unsigned short startRank = MOVE_START_RANK(move);

	if(team == TEAM_WHITE && startRank == WHITE_PAWN_RANK) return true;

	else if(team == TEAM_BLACK && startRank == BLACK_PAWN_RANK) return true;

	else return false;
}

bool passant_pattern_valid(Move move, unsigned short team)
{
	unsigned short fileOffset = ABS_SHORT_NUMBER(move_file_offset(move, team));
	signed short rankOffset = move_rank_offset(move, team);

	return (fileOffset == 1 && rankOffset == 1);

	// Maybe check if stopRank is the correct rank
}

bool promote_pattern_valid(Move move, unsigned short team)
{
	unsigned short stopRank = POINT_RANK_MACRO(MOVE_STOP_MACRO(move));

	if(team == TEAM_WHITE && stopRank != BLACK_START_RANK) return false;

	else if(team == TEAM_BLACK && stopRank != WHITE_START_RANK) return false;

	else return false;

	return pawn_pattern_valid(move, team);
}
