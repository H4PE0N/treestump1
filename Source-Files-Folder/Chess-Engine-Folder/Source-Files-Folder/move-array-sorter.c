
#include "../Header-Files-Folder/engine-include-file.h"

void qsort_moves_scores(Move* moveArray, signed short* moveScores, short length, unsigned short team)
{
	qsort_moves_indexis(moveArray, moveScores, 0, length - 1, team);
}

void qsort_moves_indexis(Move* moveArray, signed short* moveScores, short index1, short index2, unsigned short team)
{
	if(index1 >= index2) return;

	short partIndex = partly_qsort_moves(moveArray, moveScores, index1, index2, team);

	qsort_moves_indexis(moveArray, moveScores, index1, partIndex - 1, team);
	qsort_moves_indexis(moveArray, moveScores, partIndex + 1, index2, team);
}

short partly_qsort_moves(Move* moveArray, signed short* moveScores, short index1, short index2, unsigned short team)
{
	signed short pivotScore = moveScores[index2];

	short iIndex = (index1 - 1);

	for(short jIndex = index1; jIndex <= index2 - 1; jIndex += 1)
	{
		if(!((team == TEAM_WHITE) && (moveScores[jIndex] > pivotScore)) &&
			!((team == TEAM_BLACK) && (moveScores[jIndex] < pivotScore))) continue;

		qswap_moves_scores(moveArray, moveScores, ++iIndex, jIndex);
	}
	qswap_moves_scores(moveArray, moveScores, iIndex + 1, index2);

	return (iIndex + 1);
}

void qswap_moves_scores(Move* moveArray, signed short* moveScores, short index1, short index2)
{
	qswap_array_moves(moveArray, index1, index2);
	qswap_move_scores(moveScores, index1, index2);
}

void qswap_array_moves(Move* moveArray, short index1, short index2)
{
	Move tempMove = moveArray[index1];
	moveArray[index1] = moveArray[index2];
	moveArray[index2] = tempMove;
}

void qswap_move_scores(signed short* moveScores, short index1, short index2)
{
	short tempScore = moveScores[index1];
	moveScores[index1] = moveScores[index2];
	moveScores[index2] = tempScore;
}
