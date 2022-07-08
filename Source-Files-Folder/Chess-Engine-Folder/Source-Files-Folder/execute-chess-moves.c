
#include "../Header-Files-Folder/engine-include-file.h"

// This function is going to just move the pieces around,
// based on what action (flag) the move has
// This function is not going to check any validation
bool execute_chess_move(Piece* board, Info* info, Move move)
{
	if(!move_inside_board(move)) return false;

	Move moveFlag = (move & MOVE_FLAG_MASK);

	if(moveFlag == MOVE_FLAG_KNIGHT || moveFlag == MOVE_FLAG_BISHOP || moveFlag == MOVE_FLAG_ROOK || moveFlag == MOVE_FLAG_QUEEN)
	{
		return execute_promote_move(board, info, move);
	}
	else if(moveFlag == MOVE_FLAG_CASTLE)
	{
		return execute_castle_move(board, info, move);
	}
	else if(moveFlag == MOVE_FLAG_PASSANT)
	{
		return execute_passant_move(board, info, move);
	}
	else if(moveFlag == MOVE_FLAG_DOUBLE)
	{
		return execute_double_move(board, info, move);
	}
	else return execute_normal_move(board, info, move);
}

// This function is going to execute all normal moves
// - It just moves the piece to a specific point
bool execute_normal_move(Piece* board, Info* info, Move move)
{
	if(!move_inside_board(move)) return false;

	Point startPoint = MOVE_START_MACRO(move);
	Point stopPoint = MOVE_STOP_MACRO(move);


	unsigned short startFile = POINT_FILE_MACRO(startPoint);
	unsigned short startRank = POINT_RANK_MACRO(startPoint);

	unsigned short stopFile = POINT_FILE_MACRO(stopPoint);
	unsigned short stopRank = POINT_RANK_MACRO(stopPoint);


	Piece startPieceType = (board[startPoint] & PIECE_TYPE_MASK);
	Piece stopPieceType = (board[stopPoint] & PIECE_TYPE_MASK);

	Piece startPiece = board[startPoint];

	unsigned short startTeam = PIECE_TEAM_MACRO(startPiece);

	board[startPoint] = PIECE_NONE;
	board[stopPoint] = startPiece;

	if(startPieceType == PIECE_TYPE_KING)
	{
		if(startTeam == TEAM_WHITE)
		{
			// Resets the bits of white king and queen
			*info = (*info & ~INFO_WHITE_KING & ~INFO_WHITE_QUEEN);
		}
		else if(startTeam == TEAM_BLACK)
		{
			// Resets the bits of black king and queen
			*info = (*info & ~INFO_BLACK_KING & ~INFO_BLACK_QUEEN);
		}
	}

	// If a rook is moving, or a rook is taken: The castle ability must be set to false
	if(startPieceType == PIECE_TYPE_ROOK || stopPieceType == PIECE_TYPE_ROOK)
	{
		unsigned short rookRank = (startPieceType == PIECE_TYPE_ROOK) ? startRank : stopRank;
		unsigned short rookFile = (startPieceType == PIECE_TYPE_ROOK) ? startFile : stopFile;

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


	unsigned short turns = INFO_TURNS_MACRO(*info);
	unsigned short team = INFO_TEAM_MACRO(*info);

	if(team == TEAM_BLACK) *info = ALLOC_INFO_TURNS(*info, TURNS_INFO_MACRO((turns + 1)) );


	if(team == TEAM_WHITE) *info = ALLOC_INFO_TEAM(*info, INFO_TEAM_BLACK);
	if(team == TEAM_BLACK) *info = ALLOC_INFO_TEAM(*info, INFO_TEAM_WHITE);

	return true;
}

// This function is going to execute a castle
// - It has to move both the king and the rook
bool execute_castle_move(Piece* board, Info* info, Move move)
{
	Point kingPoint = MOVE_START_MACRO(move);

	Piece kingPiece = board[kingPoint];

	unsigned short kingTeam = PIECE_TEAM_MACRO(kingPiece);

	Point rookPoint = castle_rook_point(move, kingTeam);

	if(rookPoint == POINT_NONE) return false;


	Piece rookPiece = board[rookPoint];


	signed short fileOffset = move_file_offset(move, kingTeam);

	Point newKingPoint = MOVE_STOP_MACRO(move);
	Point newRookPoint = (fileOffset == KING_CASTLE_PAT) ? (newKingPoint - 1) : (newKingPoint + 1);

	board[newKingPoint] = kingPiece;
	board[kingPoint] = PIECE_NONE;

	board[newRookPoint] = rookPiece;
	board[rookPoint] = PIECE_NONE;


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

	unsigned short turns = INFO_TURNS_MACRO(*info);
	unsigned short team = INFO_TEAM_MACRO(*info);

	if(team == TEAM_BLACK) *info = ALLOC_INFO_TURNS(*info, TURNS_INFO_MACRO((turns + 1)) );


	if(team == TEAM_WHITE) *info = ALLOC_INFO_TEAM(*info, INFO_TEAM_BLACK);
	if(team == TEAM_BLACK) *info = ALLOC_INFO_TEAM(*info, INFO_TEAM_WHITE);

	return true;
}

Piece promote_piece_type(Move move)
{
	Move moveFlag = MASK_MOVE_FLAG(move);

	if(moveFlag == MOVE_FLAG_ROOK) return PIECE_TYPE_ROOK;

	else if(moveFlag == MOVE_FLAG_BISHOP) return PIECE_TYPE_BISHOP;

	else if(moveFlag == MOVE_FLAG_KNIGHT) return PIECE_TYPE_KNIGHT;

	else if(moveFlag == MOVE_FLAG_QUEEN) return PIECE_TYPE_QUEEN;

	else return PIECE_TYPE_NONE;
}

Piece move_promote_piece(Move move, unsigned short team)
{
	if(!normal_team_exists(team)) return PIECE_NONE;

	Piece pieceType = promote_piece_type(move);

	if(pieceType == PIECE_TYPE_NONE) return PIECE_NONE;

	return (TEAM_PIECE_MACRO(team) | pieceType);
}

// This function is going to execute a promotion
// - It has to get the promotion (KNIGHT, BISHOP, ROOK, QUEEN)
// and swap the piece at the STOP point in the move
bool execute_promote_move(Piece* board, Info* info, Move move)
{
	if(!move_inside_board(move)) return false;


	Point startPoint = MOVE_START_MACRO(move);
	Point stopPoint = MOVE_STOP_MACRO(move);


	unsigned short startTeam = move_start_team(move, board);


	Piece promotePiece = move_promote_piece(move, startTeam);
	if(promotePiece == PIECE_NONE) return false;


	board[stopPoint] = promotePiece;
	board[startPoint] = PIECE_NONE;


	*info = ALLOC_INFO_PASSANT(*info, 0);

	unsigned short turns = INFO_TURNS_MACRO(*info);
	unsigned short team = INFO_TEAM_MACRO(*info);

	if(team == TEAM_BLACK) *info = ALLOC_INFO_TURNS(*info, TURNS_INFO_MACRO((turns + 1)) );


	if(team == TEAM_WHITE) *info = ALLOC_INFO_TEAM(*info, INFO_TEAM_BLACK);
	if(team == TEAM_BLACK) *info = ALLOC_INFO_TEAM(*info, INFO_TEAM_WHITE);

	return true;
}

// This function is going to execute en passant take
// - It has to update the passant point to POINT_NONE
bool execute_passant_move(Piece* board, Info* info, Move move)
{
	if(!move_inside_board(move)) return false;


	Point startPoint = MOVE_START_MACRO(move);
	Point stopPoint = MOVE_STOP_MACRO(move);

	Piece startPieceTeam = (board[startPoint] & PIECE_TEAM_MASK);

	unsigned short stopRank = POINT_RANK_MACRO(stopPoint);


	unsigned short pawnRank = 0;

	if(startPieceTeam == PIECE_TEAM_WHITE) pawnRank = (stopRank + BLACK_MOVE_VALUE);

	else if(startPieceTeam == PIECE_TEAM_BLACK) pawnRank = (stopRank + WHITE_MOVE_VALUE);

	else return false;


	unsigned short pawnFile = (INFO_PASSANT_MACRO(*info) - 1);


	Point pawnPoint = RANK_POINT_MACRO(pawnRank) | FILE_POINT_MACRO(pawnFile);


	board[stopPoint] = board[startPoint];
	board[startPoint] = PIECE_NONE;
	board[pawnPoint] = PIECE_NONE;


	*info = ALLOC_INFO_PASSANT(*info, 0);

	unsigned short turns = INFO_TURNS_MACRO(*info);
	unsigned short team = INFO_TEAM_MACRO(*info);

	if(team == TEAM_BLACK) *info = ALLOC_INFO_TURNS(*info, TURNS_INFO_MACRO((turns + 1)) );


	if(team == TEAM_WHITE) *info = ALLOC_INFO_TEAM(*info, INFO_TEAM_BLACK);
	if(team == TEAM_BLACK) *info = ALLOC_INFO_TEAM(*info, INFO_TEAM_WHITE);

	return true;
}

// This function is going to execute the double jump by a pawn
// - It has to update the passant point
bool execute_double_move(Piece* board, Info* info, Move move)
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

	unsigned short turns = INFO_TURNS_MACRO(*info);
	unsigned short team = INFO_TEAM_MACRO(*info);

	if(team == TEAM_BLACK) *info = ALLOC_INFO_TURNS(*info, TURNS_INFO_MACRO((turns + 1)) );


	if(team == TEAM_WHITE) *info = ALLOC_INFO_TEAM(*info, INFO_TEAM_BLACK);
	if(team == TEAM_BLACK) *info = ALLOC_INFO_TEAM(*info, INFO_TEAM_WHITE);

	return true;
}
