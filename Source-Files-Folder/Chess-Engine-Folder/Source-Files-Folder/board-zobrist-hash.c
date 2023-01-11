
#include "../Header-Files-Folder/engine-include-file.h"

uint64_t** hashMatrix;

uint64_t** create_uint64_matrix(int height, int width, uint64_t minimum, uint64_t maximum)
{
	uint64_t** matrix = malloc(sizeof(uint64_t*) * height);

	for(int index = 0; index < height; index += 1)
	{
		matrix[index] = random_uint64_array(width, minimum, maximum);
	}
	return matrix;
}

void free_uint64_matrix(uint64_t* matrix[], int height, int width)
{
	for(int index = 0; index < height; index += 1)
	{ free(matrix[index]); } free(matrix);
}

uint64_t* random_uint64_array(int amount, uint64_t minimum, uint64_t maximum)
{
	uint64_t* array = malloc(sizeof(uint64_t) * amount);

	for(int index = 0; index < amount; index += 1)
	{
		array[index] = create_random_uint64(minimum, maximum);
	}
	return array;
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
