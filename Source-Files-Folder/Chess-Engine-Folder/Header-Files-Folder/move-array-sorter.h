
#ifndef MOVE_ARRAY_SORTER_H
#define MOVE_ARRAY_SORTER_H

void qsort_moves_values(Move* moveArray, signed short* moveValues, short length, unsigned short team);

void qsort_moves_indexis(Move* moveArray, signed short* moveValues, short index1, short index2, unsigned short team);

short partly_qsort_moves(Move* moveArray, signed short* moveValues, short index1, short index2, unsigned short team);

void qswap_moves_values(Move* moveArray, signed short* moveValues, short index1, short index2);

void qswap_move_values(signed short* moveValues, short index1, short index2);

void qswap_array_moves(Move* moveArray, short index1, short index2);

#endif
