
#ifndef MOVE_ARRAY_SORTER_H
#define MOVE_ARRAY_SORTER_H

void qsort_moves_values(Move*, short*, unsigned short, unsigned short);

void qsort_moves_indexis(Move*, short*, short, short, unsigned short);

short partly_qsort_moves(Move*, short*, short, short, unsigned short);

void qswap_moves_values(Move*, short*, short, short);

#endif
