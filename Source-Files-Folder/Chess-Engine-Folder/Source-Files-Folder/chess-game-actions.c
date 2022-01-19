
#include "../Header-Files-Folder/engine-include-file.h"

bool move_chess_piece(Piece* board, Info* info, Kings* kings, Move move)
{
	Piece startPiece = board[MOVE_START_MACRO(move)];

	Piece startTeam = (startPiece & PIECE_TEAM_MASK);

	if(!current_team_move(*info, startTeam)) return false;


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
	memset(*moveArray, MOVE_NONE, 64);


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

// This function should give the move its correct flag
// To do that, it checks for patterns, but the move don't have to be legal,
// this function just sets the flag that it would have had to have.
bool correct_move_flag(Move* move, Piece piece, Info info)
{
	if(!move_inside_board(*move)) return false;

	Piece pieceTeam = (piece & PIECE_TEAM_MASK);
	Piece pieceType = (piece & PIECE_TYPE_MASK);

	Point stopPoint = MOVE_STOP_MACRO(*move);

	unsigned short stopFile = POINT_FILE_MACRO(stopPoint);
	unsigned short stopRank = POINT_RANK_MACRO(stopPoint);

	unsigned short fileOffset = ABS_SHORT_NUMBER(move_file_offset(*move, pieceTeam));
	unsigned short rankOffset = ABS_SHORT_NUMBER(move_rank_offset(*move, pieceTeam));

	unsigned short passantFile = INFO_PASSANT_MACRO(info);

	Move moveFlag = (*move & MOVE_FLAG_MASK);

	if(pieceType == PIECE_TYPE_PAWN && rankOffset == 2 && fileOffset == 0)
	{
		moveFlag = MOVE_FLAG_DOUBLE;
	}
	else if(pieceType == PIECE_TYPE_KING && rankOffset == 0 && fileOffset == 2)
	{
		moveFlag = MOVE_FLAG_CASTLE;
	}
	else if((pieceType == PIECE_TYPE_PAWN) && ((stopFile + 1) == passantFile) &&
		((pieceTeam == PIECE_TEAM_WHITE && stopRank == BLACK_PAWN_RANK + BLACK_MOVE_VALUE) ||
		(pieceTeam == PIECE_TEAM_BLACK && stopRank == WHITE_PAWN_RANK + WHITE_MOVE_VALUE)))
	{
		moveFlag = MOVE_FLAG_PASSANT;
	}
	else if((pieceType == PIECE_TYPE_PAWN) &&
		((pieceTeam == PIECE_TEAM_WHITE && stopRank == BLACK_START_RANK) ||
		(pieceTeam == PIECE_TEAM_BLACK && stopRank == WHITE_START_RANK)))
	{
		if(moveFlag != MOVE_FLAG_KNIGHT && moveFlag != MOVE_FLAG_BISHOP && moveFlag != MOVE_FLAG_ROOK && moveFlag != MOVE_FLAG_QUEEN)
		{
			moveFlag = MOVE_FLAG_QUEEN; // This is the default value;
		}
	}

	*move = ALLOC_MOVE_FLAG(*move, moveFlag);

	return true;
}
