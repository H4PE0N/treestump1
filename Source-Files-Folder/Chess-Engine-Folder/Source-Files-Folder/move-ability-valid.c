
#include "../Header-Files-Folder/engine-include-file.h"

bool move_ability_valid(Move move, Piece piece, Info info)
{
	if(!chess_piece_exists(piece)) return false;

	unsigned short team = PIECE_TEAM_MACRO(piece);
	Move moveFlag = MASK_MOVE_FLAG(move);

	if(moveFlag == MOVE_FLAG_CASTLE)
		return castle_ability_valid(move, info, team);

	else if(moveFlag == MOVE_FLAG_PASSANT)
		return passant_ability_valid(move, info);

	return true;
}

bool castle_ability_valid(Move move, Info info, unsigned short team)
{
	if(!move_inside_board(move)) return false;
	if(!normal_team_exists(team)) return false;

	signed short movePattern = board_move_pattern(move);

	if(team == TEAM_WHITE && movePattern == KING_CASTLE_PAT)
	{
		if(info & INFO_WHITE_KING) return true;
	}
	else if(team == TEAM_WHITE && movePattern == QUEEN_CASTLE_PAT)
	{
		if(info & INFO_WHITE_QUEEN) return true;
	}
	else if(team == TEAM_BLACK && movePattern == KING_CASTLE_PAT)
	{
		if(info & INFO_BLACK_KING) return true;
	}
	else if(team == TEAM_BLACK && movePattern == QUEEN_CASTLE_PAT)
	{
		if(info & INFO_BLACK_QUEEN) return true;
	}
	return false;
}

bool passant_ability_valid(Move move, Info info)
{
	if(!move_inside_board(move)) return false;

	unsigned short passantFile = INFO_PASSANT_MACRO(info);

	return ( (MOVE_STOP_FILE(move) + 1) == passantFile);
}
