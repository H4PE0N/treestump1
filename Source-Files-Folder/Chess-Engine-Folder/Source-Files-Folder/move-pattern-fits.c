
#include "../Header-Files-Folder/engine-include-file.h"

// This function is going to check if the move-pattern
// fits inside the board (pawn-takes, castling, pawn double jump)
// - the stop piece can't be of same team
// - the stop piece must be empty if the pawn moves forward
// - it must be a rook in the corner, if it is castle
// - the move path is clear (except for the knight)
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

	if(!clear_moving_path(board, move)) return false;

	return true;
}

bool passant_pattern_fits(const Piece board[], Move move)
{
	if(!move_inside_board(move)) return false;

	Point startPoint = MOVE_START_MACRO(move);
	Point stopPoint = MOVE_STOP_MACRO(move);

	Piece startType = (board[startPoint] & PIECE_TYPE_MASK);


	if(startType != PIECE_TYPE_PAWN) return false;

	if(chess_piece_exists(board[stopPoint])) return false;

	// ememy pawn must be at its place

	if(!clear_moving_path(board, move)) return false;

	return true;
}

bool castle_pattern_fits(const Piece board[], Move move)
{
	if(!move_inside_board(move)) return false;

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

	if(!clear_moving_path(board, move)) return false;

	return true;
}

Point castle_rook_point(Move move, unsigned short team)
{
	if(!move_inside_board(move)) return false;

	if(!normal_team_exists(team)) return false;

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

bool pawn_pattern_fits(const Piece board[], Move move)
{
	if(!move_inside_board(move)) return false;

	Point startPoint = MOVE_START_MACRO(move);
	Point stopPoint = MOVE_STOP_MACRO(move);


	Piece startPieceType = (board[startPoint] & PIECE_TYPE_MASK);

	if(startPieceType != PIECE_TYPE_PAWN) return false;


	unsigned short startTeam = PIECE_TEAM_MACRO(board[startPoint]);
	unsigned short stopTeam = PIECE_TEAM_MACRO(board[stopPoint]);

	unsigned short fileOffset = ABS_SHORT_NUMBER(move_file_offset(move, startTeam));
	signed short rankOffset = move_rank_offset(move, startTeam);


	if(fileOffset == 0 && (rankOffset == 1 || rankOffset == 2))
	{
		if(chess_piece_exists(board[stopPoint])) return false;
	}

	else if(fileOffset == 1 && rankOffset == 1)
	{
		if(!normal_teams_enemy(startTeam, stopTeam)) return false;
	}

	if(!clear_moving_path(board, move)) return false;

	return true;
}

bool clear_moving_path(const Piece board[], Move move)
{
	if(!move_inside_board(move)) return false;

	Point startPoint = MOVE_START_MACRO(move);
	if((board[startPoint] & PIECE_TYPE_MASK) == PIECE_TYPE_KNIGHT) return true;

	Point* movePoints;
	if(!moving_path_points(&movePoints, move)) return false;

	unsigned short amount = point_array_amount(movePoints);

	bool result = testing_clear_path(board, movePoints, amount, move);

	free(movePoints); return result;
}

bool testing_clear_path(const Piece board[], const Point movePoints[], unsigned short amount, Move move)
{
	Point startPoint = MOVE_START_MACRO(move);
	Point stopPoint = MOVE_STOP_MACRO(move);

	for(short index = 0; index < amount; index += 1)
	{
		Point currentPoint = movePoints[index];

		if(currentPoint == startPoint || currentPoint == stopPoint) continue;

		if(board_point_exists(board, currentPoint)) return false;
	}
	return true;
}

bool moving_path_points(Point** movePoints, Move move)
{
	if(!move_inside_board(move)) return false;

	signed short rankFactor, fileFactor;
	unsigned short moveSteps;

	if(!moving_path_values(&rankFactor, &fileFactor, &moveSteps, move)) return false;

	unsigned short startFile = POINT_FILE_MACRO(MOVE_START_MACRO(move));
	unsigned short startRank = POINT_RANK_MACRO(MOVE_START_MACRO(move));

	*movePoints = create_point_array(32);

	for(unsigned short index = 0; index <= moveSteps; index += 1)
	{
		unsigned short currentFile = startFile + (index * fileFactor);
		unsigned short currentRank = startRank + (index * rankFactor);

		(*movePoints)[index] = rank_file_point(currentRank, currentFile);
	}
	return true;
}

bool moving_path_values(signed short* rankFactor, signed short* fileFactor, unsigned short* moveSteps, Move move)
{
	// if(!move_inside_board(move)) return false;

	signed short rankOffset = normal_rank_offset(move);
	signed short fileOffset = normal_file_offset(move);

	unsigned short absRankOffset = ABS_SHORT_NUMBER(rankOffset);
	unsigned short absFileOffset = ABS_SHORT_NUMBER(fileOffset);

	bool moveStraight = (absRankOffset == 0 || absFileOffset == 0);
	bool moveDiagonal = (absRankOffset == absFileOffset);

	if(!moveStraight && !moveDiagonal) return false;

	*fileFactor = move_offset_factor(fileOffset);
	*rankFactor = move_offset_factor(rankOffset);
	*moveSteps = (absRankOffset > absFileOffset) ? absRankOffset : absFileOffset;

	return true;
}
