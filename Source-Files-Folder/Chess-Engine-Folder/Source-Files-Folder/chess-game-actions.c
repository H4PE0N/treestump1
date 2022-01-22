
#include "../Header-Files-Folder/engine-include-file.h"

bool move_chess_piece(Piece* board, Info* info, Kings* kings, Move move)
{
	Piece startPiece = board[MOVE_START_MACRO(move)];

	Piece startTeam = (startPiece & PIECE_TEAM_MASK);

	if(!current_team_move(*info, startTeam)) return false;



	if(!correct_move_flag(&move, startPiece, *info))
	{
		return false;
	}

	if(!move_fully_legal(board, *info, *kings, move))
	{
		return false;
	}

	if(!execute_chess_move(board, info, kings, move))
	{
		return false;
	}

	return true;
}

// This function creates memory for an array of legal moves
// The memory has to be freed after use!! OBS!
// This function is trash, make it more specific for the pieces:
bool piece_legal_moves(Move** moveArray, const Piece board[], Info info, Kings kings, Point startPoint)
{
	if(!point_inside_board(startPoint)) return false;


	*moveArray = malloc(sizeof(Move) * 64);
	for(unsigned short index = 0; index < 64; index += 1)
	{
		(*moveArray)[index] = MOVE_NONE;
	}


	Piece startPiece = board[startPoint];


	unsigned short moveAmount = 0;


	for(unsigned short stopPoint = 0; stopPoint < BOARD_LENGTH; stopPoint += 1)
	{
		Move currentMove = START_MOVE_MACRO(startPoint) | STOP_MOVE_MACRO(stopPoint);

		if(!correct_move_flag(&currentMove, startPiece, info)) continue;

		if(move_fully_legal(board, info, kings, currentMove))
		{
			(*moveArray)[moveAmount] = currentMove;

			moveAmount += 1;
		}
	}

	return true;
}

bool team_legal_moves(Move** moveArray, const Piece board[], Info info, Kings kings, Piece pieceTeam)
{
	*moveArray = malloc(sizeof(Move) * 1024);

	for(unsigned short index = 0; index < 1024; index += 1)
	{
		(*moveArray)[index] = MOVE_NONE;
	}



	// if(!piece_team_exists(team)) return false;

	unsigned short movesAmount = 0;


	for(Point point = 0; point < BOARD_LENGTH; point += 1)
	{
		Piece currentTeam = (board[point] & PIECE_TEAM_MASK);

		if(currentTeam != pieceTeam) continue;


		Move* addingMoves;

		if(!piece_legal_moves(&addingMoves, board, info, kings, point))
		{
			continue;
		}


		unsigned short addingAmount = 0;

		while(addingMoves[addingAmount] != MOVE_NONE && addingMoves[addingAmount] >= 0)
		{
			addingAmount += 1;
		}

		for(unsigned short index = 0; index < addingAmount; index += 1)
		{
			(*moveArray)[movesAmount] = addingMoves[index];

			movesAmount += 1;
		}

		free(addingMoves);
	}

	return true;
}

// This function should give the move its correct flag
// To do that, it checks for patterns, but the move don't have to be legal,
// this function just sets the flag that it would have had to have.
bool correct_move_flag(Move* move, Piece piece, Info info)
{
	if(!move_inside_board(*move)) return false;

	Move moveFlag = (*move & MOVE_FLAG_MASK);

	if(double_move_ident(info, *move, piece))
	{
		moveFlag = MOVE_FLAG_DOUBLE;
	}
	else if(castle_move_ident(info, *move, piece))
	{
		moveFlag = MOVE_FLAG_CASTLE;
	}
	else if(passant_move_ident(info, *move, piece))
	{
		moveFlag = MOVE_FLAG_PASSANT;
	}
	else if(promote_move_ident(info, *move, piece))
	{
		if(moveFlag != MOVE_FLAG_KNIGHT && moveFlag != MOVE_FLAG_BISHOP && moveFlag != MOVE_FLAG_ROOK && moveFlag != MOVE_FLAG_QUEEN)
		{
			moveFlag = MOVE_FLAG_QUEEN; // This is the default value;
		}
	}
	else
	{
		moveFlag = MOVE_FLAG_NONE;
	}

	*move = ALLOC_MOVE_FLAG(*move, moveFlag);

	return true;
}

bool castle_move_ident(Info info, Move move, Piece piece)
{
	Piece pieceType = (piece & PIECE_TYPE_MASK);
	Piece pieceTeam = (piece & PIECE_TEAM_MASK);

	unsigned short fileOffset = ABS_SHORT_NUMBER(move_file_offset(move, pieceTeam));

	if(pieceType != PIECE_TYPE_KING) return false;

	if(fileOffset == KING_CASTLE_PAT || fileOffset == QUEEN_CASTLE_PAT) return true;

	return false;
}

bool passant_move_ident(Info info, Move move, Piece piece)
{
	Point stopPoint = MOVE_STOP_MACRO(move);

	Piece pieceTeam = (piece & PIECE_TEAM_MASK);
	Piece pieceType = (piece & PIECE_TYPE_MASK);

	unsigned short stopFile = POINT_FILE_MACRO(stopPoint);
	unsigned short stopRank = POINT_RANK_MACRO(stopPoint);

	unsigned short passantFile = INFO_PASSANT_MACRO(info);

	if(pieceType != PIECE_TYPE_PAWN) return false;

	if((stopFile + 1) != passantFile) return false;

	// Piece is pawn, and stopFile is passant file

	if(pieceTeam == PIECE_TEAM_WHITE && stopRank == (BLACK_PAWN_RANK + BLACK_MOVE_VALUE) ) return true;

	if(pieceTeam == PIECE_TEAM_BLACK && stopRank == (WHITE_PAWN_RANK + WHITE_MOVE_VALUE) ) return true;

	return false;
}

bool promote_move_ident(Info info, Move move, Piece piece)
{
	Point stopPoint = MOVE_STOP_MACRO(move);

	Piece pieceTeam = (piece & PIECE_TEAM_MASK);
	Piece pieceType = (piece & PIECE_TYPE_MASK);

	unsigned short stopRank = POINT_RANK_MACRO(stopPoint);

	if(pieceType != PIECE_TYPE_PAWN) return false;

	if(pieceTeam == PIECE_TEAM_WHITE && stopRank == BLACK_START_RANK) return true;

	if(pieceTeam == PIECE_TEAM_BLACK && stopRank == WHITE_START_RANK) return true;

	return false;
}

bool double_move_ident(Info info, Move move, Piece piece)
{
	Piece pieceTeam = (piece & PIECE_TEAM_MASK);
	Piece pieceType = (piece & PIECE_TYPE_MASK);

	unsigned short rankOffset = move_rank_offset(move, pieceTeam);

	if(pieceType == PIECE_TYPE_PAWN && rankOffset == 2) return true;

	return false;
}

bool best_computer_move(Move* move, const Piece board[], Info info, Kings kings, unsigned short team, signed short depth)
{
	if(depth <= 0) return false;

	// if(!piece_team_exists(pieceTeam)) return false;

	Move* moveArray;
	if(!team_legal_moves(&moveArray, board, info, kings, TEAM_PIECE_MACRO(team)))
	{
		printf("if(!team_legal_moves(&moves, board, info, kings, pieceTeam))\n");

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

	if(!team_legal_moves(&moveArray, board, infoCopy, kings, TEAM_PIECE_MACRO(currentTeam)))
	{
		printf("if(!team_legal_moves(&moves, board, info, kings, pieceTeam))\n");

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

signed short team_state_value(const Piece board[], Info info, Kings kings, unsigned short team)
{
	return 0;
}
