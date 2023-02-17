
#include "../Header-Files-Folder/engine-include-file.h"

long search_depth_nodes(const Piece board[], State state, int depth, long startClock, int seconds)
{
	if(depth <= 0) return 1;

	if(timing_limit_ended(startClock, seconds)) return 1;

	Move* moveArray; int moveAmount;
	if(!team_legal_moves(&moveArray, &moveAmount, board, state)) return 1;

	long localNodes = 0;

	for(int index = 0; index < moveAmount; index += 1)
	{
		Move currentMove = moveArray[index];

		localNodes += search_move_nodes(board, state, (depth - 1), currentMove, startClock, seconds);
	}
	free(moveArray); return localNodes;
}

long search_move_nodes(const Piece board[], State state, int depth, Move move, long startClock, int seconds)
{
	Piece* boardCopy = copy_chess_board(board);

	long moveNodes = search_move_nodes_t(boardCopy, state, depth, move, startClock, seconds);

	free(boardCopy); return moveNodes;
}

long search_move_nodes_t(Piece* boardCopy, State stateCopy, int depth, Move move, long startClock, int seconds)
{
	if(!execute_chess_move(boardCopy, &stateCopy, move)) return 1;

	return search_depth_nodes(boardCopy, stateCopy, depth, startClock, seconds);
}
