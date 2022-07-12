
#include "../Header-Files-Folder/engine-include-file.h"

long search_depth_nodes(const Piece board[], Info info, unsigned short currentTeam, short depth, long startClock, short seconds)
{
	if(depth <= 0) return 1;

	if(timing_limit_ended(startClock, seconds)) return 1;

	Move* moveArray;
	if(!team_legal_moves(&moveArray, board, info, currentTeam)) return 1;

	unsigned short moveAmount = move_array_amount(moveArray);

	long localNodes = 0;

	for(unsigned short index = 0; index < moveAmount; index += 1)
	{
		Move currentMove = moveArray[index];

		localNodes += search_move_nodes(board, info, currentTeam, (depth - 1), currentMove, startClock, seconds);
	}
	free(moveArray); return localNodes;
}

long search_move_nodes(const Piece board[], Info info, unsigned short currentTeam, short depth, Move move, long startClock, short seconds)
{
	Info infoCopy = info;
	infoCopy = ALLOC_INFO_TEAM(infoCopy, TEAM_INFO_MACRO(currentTeam));

	Piece* boardCopy = copy_chess_board(board);

	if(!move_chess_piece(boardCopy, &infoCopy, move))
	{ free(boardCopy); return 1; }

	unsigned short nextTeam = normal_team_enemy(currentTeam);

	long moveNodes = search_depth_nodes(boardCopy, infoCopy, nextTeam, depth, startClock, seconds);

	free(boardCopy); return moveNodes;
}
