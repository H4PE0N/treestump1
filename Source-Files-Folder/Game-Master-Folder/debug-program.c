
#include "../Engine-Logic-Folder/Header-Files-Folder/englog-include-file.h"
#include "../Chess-Engine-Folder/Header-Files-Folder/engine-include-file.h"
#include "../Game-Console-Folder/Header-Files-Folder/console-include-file.h"

// "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 1 0"
// "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 1 0"
// "8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - - 1 0"
// "r3k2r/Pppp1ppp/1b3nbN/nP6/BBP1P3/q4N2/Pp1P2PP/R2Q1RK1 w kq - 0 1"
// "rnbq1k1r/pp1Pbppp/2p5/8/2B5/8/PPP1NnPP/RNBQK2R w KQ - 1 8"
// "r4rk1/1pp1qppp/p1np1n2/2b1p1B1/2B1P1b1/P1NP1N2/1PP1QPPP/R4RK1 w - - 0 10"
// "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1"
// "4k2r/6r1/8/8/8/8/3R4/R3K3 w Qk - 0 1"

int main(int argc, char* argv[])
{
	srand(time(NULL));

	if(!extract_score_matrixs(TYPE_SCORE_MATRIX)) return false;

	create_hash_matrix(HASH_MATRIX);

	char* fenString = (argc >= 2) ? argv[1] : (char*) FEN_START_STRING;

	Piece* board; State state;
	if(!parse_create_board(&board, &state, fenString)) return false;

	Entry* hashTable = create_hash_table(HASH_TABLE_SIZE);


	print_console_board(board);

  print_console_state(state);

	int depth = 7;

	long startTime = clock();

	Move bestMove;
	engine_depth_move(&bestMove, board, state, hashTable, depth);

	double time = time_passed_since(startTime);

	char moveString[16];
	create_string_move(moveString, bestMove);

	printf("depth %d time: %.2f move: (%s)\n", depth, time, moveString);



	printf("free(hashTable);\n"); free(hashTable);

	printf("free(board);\n"); free(board);

	return false;
}
