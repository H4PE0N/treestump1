
#include "../Header-Files-Folder/engine-include-file.h"

bool best_computer_move(Move* move, const Piece board[], Info info, Kings kings, unsigned short team, signed short depth)
{
	if(depth <= 0) return false;

	// if(!piece_team_exists(pieceTeam)) return false;

	Move* moveArray;
	if(!team_legal_moves(&moveArray, board, info, kings, team))
	{
		return false;
	}


	unsigned short movesAmount = move_array_amount(moveArray);

	if(movesAmount <= 0)
	{
		free(moveArray);

		return false;
	}

	Move bestMove = moveArray[0];
	signed short bestValue = MIN_BOARD_VALUE;

	for(unsigned short index = 0; index < movesAmount; index += 1)
	{
		Move currentMove = moveArray[index];



		Info infoCopy = info;
		infoCopy = ALLOC_INFO_TEAM(infoCopy, TEAM_INFO_MACRO(team));

		Kings kingsCopy = kings;

		Piece* boardCopy = malloc(sizeof(Piece) * BOARD_LENGTH);
		memcpy(boardCopy, board, sizeof(Piece) * BOARD_LENGTH);


		if(!move_chess_piece(boardCopy, &infoCopy, &kingsCopy, currentMove))
		{
			// For some reson, the computer cant move!

			free(boardCopy);

			continue;
		}

		unsigned short nextTeam = normal_team_enemy(team);

		signed short currentValue = board_depth_value(boardCopy, infoCopy, kingsCopy, (depth - 1), MIN_BOARD_VALUE, MAX_BOARD_VALUE, team, nextTeam);

		printf("CurrentMove: [%d -> %d]\tCurrentValue: %d\n", MOVE_START_MACRO(currentMove), MOVE_STOP_MACRO(currentMove), currentValue);

		free(boardCopy);


		if(currentValue > bestValue)
		{
			bestMove = currentMove;
			bestValue = currentValue;
		}
	}

	free(moveArray);

	*move = bestMove;

	return true;
}

unsigned short board_depth_value(const Piece board[], Info info, Kings kings, signed short depth, signed short alpha, signed short beta, unsigned short team, unsigned short currentTeam)
{
	if(!normal_team_exists(team) || !normal_team_exists(currentTeam)) return 0;

	// Base-case, Should return the v alue of the board
	if(depth <= 0) return team_state_value(board, info, kings, team);


	Info infoCopy = info;
	infoCopy = ALLOC_INFO_TEAM(infoCopy, TEAM_INFO_MACRO(currentTeam));

	Move* moveArray;

	if(!team_legal_moves(&moveArray, board, infoCopy, kings, currentTeam))
	{
		return false;
	}


	unsigned short movesAmount = move_array_amount(moveArray);

	if(movesAmount <= 0)
	{
		free(moveArray);

		return team_state_value(board, info, kings, team);
	}

	signed short bestValue = (currentTeam == team) ? MIN_BOARD_VALUE : MAX_BOARD_VALUE;

	// This is very slow, and makes the program run MUCH SLOWER (3s vs 73s)
	//sort_pruning_moves(moves, amount, board, info, currentTeam);

	for(unsigned short index = 0; index < movesAmount; index += 1)
	{
		Move currentMove = moveArray[index];

		infoCopy = info;
		infoCopy = ALLOC_INFO_TEAM(infoCopy, TEAM_INFO_MACRO(currentTeam));

		Kings kingsCopy = kings;

		Piece* boardCopy = malloc(sizeof(Piece) * BOARD_LENGTH);
		memcpy(boardCopy, board, sizeof(Piece) * BOARD_LENGTH);

		if(!move_chess_piece(boardCopy, &infoCopy, &kingsCopy, currentMove))
		{
			free(boardCopy);

			continue;
		}

		unsigned short nextTeam = normal_team_enemy(currentTeam);
		signed short currentValue = board_depth_value(boardCopy, infoCopy, kingsCopy, (depth - 1), alpha, beta, team, nextTeam);

		free(boardCopy);

		if(currentTeam == team && currentValue > bestValue)	bestValue = currentValue;
		if(currentTeam != team && currentValue < bestValue)	bestValue = currentValue;

		if(currentTeam == team && currentValue > alpha)			alpha = currentValue;
		if(currentTeam != team && currentValue < beta)			beta = currentValue;

		if(beta <= alpha) break;
	}

	free(moveArray);

	return bestValue;
}
