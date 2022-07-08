
#include "../Header-Files-Folder/engine-include-file.h"

bool king_inside_check(const Piece board[], Info info, Point kingPoint)
{
	if(!point_inside_board(kingPoint)) return false;

	unsigned short kingTeam = PIECE_TEAM_MACRO(board[kingPoint]);


	for(Point point = 0; point < BOARD_LENGTH; point += 1)
	{
		unsigned short currentTeam = PIECE_TEAM_MACRO(board[point]);

		// If the two pieces are not enemies, they cant make check on each other.
		if(!normal_teams_enemy(currentTeam, kingTeam)) continue;

		if(piece_does_check(board, info, kingPoint, point)) return true;
	}
	return false;
}

bool piece_does_check(const Piece board[], Info info, Point kingPoint, Point point)
{
	if(!point_inside_board(point)) return false;
	if(!point_inside_board(kingPoint)) return false;

	if(!board_points_enemy(board, kingPoint, point)) return false;

	Move move = start_stop_move(point, kingPoint);

	if(!move_pattern_valid(move, board[point])) return false;

	return move_pattern_fits(board, move);

	// if(!correct_move_flag(&move, board[point], info)) return false;
	//
	// return move_pseudo_legal(board, info, move);
}

bool game_still_running(const Piece board[], Info info)
{
	unsigned short currentTeam = INFO_TEAM_MACRO(info);

	if(check_mate_ending(board, info, currentTeam)) return false;

	if(check_draw_ending(board, info, currentTeam)) return false;

	return true;
}

bool check_mate_ending(const Piece board[], Info info, unsigned short team)
{
	if(!normal_team_exists(team)) return false;

	Point kingPoint = board_king_point(board, team);

	if(kingPoint == POINT_NONE) return false;


	if(!king_inside_check(board, info, kingPoint)) return false;

	if(team_pieces_movable(board, info, team)) return false;

	return true;
}

bool check_draw_ending(const Piece board[], Info info, unsigned short team)
{
	if(!normal_team_exists(team)) return false;

	Point kingPoint = board_king_point(board, team);

	if(kingPoint == POINT_NONE) return false;


	if(king_inside_check(board, info, kingPoint)) return false;

	if(team_pieces_movable(board, info, team)) return false;

	return true;
}

bool team_pieces_movable(const Piece board[], Info info, unsigned short team)
{
	if(!normal_team_exists(team)) return false;

	for(Point point = 0; point < BOARD_LENGTH; point += 1)
	{
		unsigned short currentTeam = PIECE_TEAM_MACRO(board[point]);

		if(!normal_teams_team(currentTeam, team)) continue;

		if(chess_piece_movable(board, info, point)) return true;
	}
	return false;
}

bool chess_piece_movable(const Piece board[], Info info, Point piecePoint)
{
	if(!point_inside_board(piecePoint)) return false;

	Piece piece = board[piecePoint];

	Move* moveArray;
	if(!piece_pattern_moves(&moveArray, board, piecePoint)) return false;

	unsigned short moveAmount = move_array_amount(moveArray);

	bool result = piece_movable_test(board, info, piece, moveArray, moveAmount);

	free(moveArray); return result;
}

bool piece_movable_test(const Piece board[], Info info, Piece piece, const Move moveArray[], short moveAmount)
{
	for(unsigned short index = 0; index < moveAmount; index += 1)
	{
		Move move = moveArray[index];

		if(!correct_move_flag(&move, piece, info)) continue;

		if(move_fully_legal(board, info, move)) return true;
	}
	return false;
}

bool move_deliver_check(const Piece board[], Info info, Move move)
{
	if(!move_inside_board(move)) return false;

	Piece* boardCopy = copy_chess_board(board);

	Info infoCopy = info;

	bool result = deliver_check_test(boardCopy, infoCopy, move);

	free(boardCopy); return result;
}

bool deliver_check_test(Piece* boardCopy, Info infoCopy, Move move)
{
	unsigned short enemyTeam = move_start_enemy(move, boardCopy);

	if(!execute_chess_move(boardCopy, &infoCopy, move)) return false;

	Point kingPoint = board_king_point(boardCopy, enemyTeam);

	if(kingPoint == POINT_NONE) return false;

	return king_inside_check(boardCopy, infoCopy, kingPoint);
}

bool move_deliver_mate(const Piece board[], Info info, Move move)
{
	if(!move_inside_board(move)) return false;

	Piece* boardCopy = copy_chess_board(board);

	Info infoCopy = info;

	bool result = deliver_mate_test(boardCopy, infoCopy, move);

	free(boardCopy); return result;
}

bool deliver_mate_test(Piece* boardCopy, Info infoCopy, Move move)
{
	unsigned short enemyTeam = move_start_enemy(move, boardCopy);

	if(!execute_chess_move(boardCopy, &infoCopy, move)) return false;

	Point kingPoint = board_king_point(boardCopy, enemyTeam);

	if(kingPoint == POINT_NONE) return false;

	return check_mate_ending(boardCopy, infoCopy, enemyTeam);
}
