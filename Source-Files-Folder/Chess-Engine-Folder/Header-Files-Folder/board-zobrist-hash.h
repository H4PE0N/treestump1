
#ifndef BOARD_ZOBRIST_HASH_H
#define BOARD_ZOBRIST_HASH_H

typedef struct ZobrKeys
{
	uint64_t squares[64][12];
	uint64_t passant[8];
	uint64_t castles[12];
	uint64_t current;
} ZobrKeys;

extern ZobrKeys ZOBRIST_KEYS;

Entry* create_hash_table(int tableSize);

void create_squares_keys(uint64_t squareKeys[BOARD_POINTS][12]);

void create_pieces_keys(uint64_t squareKeys[BOARD_POINTS][12], Point point);

void create_passant_keys(uint64_t passantKeys[8]);

void create_castles_keys(uint64_t castlesKeys[16]);

void create_zobrist_keys(ZobrKeys* zobristKeys);

uint64_t create_random_uint64(uint64_t minimum, uint64_t maximum);

uint64_t create_zobrist_hash(const Piece board[], State state);

uint64_t create_squares_hash(const Piece board[]);

#endif
