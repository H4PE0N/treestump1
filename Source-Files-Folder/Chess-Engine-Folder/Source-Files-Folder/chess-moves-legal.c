
#include "../Header-Files-Folder/engine-include-file.h"

// This function should check:
// - the move is pseudo legal
// - the own king is not set in check
bool move_fully_legal(const Piece board[], Info info, Kings kings, Move move)
{
	if(!move_inside_board(move)) return false;

	if(!move_pseudo_legal(board, info, move)) return false;

	if(!move_prevent_check(board, info, kings, move)) return false;

	return true;
}

// This function should check:
// - the piece is allowed to move that way
// - the move path is clear (except for the knight)
bool move_pseudo_legal(const Piece board[], Info info, Move move)
{
	if(!move_inside_board(move)) return false;

	Piece startPiece = board[MOVE_START_MACRO(move)];

	if(!move_pattern_valid(move, startPiece)) return false;

	if(!move_ability_valid(move, startPiece, info)) return false;

	if(!move_pattern_fits(board, move)) return false;

	if(!clear_moving_path(board, move)) return false;

	return true;
}

// This function creates memory for an array of legal moves
// The memory has to be freed after use!! OBS!
// This function is trash, make it more specific for the pieces:
bool piece_legal_moves(Move** moveArray, const Piece board[], Info info, Kings kings, Point piecePoint)
{
	if(!point_inside_board(piecePoint)) return false;


	*moveArray = create_move_array(32);
	// 32: Because the QUEEN is the one that can move the most,
	// and she can move to 28 squares (7 horizontal, 7 vertical, 7 right diagonal, 7 left diagonal)

	Piece startPiece = board[piecePoint];

	unsigned short moveAmount = 0;


	for(Point stopPoint = 0; stopPoint < BOARD_LENGTH; stopPoint += 1)
	{
		Move currentMove = (START_MOVE_MACRO(piecePoint) | STOP_MOVE_MACRO(stopPoint));

		if(!correct_move_flag(&currentMove, startPiece, info)) continue;

		if(!move_fully_legal(board, info, kings, currentMove)) continue;

		(*moveArray)[moveAmount++] = currentMove;
	}

	return true;
}

bool team_legal_moves(Move** moveArray, const Piece board[], Info info, Kings kings, unsigned short team)
{
	if(!normal_team_exists(team)) return false;


	*moveArray = create_move_array(376);
	// If all pawns has been promoted to queens (+8 QUEENS), and every other piece remains.
	// The total amount of moves possible for all pieces combined, will add up to 376 with a large margin.

	unsigned short moveAmount = 0;


	for(Point point = 0; point < BOARD_LENGTH; point += 1)
	{
		unsigned short currentTeam = PIECE_TEAM_MACRO(board[point]);

		if(currentTeam != team) continue;


		Move* addingMoves;

		if(!piece_legal_moves(&addingMoves, board, info, kings, point)) continue;


		unsigned short addingAmount = move_array_amount(addingMoves);


		for(unsigned short index = 0; index < addingAmount; index += 1)
		{
			(*moveArray)[moveAmount++] = addingMoves[index];
		}

		free(addingMoves);
	}

	return true;
}

// This function should check if the inputted move prevents check.
// It can do that by executing the move, and see if the king is in check
bool move_prevent_check(const Piece board[], Info info, Kings kings, Move move)
{
	if(!move_inside_board(move)) return false;


	Point startPoint = MOVE_START_MACRO(move);
	unsigned short startTeam = PIECE_TEAM_MACRO(board[startPoint]);


	Piece* boardCopy = malloc(sizeof(Piece) * BOARD_LENGTH);
	memcpy(boardCopy, board, sizeof(Piece) * BOARD_LENGTH);

	Info infoCopy = info;
	Kings kingsCopy = kings;

	if(!execute_chess_move(boardCopy, &infoCopy, &kingsCopy, move))
	{
		free(boardCopy);

		return false;
	}


	Point kingPoint = POINT_NONE;

	if(startTeam == TEAM_WHITE) kingPoint = KINGS_WHITE_MACRO(kingsCopy);

	else if(startTeam == TEAM_BLACK) kingPoint = KINGS_BLACK_MACRO(kingsCopy);


	if(king_inside_check(boardCopy, infoCopy, kingPoint))
	{
		free(boardCopy);

		return false;
	}

	free(boardCopy);

	// If it is a king that is castling, you have to check
	// that the king does not pass through check (the point
	// where the rook later lands, should not be in check)

	return true;
}

bool clear_moving_path(const Piece board[], Move move)
{
	if(!move_inside_board(move)) return false;

	Point startPoint = MOVE_START_MACRO(move);
	Point stopPoint = MOVE_STOP_MACRO(move);

	Piece piece = board[startPoint];
	Piece pieceType = PIECE_TYPE_MACRO(piece);

	if(pieceType == PIECE_TYPE_KNIGHT) return true;


	unsigned short startRank = POINT_RANK_MACRO(startPoint);
	unsigned short startFile = POINT_FILE_MACRO(startPoint);

	unsigned short stopFile = POINT_FILE_MACRO(stopPoint);
	unsigned short stopRank = POINT_RANK_MACRO(stopPoint);

	signed short rankOffset = (stopRank - startRank);
	signed short fileOffset = (stopFile - startFile);

	unsigned short absRankOffset = ABS_SHORT_NUMBER(rankOffset);
	unsigned short absFileOffset = ABS_SHORT_NUMBER(fileOffset);

	// If both rank- and file-offset is 0, then its not moving
	if(absRankOffset == 0 && absFileOffset == 0) return false;

	// Either it can go straight (one is 0), or it can go diagonal (both the same)

	if( (absRankOffset != 0 && absFileOffset != 0) && absRankOffset != absFileOffset) return false;

	unsigned short moveSteps = (absRankOffset > absFileOffset) ? absRankOffset : absFileOffset;


	signed short rankFactor = (absRankOffset == 0) ? 0 : (rankOffset / absRankOffset);
	signed short fileFactor = (absFileOffset == 0) ? 0 : (fileOffset / absFileOffset);


	for(unsigned short index = 1; index < moveSteps; index = index + 1)
	{
		unsigned short currentFile = startFile + (index * fileFactor);
		unsigned short currentRank = startRank + (index * rankFactor);

		Point point = (currentFile << POINT_FILE_SHIFT) | (currentRank << POINT_RANK_SHIFT);

		Piece currentPieceTeam = (board[point] & PIECE_TEAM_MASK);
		Piece currentPieceType = (board[point] & PIECE_TYPE_MASK);

		if(currentPieceType != PIECE_TYPE_NONE || currentPieceTeam != PIECE_TEAM_NONE) return false;
	}

	return true;
}

bool move_ability_valid(Move move, Piece piece, Info info)
{
	if(!move_inside_board(move)) return false;

	unsigned short team = PIECE_TEAM_MACRO(piece);

	Move moveFlag = move & MOVE_FLAG_MASK;


	if(moveFlag == MOVE_FLAG_CASTLE)
	{
		return castle_ability_valid(move, info, team);
	}

	else if(moveFlag == MOVE_FLAG_PASSANT)
	{
		return passant_ability_valid(move, info);
	}

	return true;
}

bool castle_ability_valid(Move move, Info info, unsigned short team)
{
	signed short movePattern = board_move_pattern(move);

	Info infoCastles = (info & INFO_CASTLES_MASK);


	if(team == TEAM_WHITE && movePattern == KING_CASTLE_PAT)
	{
		if(!(infoCastles & INFO_WHITE_KING)) return false;
	}
	else if(team == TEAM_WHITE && movePattern == QUEEN_CASTLE_PAT)
	{
		if(!(infoCastles & INFO_WHITE_QUEEN)) return false;
	}
	else if(team == TEAM_BLACK && movePattern == KING_CASTLE_PAT)
	{
		if(!(infoCastles & INFO_BLACK_KING)) return false;
	}
	else if(team == TEAM_BLACK && movePattern == QUEEN_CASTLE_PAT)
	{
		if(!(infoCastles & INFO_BLACK_QUEEN)) return false;
	}
	else return false;

	return true;
}

bool passant_ability_valid(Move move, Info info)
{
	unsigned short stopFile = POINT_FILE_MACRO(MOVE_STOP_MACRO(move));

	unsigned short passantFile = INFO_PASSANT_MACRO(info);

	return ( (stopFile + 1) == passantFile);
}

bool current_team_move(Info info, unsigned short team)
{
	unsigned short infoTeamValue = INFO_TEAM_MACRO(info);

	return normal_teams_team(infoTeamValue, team);
}

// This function is going to check if the move-pattern
// fits inside the board (pawn-takes, castling, pawn double jump)
// - the stop piece can't be of same team
// - the stop piece must be empty if the pawn moves forward
// - it must be a rook in the corner, if it is castle
bool move_pattern_fits(const Piece board[], Move move)
{
	if(!move_inside_board(move)) return false;

	Point startPoint = MOVE_START_MACRO(move);
	Point stopPoint = MOVE_STOP_MACRO(move);

	Piece startType = (board[startPoint] & PIECE_TYPE_MASK);


	if(board_points_team(board, startPoint, stopPoint)) return false;


	Move moveFlag = (move & MOVE_FLAG_MASK);

	if(moveFlag == MOVE_FLAG_CASTLE)
	{
		return castle_pattern_fits(board, move);
	}
	else if(startType == PIECE_TYPE_PAWN && moveFlag == MOVE_FLAG_PASSANT)
	{
		return passant_pattern_fits(board, move);
	}
	else if(startType == PIECE_TYPE_PAWN)
	{
		return pawn_pattern_fits(board, move);
	}

	return true;
}

bool passant_pattern_fits(const Piece board[], Move move)
{
	Point startPoint = MOVE_START_MACRO(move);
	Point stopPoint = MOVE_STOP_MACRO(move);

	Piece startType = (board[startPoint] & PIECE_TYPE_MASK);


	if(startType != PIECE_TYPE_PAWN) return false;

	if(chess_piece_exists(board[stopPoint])) return false;

	// ememy pawn must be at its place

	return true;
}

bool castle_pattern_fits(const Piece board[], Move move)
{
	Point startPoint = MOVE_START_MACRO(move);

	Piece startPieceType = (board[startPoint] & PIECE_TYPE_MASK);
	Piece startPieceTeam = (board[startPoint] & PIECE_TEAM_MASK);

	unsigned short startTeam = PIECE_TEAM_MACRO(board[startPoint]);


	if(startPieceType != PIECE_TYPE_KING) return false;


	Point rookPoint = castle_rook_point(move, startTeam);

	if(rookPoint == POINT_NONE) return false;


	Piece rookPieceType = (board[rookPoint] & PIECE_TYPE_MASK);
	Piece rookPieceTeam = (board[rookPoint] & PIECE_TEAM_MASK);

	if(rookPieceType != PIECE_TYPE_ROOK || rookPieceTeam != startPieceTeam) return false;

	return true;
}

bool pawn_pattern_fits(const Piece board[], Move move)
{
	Point startPoint = MOVE_START_MACRO(move);
	Point stopPoint = MOVE_STOP_MACRO(move);

	Piece startPieceType = (board[startPoint] & PIECE_TYPE_MASK);

	unsigned short startTeam = PIECE_TEAM_MACRO(board[startPoint]);
	unsigned short stopTeam = PIECE_TEAM_MACRO(board[stopPoint]);

	unsigned short fileOffset = ABS_SHORT_NUMBER(move_file_offset(move, startTeam));
	signed short rankOffset = move_rank_offset(move, startTeam);


	if(startPieceType != PIECE_TYPE_PAWN) return false;


	if(fileOffset == 0 && (rankOffset == 1 || rankOffset == 2))
	{
		if(chess_piece_exists(board[stopPoint])) return false;
	}

	else if(fileOffset == 1 && rankOffset == 1)
	{
		if(!normal_teams_enemy(startTeam, stopTeam)) return false;
	}

	return true;
}

Point castle_rook_point(Move move, unsigned short team)
{
	Point kingPoint = MOVE_START_MACRO(move);
	unsigned short kingRank = POINT_RANK_MACRO(kingPoint);

	signed short fileOffset = move_file_offset(move, team);

	Point rookPoint = POINT_NONE;

	if(kingRank == WHITE_START_RANK && fileOffset == KING_CASTLE_PAT)
	{
		rookPoint = FILE_POINT_MACRO((BOARD_FILES - 1)) | RANK_POINT_MACRO(WHITE_START_RANK);
	}
	else if(kingRank == WHITE_START_RANK && fileOffset == QUEEN_CASTLE_PAT)
	{
		rookPoint = FILE_POINT_MACRO(0) | RANK_POINT_MACRO(WHITE_START_RANK);
	}
	else if(kingRank == BLACK_START_RANK && fileOffset == KING_CASTLE_PAT)
	{
		rookPoint = FILE_POINT_MACRO((BOARD_FILES - 1)) | RANK_POINT_MACRO(BLACK_START_RANK);
	}
	else if(kingRank == BLACK_START_RANK && fileOffset == QUEEN_CASTLE_PAT)
	{
		rookPoint = FILE_POINT_MACRO(0) | RANK_POINT_MACRO(BLACK_START_RANK);
	}
	return rookPoint;
}
