
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
