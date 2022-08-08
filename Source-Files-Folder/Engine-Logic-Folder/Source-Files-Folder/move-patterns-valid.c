
#include "../Header-Files-Folder/englog-include-file.h"

bool pawn_pattern_valid(Move move, unsigned short team)
{
	unsigned short fileOffset = abs_move_foffset(move, team);
	signed short rankOffset = move_rank_offset(move, team);

	if(fileOffset == 1 && rankOffset == 1) return true;
	if(fileOffset == 0 && rankOffset == 1) return true;

	return false;
}

bool knight_pattern_valid(Move move, unsigned short team)
{
	unsigned short fileOffset = abs_move_foffset(move, team);
	unsigned short rankOffset = abs_move_roffset(move, team);

	if(fileOffset == 1 && rankOffset == 2) return true;
	if(fileOffset == 2 && rankOffset == 1) return true;

	return false;
}

bool bishop_pattern_valid(Move move, unsigned short team)
{
	unsigned short fileOffset = abs_move_foffset(move, team);
	unsigned short rankOffset = abs_move_roffset(move, team);

	return (fileOffset == rankOffset);
}

bool rook_pattern_valid(Move move, unsigned short team)
{
	unsigned short fileOffset = abs_move_foffset(move, team);
	unsigned short rankOffset = abs_move_roffset(move, team);

	return (fileOffset == 0 || rankOffset == 0);
}

bool queen_pattern_valid(Move move, unsigned short team)
{
	unsigned short fileOffset = abs_move_foffset(move, team);
	unsigned short rankOffset = abs_move_roffset(move, team);

	if(fileOffset == rankOffset) return true;
	if(fileOffset == 0 || rankOffset == 0) return true;

	return false;
}

bool king_pattern_valid(Move move, unsigned short team)
{
	unsigned short fileOffset = abs_move_foffset(move, team);
	unsigned short rankOffset = abs_move_roffset(move, team);

	return (fileOffset <= 1 && rankOffset <= 1);
}

bool castle_pattern_valid(Move move, unsigned short team)
{
	if(!normal_team_exists(team)) return false;

	Point kingPoint = MOVE_START_MACRO(move);
	signed short movePattern = board_move_pattern(move);

	if(team == TEAM_WHITE && kingPoint != WHITE_KING_POINT) return false;
	if(team == TEAM_BLACK && kingPoint != BLACK_KING_POINT) return false;

	return (movePattern == KSIDE_FILE_OFFSET || movePattern == QSIDE_FILE_OFFSET);
}

bool double_pattern_valid(Move move, unsigned short team)
{
	if(!normal_team_exists(team)) return false;

	signed short fileOffset = move_file_offset(move, team);
	signed short rankOffset = move_rank_offset(move, team);

	if(fileOffset != 0 || rankOffset != 2) return false;

	unsigned short startRank = MOVE_START_RANK(move);

	if(team == TEAM_WHITE && startRank == WHITE_PAWN_RANK) return true;
	if(team == TEAM_BLACK && startRank == BLACK_PAWN_RANK) return true;

	return false;
}

bool passant_pattern_valid(Move move, unsigned short team)
{
	if(!normal_team_exists(team)) return false;

	unsigned short fileOffset = abs_move_foffset(move, team);
	signed short rankOffset = move_rank_offset(move, team);

	unsigned short stopRank = MOVE_STOP_RANK(move);

	if(team == TEAM_WHITE && stopRank != (BLACK_PAWN_RANK + BLACK_MOVE_VALUE)) return false;
	if(team == TEAM_BLACK && stopRank != (WHITE_PAWN_RANK + WHITE_MOVE_VALUE)) return false;

	return (fileOffset == 1 && rankOffset == 1);
}

bool promote_pattern_valid(Move move, unsigned short team)
{
	if(!normal_team_exists(team)) return false;

	unsigned short stopRank = MOVE_STOP_RANK(move);

	if(team == TEAM_WHITE && stopRank != BLACK_START_RANK) return false;
	if(team == TEAM_BLACK && stopRank != WHITE_START_RANK) return false;

	return pawn_pattern_valid(move, team);
}
