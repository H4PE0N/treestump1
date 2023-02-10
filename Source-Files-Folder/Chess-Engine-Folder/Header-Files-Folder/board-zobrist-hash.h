
#ifndef BOARD_ZOBRIST_HASH_H
#define BOARD_ZOBRIST_HASH_H

extern uint64_t HASH_MATRIX[64][12];

Entry* create_hash_table(int tableSize);

void create_hash_matrix(uint64_t hashMatrix[BOARD_POINTS][12]);

void create_pieces_hashes(uint64_t hashMatrix[BOARD_POINTS][12], Point point);

uint64_t create_random_uint64(uint64_t minimum, uint64_t maximum);

uint64_t create_zobrist_hash(uint64_t* hashMatrix[], const Piece board[], State state);

#endif
