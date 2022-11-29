
#include "../Header-Files-Folder/engine-include-file.h"

bool optimal_depth_move(Move* move, const Piece board[], Info info, unsigned short team, short seconds)
{
	Move* moveArray; short moveAmount;
	if(!team_legal_moves(&moveArray, &moveAmount, board, info, team)) return false;

	bool result = search_depths_move(move, board, info, team, seconds, moveArray, moveAmount);

	free(moveArray); return result;
}

bool search_depths_move(Move* move, const Piece board[], Info info, unsigned short team, short seconds, const Move moveArray[], short moveAmount)
{
	if(moveAmount <= 0) return false;

	*move = moveArray[0];

	if(moveAmount == 1) return true;

	long startClock = clock();

	Move engineMove = moveArray[0]; signed short engineValue = 0;

	for(unsigned short depth = 1;; depth += 1)
	{
		if(!choose_timing_move(&engineMove, &engineValue, board, info, team, depth, startClock, seconds, moveArray, moveAmount)) return false;

		if(timing_limit_ended(startClock, seconds)) break;

		char moveString[16];
		create_string_move(moveString, engineMove);

		printf("info depth %d time %d move %s value %d\n", depth, (int) (time_passed_since(startClock) * 1000), moveString, engineValue);

		if(current_mate_value(engineValue, team)) break;
	}
	*move = engineMove; return true;
}

bool choose_timing_move(Move* move, signed short* value, const Piece board[], Info info, unsigned short team, short depth, long startClock, short seconds, const Move moveArray[], short moveAmount)
{
	if(moveAmount <= 0) return false;

	Move bestMove = moveArray[0];
	signed short bestValue = team_weight_value(MIN_STATE_VALUE, team);

	for(unsigned short index = 0; index < moveAmount; index += 1)
	{
		if(timing_limit_ended(startClock, seconds)) return true;

		Move currentMove = moveArray[index];

		short currentValue;
		if(!chess_move_value(&currentValue, board, info, team, (depth - 1), MIN_STATE_VALUE, MAX_STATE_VALUE, currentMove)) continue;

		if(update_mate_value(currentMove, currentValue, &bestMove, &bestValue, team)) break;

		update_move_value(currentMove, currentValue, &bestMove, &bestValue, team);
	}
	*move = bestMove; *value = bestValue; return true;
}

double time_passed_since(long startClock)
{
	return (double) (clock() - startClock) / CLOCKS_PER_SEC;
}

bool timing_limit_ended(long startClock, short seconds)
{
	return (time_passed_since(startClock) >= seconds);
}
