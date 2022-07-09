
#include "../Header-Files-Folder/engine-include-file.h"

// This function should check if the inputted move prevents check.
// It can do that by executing the move, and see if the king is in check
bool move_check_handler(const Piece board[], Info info, Move move)
{
	if(!move_inside_board(move)) return false;

	Piece piece = move_start_piece(move, board);

	if(castle_move_ident(info, move, piece))
		return castle_prevent_check(board, info, move);

	return move_prevent_check(board, info, move);
}

bool castle_prevent_check(const Piece board[], Info info, Move castleMove)
{
	if(!move_inside_board(castleMove)) return false;

	Point kingPoint = MOVE_START_MACRO(castleMove);

	if(king_inside_check(board, info, kingPoint)) return false;

	Move middleMove = castle_middle_move(castleMove);

	if(!move_prevent_check(board, info, middleMove)) return false;

	return move_prevent_check(board, info, castleMove);
}

Move castle_middle_move(Move castleMove)
{
	Point kingPoint = MOVE_START_MACRO(castleMove);
	Point middlePoint = castle_middle_point(castleMove);

	return START_STOP_MOVE(kingPoint, middlePoint);
}

Point castle_middle_point(Move castleMove)
{
	Point kingPoint = MOVE_START_MACRO(castleMove);

	unsigned short kingFile = POINT_FILE_MACRO(kingPoint);
	unsigned short kingRank = POINT_RANK_MACRO(kingPoint);

	signed short fileOffset = normal_file_offset(castleMove);
	signed short fileFactor = move_offset_factor(fileOffset);

	return RANK_FILE_POINT(kingRank, (kingFile + fileFactor));
}

bool move_prevent_check(const Piece board[], Info info, Move move)
{
	if(!move_inside_board(move)) return false;

	Piece* boardCopy = copy_chess_board(board);

	bool result = prevent_check_test(boardCopy, info, move);

	free(boardCopy); return result;
}

bool prevent_check_test(Piece* boardCopy, Info infoCopy, Move move)
{
	unsigned short startTeam = move_start_team(move, boardCopy);

	if(!execute_chess_move(boardCopy, &infoCopy, move)) return false;

	Point kingPoint = board_king_point(boardCopy, startTeam);

	if(kingPoint == POINT_NONE) return false;

	return !king_inside_check(boardCopy, infoCopy, kingPoint);
}
