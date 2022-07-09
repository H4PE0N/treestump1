
#ifndef MOVE_ARRAY_SORTER_H
#define MOVE_ARRAY_SORTER_H

void qsort_moves_values(Move*, signed short*, short, unsigned short);

void qsort_moves_indexis(Move*, signed short*, short, short, unsigned short);

short partly_qsort_moves(Move*, signed short*, short, short, unsigned short);

void qswap_moves_values(Move*, signed short*, short, short);

void qswap_move_values(signed short*, short, short);

void qswap_array_moves(Move*, short, short);

#endif
