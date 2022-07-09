
#include "../Header-Files-Folder/engine-include-file.h"

bool move_ability_valid(Move move, Info info)
{
	if(MOVE_STORE_FLAG(move, MOVE_FLAG_CASTLE))
		return castle_ability_valid(move, info);

	if(MOVE_STORE_FLAG(move, MOVE_FLAG_PASSANT))
		return passant_ability_valid(move, info);

	return true;
}

bool castle_ability_valid(Move move, Info info)
{
	if(!move_inside_board(move)) return false;

	unsigned short kingPoint = MOVE_START_MACRO(move);
	signed short movePattern = board_move_pattern(move);

	if(kingPoint == WHITE_KING_POINT && movePattern == KSIDE_FILE_OFFSET)
		return (MASK_WHITE_KSIDE(info) == INFO_WHITE_KSIDE);

	if(kingPoint == WHITE_KING_POINT && movePattern == QSIDE_FILE_OFFSET)
		return (MASK_WHITE_QSIDE(info) == INFO_WHITE_QSIDE);

	if(kingPoint == BLACK_KING_POINT && movePattern == KSIDE_FILE_OFFSET)
		return (MASK_BLACK_KSIDE(info) == INFO_BLACK_KSIDE);

	if(kingPoint == BLACK_KING_POINT && movePattern == QSIDE_FILE_OFFSET)
		return (MASK_BLACK_QSIDE(info) == INFO_BLACK_QSIDE);

	return false;
}

bool passant_ability_valid(Move move, Info info)
{
	if(!move_inside_board(move)) return false;

	unsigned short passantFile = INFO_PASSANT_MACRO(info);

	return ( (MOVE_STOP_FILE(move) + 1) == passantFile);
}
