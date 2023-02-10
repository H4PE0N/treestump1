
#include "../Header-Files-Folder/engine-include-file.h"

long search_depth_nodes(const Piece board[], State state, uint8_t currentTeam, int depth, long startClock, int seconds)
{
	if(depth <= 0) return 1;

	if(timing_limit_ended(startClock, seconds)) return 1;

	Move* moveArray; int moveAmount;
	if(!team_legal_moves(&moveArray, &moveAmount, board, state, currentTeam)) return 1;

	long localNodes = 0;

	for(int index = 0; index < moveAmount; index += 1)
	{
		Move currentMove = moveArray[index];

		localNodes += search_move_nodes(board, state, currentTeam, (depth - 1), currentMove, startClock, seconds);
	}
	free(moveArray); return localNodes;
}

long search_move_nodes(const Piece board[], State state, uint8_t currentTeam, int depth, Move move, long startClock, int seconds)
{
	State stateCopy = ALLOC_CURRENT_STATE(state, currentTeam);

	Piece* boardCopy = copy_chess_board(board);

	if(!execute_chess_move(boardCopy, &stateCopy, move))
	{ free(boardCopy); return 1; }

	uint8_t nextTeam = NORMAL_TEAM_ENEMY(currentTeam);

	long moveNodes = search_depth_nodes(boardCopy, stateCopy, nextTeam, depth, startClock, seconds);

	free(boardCopy); return moveNodes;
}
