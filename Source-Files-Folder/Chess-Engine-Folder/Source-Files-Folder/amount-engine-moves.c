
#include "../Header-Files-Folder/engine-include-file.h"

bool amount_engine_moves(Move** moveArray, const Piece board[], Info info, unsigned short team, short depth, short amount)
{
	if((amount <= 0) && (depth <= 0)) return false;

	Move* engineMoves; short engineAmount;
	if(!sorted_engine_moves(&engineMoves, &engineAmount, board, info, team, depth)) return false;

	*moveArray = create_move_array(amount);

	paste_capped_moves(*moveArray, amount, engineMoves, engineAmount);

	free(engineMoves); return true;
}

bool sorted_engine_moves(Move** moveArray, short* moveAmount, const Piece board[], Info info, unsigned short evalTeam, short depth)
{
	if(depth <= 0) return false;

	int currTeam = INFO_TEAM_MACRO(info);

	if(!team_legal_moves(moveArray, moveAmount, board, info, currTeam)) return false;

	short* moveScores;
	if(!move_array_scores(&moveScores, board, info, currTeam, depth, *moveArray, *moveAmount)) return false;

	qsort_moves_scores(*moveArray, moveScores, *moveAmount, evalTeam);

	free(moveScores); return true;
}

bool move_array_scores(short** moveScores, const Piece board[], Info info, unsigned short team, short depth, const Move moveArray[], short moveAmount)
{
	if(moveAmount <= 0) return false;

	*moveScores = create_short_array(moveAmount);

	int playerSign = TEAM_SCORE_WEIGHT(team);

	for(unsigned short index = 0; index < moveAmount; index += 1)
	{
		Move currentMove = moveArray[index];

		signed short moveScore = chess_move_score(board, info, depth, MIN_STATE_SCORE, MAX_STATE_SCORE, playerSign, currentMove);

		(*moveScores)[index] = moveScore;
	}
	return true;
}

short* create_short_array(unsigned short length)
{
	short* array = malloc(sizeof(short) * (length + 1));
	for(unsigned short index = 0; index < (length + 1); index += 1)
	{
		array[index] = 0;
	}
	return array;
}
