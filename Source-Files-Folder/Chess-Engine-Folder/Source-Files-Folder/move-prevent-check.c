
#include "../Header-Files-Folder/engine-include-file.h"

// This function should check if the inputted move prevents check.
// It can do that by executing the move, and see if the king is in check
bool move_check_handler(const Piece board[], Info info, Kings kings, Move move)
{
	if(!move_inside_board(move)) return false;

	if(castle_pattern_fits(board, move))
	{
		return castle_prevent_check(board, info, kings, move);
	}
	else return move_prevent_check(board, info, kings, move);
}

bool castle_prevent_check(const Piece board[], Info info, Kings kings, Move castleMove)
{
	if(!move_inside_board(castleMove)) return false;

	Point kingPoint = MOVE_START_MACRO(castleMove);

	if(king_inside_check(board, info, kingPoint)) return false;

	Move middleMove = castle_middle_move(castleMove);

	if(!move_prevent_check(board, info, kings, middleMove)) return false;

	return move_prevent_check(board, info, kings, castleMove);
}

Point castle_middle_move(Move castleMove)
{
	Point kingPoint = MOVE_START_MACRO(castleMove);

	unsigned short kingFile = POINT_FILE_MACRO(kingPoint);
	unsigned short kingRank = POINT_RANK_MACRO(kingPoint);

	signed short fileOffset = normal_file_offset(castleMove);
	signed short fileFactor = move_offset_factor(fileOffset);

	Point middlePoint = rank_file_point(kingRank, kingFile + fileFactor);
	return start_stop_move(kingPoint, middlePoint);
}

bool move_prevent_check(const Piece board[], Info info, Kings kings, Move move)
{
	if(!move_inside_board(move)) return false;

	Piece* boardCopy = malloc(sizeof(Piece) * BOARD_LENGTH);
	memcpy(boardCopy, board, sizeof(Piece) * BOARD_LENGTH);

	Info infoCopy = info; Kings kingsCopy = kings;

	bool result = prevent_check_test(boardCopy, infoCopy, kingsCopy, move);

	free(boardCopy); return result;
}

bool prevent_check_test(Piece* boardCopy, Info infoCopy, Kings kingsCopy, Move move)
{
	Point startPoint = MOVE_START_MACRO(move);

	unsigned short startTeam = PIECE_TEAM_MACRO(boardCopy[startPoint]);

	if(!execute_chess_move(boardCopy, &infoCopy, &kingsCopy, move)) return false;

	Point kingPoint = team_king_point(kingsCopy, startTeam);

	if(kingPoint == POINT_NONE) return false;

	return !king_inside_check(boardCopy, infoCopy, kingPoint);
}
