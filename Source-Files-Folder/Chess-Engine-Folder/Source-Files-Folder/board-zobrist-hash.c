
#include "../Header-Files-Folder/engine-include-file.h"

uint64_t HASH_MATRIX[64][12];

Entry* create_hash_table(int tableSize)
{
	Entry* hashTable = malloc(sizeof(Entry) * tableSize);

	for(int index = 0; index < tableSize; index += 1)
	{
		hashTable[index] = (Entry) {.hash = 0, .depth = 0, .score = 0, .flag = 0};
	}
	return hashTable;
}

void create_hash_matrix(uint64_t hashMatrix[BOARD_LENGTH][12])
{
	for(Point point = 0; point < BOARD_LENGTH; point += 1)
	{
		create_pieces_hashes(hashMatrix, point);
	}
}

void create_pieces_hashes(uint64_t hashMatrix[BOARD_LENGTH][12], Point point)
{
	for(uint8_t index = 0; index < 12; index += 1)
	{
		uint64_t random64bit = create_random_uint64(0, (UINT64_MAX - 1));

		hashMatrix[point][index] = random64bit;
	}
}

uint64_t create_random_uint64(uint64_t minimum, uint64_t maximum)
{
	return (rand() % (maximum - minimum + 1) + minimum);
}

uint64_t create_zobrist_hash(uint64_t* hashMatrix[], const Piece board[], Info info)
{
	uint64_t zobristHash = 0;
	for(Point point = 0; point < BOARD_LENGTH; point += 1)
	{
		if(!CHESS_PIECE_EXISTS(board[point])) continue;

		uint8_t type = PIECE_TYPE_MACRO(board[point]);
		uint8_t team = PIECE_TEAM_MACRO(board[point]);

		int pieceIndex = ((type - 1) * 2 + (team - 1));

		zobristHash ^= hashMatrix[point][pieceIndex];
	}
	return zobristHash;
}
