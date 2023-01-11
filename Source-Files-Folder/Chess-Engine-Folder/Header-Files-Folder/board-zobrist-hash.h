
#ifndef BOARD_ZOBRIST_HASH_H
#define BOARD_ZOBRIST_HASH_H

extern uint64_t** hashMatrix;

uint64_t** create_uint64_matrix(int height, int width, uint64_t minimum, uint64_t maximum);

void free_uint64_matrix(uint64_t* matrix[], int height, int width);

uint64_t* random_uint64_array(int amount, uint64_t minimum, uint64_t maximum);

uint64_t create_random_uint64(uint64_t minimum, uint64_t maximum);

uint64_t create_zobrist_hash(uint64_t* hashMatrix[], const Piece board[], Info info);

#endif
