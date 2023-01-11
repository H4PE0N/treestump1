
#include "../Header-Files-Folder/engine-include-file.h"

bool optimal_depth_move(Move* move, const Piece board[], Info info, Entry* hashTable, short seconds)
{
	int team = INFO_TEAM_MACRO(info);

	Move* moveArray; int moveAmount;
	if(!team_legal_moves(&moveArray, &moveAmount, board, info, team)) return false;

	int playerSign = TEAM_SCORE_WEIGHT(team);

	bool result = search_depths_move(move, board, info, hashTable, playerSign, seconds, moveArray, moveAmount);

	free(moveArray); return result;

	return false;
}

bool search_depths_move(Move* move, const Piece board[], Info info, Entry* hashTable, int playerSign, short seconds, const Move moveArray[], int moveAmount)
{
	if(moveAmount <= 0) return false;

	*move = moveArray[0];

	if(moveAmount == 1) return true;

	long startClock = clock();

	Move engineMove = moveArray[0]; signed short engineScore = 0;

	for(unsigned short depth = 1;; depth += 1)
	{
		if(!choose_timing_move(&engineMove, &engineScore, board, info, hashTable, depth, playerSign, startClock, seconds, moveArray, moveAmount)) return false;

		if(timing_limit_ended(startClock, seconds)) break;

		*move = engineMove;

		char moveString[16];
		create_string_move(moveString, engineMove);
		printf("info depth %d time %d move %s score %d\n", depth, (int) (time_passed_since(startClock) * 1000), moveString, engineScore);
	}
	return true;
}

bool choose_timing_move(Move* bestMove, signed short* bestScore, const Piece board[], Info info, Entry* hashTable, short depth, int playerSign, long startClock, short seconds, const Move moveArray[], int moveAmount)
{
	if(moveAmount <= 0) return false;

	*bestMove = moveArray[0];
	*bestScore = MIN_STATE_SCORE;

	for(int index = 0; index < moveAmount; index += 1)
	{
		if(timing_limit_ended(startClock, seconds)) return true;

		Move currMove = moveArray[index];

		int currScore = chess_move_score(board, info, hashTable, depth, MIN_STATE_SCORE, MAX_STATE_SCORE, playerSign, currMove);

		if(currScore > *bestScore)
		{
			*bestMove = currMove; *bestScore = currScore;
		}
	}
	return true;
}

double time_passed_since(long startClock)
{
	return (double) (clock() - startClock) / CLOCKS_PER_SEC;
}

bool timing_limit_ended(long startClock, short seconds)
{
	return (time_passed_since(startClock) >= seconds);
}
