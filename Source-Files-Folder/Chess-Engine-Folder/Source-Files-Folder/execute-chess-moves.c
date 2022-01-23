
#include "../Header-Files-Folder/engine-include-file.h"

// This function is going to just move the pieces around,
// based on what action (flag) the move has
// This function is not going to check any validation
bool execute_chess_move(Piece* board, Info* info, Kings* kings, Move move)
{
	Move moveFlag = (move & MOVE_FLAG_MASK);

	if(moveFlag == MOVE_FLAG_KNIGHT || moveFlag == MOVE_FLAG_BISHOP || moveFlag == MOVE_FLAG_ROOK || moveFlag == MOVE_FLAG_QUEEN)
	{
		return execute_promote_move(board, info, kings, move);
	}
	else if(moveFlag == MOVE_FLAG_CASTLE)
	{
		return execute_castle_move(board, info, kings, move);
	}
	else if(moveFlag == MOVE_FLAG_PASSANT)
	{
		return execute_passant_move(board, info, kings, move);
	}
	else if(moveFlag == MOVE_FLAG_DOUBLE)
	{
		return execute_double_move(board, info, kings, move);
	}
	else
	{
		return execute_normal_move(board, info, kings, move);
	}
}

bool update_king_point(Kings* kings, Piece pieceTeam, Point point)
{
	if(pieceTeam == PIECE_TEAM_WHITE)
	{
		*kings = ALLOC_KINGS_WHITE(*kings, WHITE_KINGS_MACRO(point));
	}
	else if(pieceTeam == PIECE_TEAM_BLACK)
	{
		*kings = ALLOC_KINGS_BLACK(*kings, BLACK_KINGS_MACRO(point));
	}
	else return false;

	return true;
}

// This function is going to execute all normal moves
// - It just moves the piece to a specific point
bool execute_normal_move(Piece* board, Info* info, Kings* kings, Move move)
{
	if(!move_inside_board(move)) return false;

	Point startPoint = MOVE_START_MACRO(move);
	Point stopPoint = MOVE_STOP_MACRO(move);


	unsigned short startFile = POINT_FILE_MACRO(startPoint);
	unsigned short startRank = POINT_RANK_MACRO(startPoint);

	unsigned short stopFile = POINT_FILE_MACRO(stopPoint);
	unsigned short stopRank = POINT_RANK_MACRO(stopPoint);


	Piece startType = (board[startPoint] & PIECE_TYPE_MASK);
	Piece stopType = (board[stopPoint] & PIECE_TYPE_MASK);

	Piece startPiece = board[startPoint];

	Piece startTeam = (startPiece & PIECE_TEAM_MASK);

	board[stopPoint] = startPiece;
	board[startPoint] = PIECE_NONE;

	if(startType == PIECE_TYPE_KING)
	{
		if(!update_king_point(kings, (startPiece & PIECE_TEAM_MASK), stopPoint))
		{
			return false;
		}

		if(startTeam == PIECE_TEAM_WHITE)
		{
			// Resets the bits of white king and queen
			*info = (*info & ~INFO_WHITE_KING & ~INFO_WHITE_QUEEN);
		}
		else if(startTeam == PIECE_TEAM_BLACK)
		{
			// Resets the bits of black king and queen
			*info = (*info & ~INFO_BLACK_KING & ~INFO_BLACK_QUEEN);
		}
	}

	// If a rook is moving, or a rook is taken: The castle ability must be set to false
	if(startType == PIECE_TYPE_ROOK || stopType == PIECE_TYPE_ROOK)
	{
		unsigned short rookRank = (startType == PIECE_TYPE_ROOK) ? startRank : stopRank;
		unsigned short rookFile = (startType == PIECE_TYPE_ROOK) ? startFile : stopFile;

		if(rookRank == WHITE_START_RANK && rookFile == 0)
		{
			*info = (*info & ~INFO_WHITE_QUEEN);
		}
		else if(rookRank == WHITE_START_RANK && rookFile == (BOARD_FILES - 1))
		{
			*info = (*info & ~INFO_WHITE_KING);
		}
		if(rookRank == BLACK_START_RANK && rookFile == 0)
		{
			*info = (*info & ~INFO_BLACK_QUEEN);
		}
		else if(rookRank == BLACK_START_RANK && rookFile == (BOARD_FILES - 1))
		{
			*info = (*info & ~INFO_BLACK_KING);
		}
	}

	*info = ALLOC_INFO_PASSANT(*info, 0);

	return true;
}

// This function is going to execute a castle
// - It has to move both the king and the rook
bool execute_castle_move(Piece* board, Info* info, Kings* kings, Move move)
{
	Point kingPoint = MOVE_START_MACRO(move);

	Piece kingPiece = board[kingPoint];

	unsigned short kingTeam = PIECE_TEAM_MACRO(kingPiece);

	Point rookPoint = castle_rook_point(move, TEAM_PIECE_MACRO(kingTeam));

	if(rookPoint == POINT_NONE) return false;


	Piece rookPiece = board[rookPoint];


	signed short fileOffset = move_file_offset(move, kingTeam);

	Point newKingPoint = MOVE_STOP_MACRO(move);
	Point newRookPoint = (fileOffset == KING_CASTLE_PAT) ? (newKingPoint - 1) : (newKingPoint + 1);

	board[newKingPoint] = kingPiece;
	board[kingPoint] = PIECE_NONE;

	board[newRookPoint] = rookPiece;
	board[rookPoint] = PIECE_NONE;


	if(!update_king_point(kings, TEAM_PIECE_MACRO(kingTeam), newKingPoint))
	{
		return false;
	}

	*info = ALLOC_INFO_PASSANT(*info, 0);


	if(kingTeam == TEAM_WHITE)
	{
		// Resets the bits of white king and queen
		*info = (*info & ~INFO_WHITE_KING & ~INFO_WHITE_QUEEN);
	}
	else if(kingTeam == TEAM_BLACK)
	{
		// Resets the bits of black king and queen
		*info = (*info & ~INFO_BLACK_KING & ~INFO_BLACK_QUEEN);
	}


	return true;
}

// This function is going to execute a promotion
// - It has to get the promotion (KNIGHT, BISHOP, ROOK, QUEEN)
// and swap the piece at the STOP point in the move
bool execute_promote_move(Piece* board, Info* info, Kings* kings, Move move)
{
	if(!move_inside_board(move)) return false;


	Point startPoint = MOVE_START_MACRO(move);
	Point stopPoint = MOVE_STOP_MACRO(move);


	Piece pieceTeam = (board[startPoint] & PIECE_TEAM_MASK);
	Piece pieceType = PIECE_BLANK;


	Move moveFlag = (move & MOVE_FLAG_MASK);


	if(moveFlag == MOVE_FLAG_ROOK) pieceType = PIECE_TYPE_ROOK;

	else if(moveFlag == MOVE_FLAG_BISHOP) pieceType = PIECE_TYPE_BISHOP;

	else if(moveFlag == MOVE_FLAG_KNIGHT) pieceType = PIECE_TYPE_KNIGHT;

	else if(moveFlag == MOVE_FLAG_QUEEN) pieceType = PIECE_TYPE_QUEEN;

	else return false;


	board[stopPoint] = (pieceTeam | pieceType);
	board[startPoint] = PIECE_NONE;


	*info = ALLOC_INFO_PASSANT(*info, 0);

	return true;
}

// This function is going to execute en passant take
// - It has to update the passant point to POINT_NONE
bool execute_passant_move(Piece* board, Info* info, Kings* kings, Move move)
{
	if(!move_inside_board(move)) return false;


	Point startPoint = MOVE_START_MACRO(move);
	Point stopPoint = MOVE_STOP_MACRO(move);

	Piece startTeam = (board[startPoint] & PIECE_TEAM_MASK);

	unsigned short stopRank = POINT_RANK_MACRO(stopPoint);


	unsigned short pawnRank = 0;

	if(startTeam == PIECE_TEAM_WHITE) pawnRank = (stopRank + BLACK_MOVE_VALUE);

	else if(startTeam == PIECE_TEAM_BLACK) pawnRank = (stopRank + WHITE_MOVE_VALUE);

	else return false;


	unsigned short pawnFile = (INFO_PASSANT_MACRO(*info) - 1);


	Point pawnPoint = RANK_POINT_MACRO(pawnRank) | FILE_POINT_MACRO(pawnFile);


	board[stopPoint] = board[startPoint];
	board[startPoint] = PIECE_NONE;
	board[pawnPoint] = PIECE_NONE;


	*info = ALLOC_INFO_PASSANT(*info, 0);

	return true;
}

// This function is going to execute the double jump by a pawn
// - It has to update the passant point
bool execute_double_move(Piece* board, Info* info, Kings* kings, Move move)
{
	if(!move_inside_board(move)) return false;


	Point startPoint = MOVE_START_MACRO(move);
	Point stopPoint = MOVE_STOP_MACRO(move);


	unsigned short startFile = POINT_FILE_MACRO(startPoint);


	board[stopPoint] = board[startPoint];
	board[startPoint] = PIECE_NONE;


	unsigned short passantFile = (startFile + 1);

	Info infoPassant = PASSANT_INFO_MACRO(passantFile);

	*info = ALLOC_INFO_PASSANT(*info, infoPassant);

	return true;
}
