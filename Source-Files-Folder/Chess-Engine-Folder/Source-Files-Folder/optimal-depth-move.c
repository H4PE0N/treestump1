
#include "../Header-Files-Folder/engine-include-file.h"

bool optimal_depth_move(Move* move, const Piece board[], State state, Entry* hashTable, int seconds)
{
	Move* moveArray; int moveAmount;
	if(!team_legal_moves(&moveArray, &moveAmount, board, state)) return false;

	bool result = search_depths_move(move, board, state, hashTable, seconds, moveArray, moveAmount);

	free(moveArray); return result;
}

bool search_depths_move(Move* move, const Piece board[], State state, Entry* hashTable, int seconds, const Move moveArray[], int moveAmount)
{
	if(moveAmount <= 0) return false;

	*move = moveArray[0];

	if(moveAmount == 1) return true;

	int playerSign = CURRENT_TEAM_WEIGHT(state);

	long startClock = clock();

	Move engineMove = moveArray[0]; int engineScore = 0;

	for(unsigned short depth = 1;; depth += 1)
	{
		if(!choose_timing_move(&engineMove, &engineScore, board, state, hashTable, depth, playerSign, startClock, seconds, moveArray, moveAmount)) return false;

		if(timing_limit_ended(startClock, seconds)) break;

		*move = engineMove;

		char moveString[16];
		create_string_move(moveString, engineMove);
		printf("state depth %d time %d move %s score %d\n", depth, (int) (time_passed_since(startClock) * 1000), moveString, engineScore);

		if((playerSign * engineScore) <= MATE_SCORE) return true;
	}
	return true;
}

bool choose_timing_move(Move* bestMove, int* bestScore, const Piece board[], State state, Entry* hashTable, int depth, int playerSign, long startClock, int seconds, const Move moveArray[], int moveAmount)
{
	if(moveAmount <= 0) return false;

	*bestMove = moveArray[0]; *bestScore = MIN_STATE_SCORE;

	for(int index = 0; index < moveAmount; index += 1)
	{
		if(timing_limit_ended(startClock, seconds)) return true;

		Move currMove = moveArray[index];

		int currScore = chess_move_score(board, state, hashTable, depth, MIN_STATE_SCORE, MAX_STATE_SCORE, playerSign, currMove);

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

bool timing_limit_ended(long startClock, int seconds)
{
	return (time_passed_since(startClock) >= seconds);
}
