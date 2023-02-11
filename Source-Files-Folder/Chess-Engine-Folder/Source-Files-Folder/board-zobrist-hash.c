
#include "../Header-Files-Folder/engine-include-file.h"

ZobrKeys ZOBRIST_KEYS;

Entry* create_hash_table(int tableSize)
{
	Entry* hashTable = malloc(sizeof(Entry) * tableSize);

	for(int index = 0; index < tableSize; index += 1)
	{
		hashTable[index] = (Entry) {.hash = 0, .depth = 0, .score = 0, .flag = 0};
	}
	return hashTable;
}

void create_squares_keys(uint64_t squareKeys[BOARD_POINTS][12])
{
	for(Point point = 0; point < BOARD_POINTS; point += 1)
	{
		create_pieces_keys(squareKeys, point);
	}
}

void create_pieces_keys(uint64_t squareKeys[BOARD_POINTS][12], Point point)
{
	for(uint8_t index = 0; index < 12; index += 1)
	{
		squareKeys[point][index] = create_random_uint64(0, (UINT64_MAX - 1));
	}
}

void create_castles_keys(uint64_t castlesKeys[16])
{
	for(uint8_t index = 0; index < 16; index += 1)
	{
		castlesKeys[index] = create_random_uint64(0, (UINT64_MAX - 1));
	}
}

void create_passant_keys(uint64_t passantKeys[8])
{
	for(uint8_t index = 0; index < 8; index += 1)
	{
		passantKeys[index] = create_random_uint64(0, (UINT64_MAX - 1));
	}
}

void create_zobrist_keys(ZobrKeys* zobristKeys)
{
	create_squares_keys(ZOBRIST_KEYS.squares);

	create_castles_keys(ZOBRIST_KEYS.castles);

	create_passant_keys(ZOBRIST_KEYS.passant);

	ZOBRIST_KEYS.current = create_random_uint64(0, (UINT64_MAX - 1));
}

uint64_t create_random_uint64(uint64_t minimum, uint64_t maximum)
{
	return (rand() % (maximum - minimum + 1) + minimum);
}

uint64_t create_zobrist_hash(const Piece board[], State state)
{
	uint64_t zobristHash = create_squares_hash(board);

	uint8_t passantFile = STATE_PASSANT_MACRO(state);
	if(passantFile != 0) zobristHash ^= ZOBRIST_KEYS.passant[passantFile - 1];

	uint8_t castles = STATE_CASTLES_MACRO(state);
	zobristHash ^= ZOBRIST_KEYS.castles[castles];

	if(STATE_STORE_CURRENT(state, TEAM_WHITE)) zobristHash ^= ZOBRIST_KEYS.current;

	return zobristHash;
}

uint64_t create_squares_hash(const Piece board[])
{
	uint64_t zobristHash = 0;

	for(Point point = 0; point < BOARD_POINTS; point += 1)
	{
		uint8_t type = PIECE_TYPE_MACRO(board[point]);
		uint8_t team = PIECE_TEAM_MACRO(board[point]);

		if(!TEAM_TYPE_EXISTS(team, type)) continue;

		int pieceIndex = ((type - 1) * 2 + (team - 1));

		zobristHash ^= ZOBRIST_KEYS.squares[point][pieceIndex];
	}
	return zobristHash;
}
