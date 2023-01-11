
#ifndef MOVE_ARRAY_SORTER_H
#define MOVE_ARRAY_SORTER_H

void qsort_moves_scores(Move* moveArray, int* moveScores, int amount, uint8_t team);

void qsort_moves_indexis(Move* moveArray, int* moveScores, int index1, int index2, uint8_t team);

int partly_qsort_moves(Move* moveArray, int* moveScores, int index1, int index2, uint8_t team);

void qswap_moves_scores(Move* moveArray, int* moveScores, int index1, int index2);

void qswap_move_scores(int* moveScores, int index1, int index2);

void qswap_array_moves(Move* moveArray, int index1, int index2);

#endif
