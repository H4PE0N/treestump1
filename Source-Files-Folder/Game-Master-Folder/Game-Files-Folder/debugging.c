
#include "../../Chess-Engine-Folder/Header-Files-Folder/engine-include-file.h"

// "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 1 0"
// "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 1 0"
// "8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - - 1 0"
// "r3k2r/Pppp1ppp/1b3nbN/nP6/BBP1P3/q4N2/Pp1P2PP/R2Q1RK1 w kq - 0 1"
// "rnbq1k1r/pp1Pbppp/2p5/8/2B5/8/PPP1NnPP/RNBQK2R w KQ - 1 8"
// "r4rk1/1pp1qppp/p1np1n2/2b1p1B1/2B1P1b1/P1NP1N2/1PP1QPPP/R4RK1 w - - 0 10"

// "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1"

// "4k2r/6r1/8/8/8/8/3R4/R3K3 w Qk - 0 1"

void foo(const Piece board[], Info info)
{
	unsigned short team = INFO_TEAM_MACRO(info);

	Move* moveArray = NULL;
	if(!team_legal_moves(&moveArray, board, info, team)) return;


	unsigned short moveAmount = move_array_amount(moveArray);
	if(moveAmount <= 0) { free(moveArray); return; }


	signed short* engineValues = NULL;
	if(!move_array_values(&engineValues, board, info, team, 1, moveArray, moveAmount))
	{ free(moveArray); return; }


	signed short* guessValues = NULL;
	if(!guess_moves_values(&guessValues, moveArray, moveAmount, board, info))
	{ free(moveArray); free(engineValues); return; }

	for(unsigned short index = 0; index < moveAmount; index += 1)
	{
		printf("#%d Guess=%d Engine=%d\n", index + 1, guessValues[index], engineValues[index]);
	}

	free(moveArray); free(engineValues); free(guessValues);
}

void print_chess_board(const Piece board[])
{
	for(unsigned short rank = 0; rank < BOARD_RANKS; rank += 1)
	{
		for(unsigned short file = 0; file < BOARD_FILES; file += 1)
		{
			Point point = RANK_POINT_MACRO(rank) | FILE_POINT_MACRO(file);

			Piece piece = board[point];

			unsigned short type = PIECE_TYPE_MACRO(piece);

			char symbol = '.';

			if((piece & PIECE_TEAM_MASK) == PIECE_TEAM_WHITE)
			{
				symbol = WHITE_TYPE_SYMBOLS[type];
			}
			else if((piece & PIECE_TEAM_MASK) == PIECE_TEAM_BLACK)
			{
				symbol = BLACK_TYPE_SYMBOLS[type];
			}

			printf("%c ", symbol);
		}
		printf("\n");
	}
}

int main(int argAmount, char* arguments[])
{
	if(argAmount < 2) return false;

	Piece* board;
	Info info;


	char* gameString = arguments[1];

	if(!parse_game_string(&board, &info, gameString))
	{
		printf("Could not parse game string!\n");

		return false;
	}

	print_chess_board(board);

	for(unsigned short rank = 0; rank < BOARD_RANKS; rank += 1)
	{
		for(unsigned short file = 0; file < BOARD_FILES; file += 1)
		{
			printf("%02d ", (rank * BOARD_FILES) + file);
		}
		printf("\n");
	}




	//foo(board, info);




	unsigned short startTeam = INFO_TEAM_MACRO(info);

	long startClock = clock();

	unsigned short seconds = 1;


	// unsigned short totalDepth = 10;
	//
	// for(unsigned short depth = 1; depth <= totalDepth; depth += 1)
	// {
	// 	printf("Depth=%d Nodes=%ld\n", depth, search_depth_nodes(board, info, startTeam, depth, startClock, seconds));
	// }




	// Move bestMove;
	// if(engine_depth_move(&bestMove, board, info, startTeam, 4))
	// {
	// 	printf("BestMove: [%d -> %d]\n", MOVE_START_MACRO(bestMove), MOVE_STOP_MACRO(bestMove));
	// }


	Move engineMove;
	if(!optimal_depth_move(&engineMove, board, info, startTeam, seconds))
	{
		printf("optimal_depth_move failed!\n");
	}

	//
	printf("Time: %.2f\n", time_passed_since(startClock));

	//
	//


	// printf("WK Point: %d BK Point: %d\n",
	// 	board_king_point(board, TEAM_WHITE),
	// 	board_king_point(board, TEAM_BLACK));

	// char* fenString;
	//
	// if(create_game_string(&fenString, board, info))
	// {
	// 	printf("[ %s ]\n", fenString);
	// 	free(fenString);
	// }
	//
	// printf("Value: %d\n", board_state_value(board, info));


	printf("free(board);\n");

	free(board);

	return 0;
}
