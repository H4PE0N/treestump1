
#include "../Header-Files-Folder/engine-include-file.h"

void qsort_moves_values(Move* moveArray, signed short* moveValues, short length, unsigned short team)
{
	qsort_moves_indexis(moveArray, moveValues, 0, length - 1, team);
}

void qsort_moves_indexis(Move* moveArray, signed short* moveValues, short index1, short index2, unsigned short team)
{
	if(index1 >= index2) return;

	short partIndex = partly_qsort_moves(moveArray, moveValues, index1, index2, team);

	qsort_moves_indexis(moveArray, moveValues, index1, partIndex - 1, team);
	qsort_moves_indexis(moveArray, moveValues, partIndex + 1, index2, team);
}

short partly_qsort_moves(Move* moveArray, signed short* moveValues, short index1, short index2, unsigned short team)
{
	signed short pivotValue = moveValues[index2];

	short iIndex = (index1 - 1);

	for(short jIndex = index1; jIndex <= index2 - 1; jIndex += 1)
	{
		if((team == TEAM_WHITE && moveValues[jIndex] > pivotValue) ||
			(team == TEAM_BLACK && moveValues[jIndex] < pivotValue))
		{
			qswap_moves_values(moveArray, moveValues, ++iIndex, jIndex);
		}
	}
	qswap_moves_values(moveArray, moveValues, iIndex + 1, index2);

	return (iIndex + 1);
}

void qswap_moves_values(Move* moveArray, signed short* moveValues, short index1, short index2)
{
	qswap_array_moves(moveArray, index1, index2);
	qswap_move_values(moveValues, index1, index2);
}

void qswap_array_moves(Move* moveArray, short index1, short index2)
{
	Move tempMove = moveArray[index1];
	moveArray[index1] = moveArray[index2];
	moveArray[index2] = tempMove;
}

void qswap_move_values(signed short* moveValues, short index1, short index2)
{
	short tempValue = moveValues[index1];
	moveValues[index1] = moveValues[index2];
	moveValues[index2] = tempValue;
}
