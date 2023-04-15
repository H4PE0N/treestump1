
#include "../Header-Files-Folder/engine-include-file.h"

bool amount_engine_moves(Move** moveArray, const Piece board[], State state, Entry* hashTable, uint8_t evalTeam, int depth, int amount)
{
	if((amount <= 0) && (depth <= 0)) return false;

	Move* engineMoves; int engineAmount;
	if(!sorted_engine_moves(&engineMoves, &engineAmount, board, state, hashTable, evalTeam, depth)) return false;

	*moveArray = create_move_array(amount);

	paste_capped_moves(*moveArray, amount, engineMoves, engineAmount);

	free(engineMoves); return true;
}

bool sorted_engine_moves(Move** moveArray, int* moveAmount, const Piece board[], State state, Entry* hashTable, uint8_t evalTeam, int depth)
{
	if(depth <= 0) return false;

	if(!team_legal_moves(moveArray, moveAmount, board, state)) return false;

	int* moveScores;
	if(!move_array_scores(&moveScores, board, state, hashTable, depth, *moveArray, *moveAmount)) return false;

	qsort_moves_scores(*moveArray, moveScores, *moveAmount, evalTeam);

	free(moveScores); return true;
}

bool move_array_scores(int** moveScores, const Piece board[], State state, Entry* hashTable, int depth, const Move moveArray[], int moveAmount)
{
	if(moveAmount <= 0) return false;

	*moveScores = create_score_array(moveAmount);

	int playerSign = CURRENT_TEAM_WEIGHT(state);

	for(int index = 0; index < moveAmount; index += 1)
	{
		int moveScore = chess_move_score(board, state, hashTable, depth, -MATE_SCORE, MATE_SCORE, playerSign, moveArray[index]);

		(*moveScores)[index] = moveScore;
	}
	return true;
}

int* create_score_array(int moveAmount)
{
	int* moveScores = malloc(sizeof(int) * moveAmount);

	memset(moveScores, 0, sizeof(int) * moveAmount);

	return moveScores;
}
