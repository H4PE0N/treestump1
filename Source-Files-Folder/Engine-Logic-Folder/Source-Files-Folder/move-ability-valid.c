
#include "../Header-Files-Folder/englog-include-file.h"

bool move_ability_valid(Move move, State state)
{
	if(MOVE_STORE_FLAG(move, MOVE_FLAG_CASTLE))
		return castle_ability_valid(move, state);

	if(MOVE_STORE_FLAG(move, MOVE_FLAG_PASSANT))
		return passant_ability_valid(move, state);

	return true;
}

bool castle_ability_valid(Move move, State state)
{
	if(!MOVE_INSIDE_BOARD(move)) return false;

	Point kingPoint = MOVE_START_MACRO(move);
	int8_t movePattern = BOARD_MOVE_PATTERN(move);

	if((kingPoint == WHITE_KING_POINT) && (movePattern == KSIDE_FILE_OFFSET))
		return (MASK_WHITE_KSIDE(state) == STATE_WHITE_KSIDE);

	if((kingPoint == WHITE_KING_POINT) && (movePattern == QSIDE_FILE_OFFSET))
		return (MASK_WHITE_QSIDE(state) == STATE_WHITE_QSIDE);

	if((kingPoint == BLACK_KING_POINT) && (movePattern == KSIDE_FILE_OFFSET))
		return (MASK_BLACK_KSIDE(state) == STATE_BLACK_KSIDE);

	if((kingPoint == BLACK_KING_POINT) && (movePattern == QSIDE_FILE_OFFSET))
		return (MASK_BLACK_QSIDE(state) == STATE_BLACK_QSIDE);

	return false;
}

bool passant_ability_valid(Move move, State state)
{
	if(!MOVE_INSIDE_BOARD(move)) return false;

	return ((MOVE_STOP_FILE(move) + 1) == STATE_PASSANT_MACRO(state));
}
