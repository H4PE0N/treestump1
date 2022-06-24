
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

	// If the two pieces are not enemies, they cant make check on each other.
	if(!board_points_enemy(board, kingPoint, point)) return false;


	Move move = (START_MOVE_MACRO(point) | STOP_MOVE_MACRO(kingPoint));


	if(!correct_move_flag(&move, board[point], info)) return false;

	if(!move_pseudo_legal(board, info, move)) return false;

	return true;
}

bool game_still_running(const Piece board[], Info info, Kings kings)
{
	unsigned short currentTeam = INFO_TEAM_MACRO(info);

	if(check_mate_ending(board, info, kings, currentTeam)) return false;

	if(check_draw_ending(board, info, kings, currentTeam)) return false;

	return true;
}

bool check_mate_ending(const Piece board[], Info info, Kings kings, unsigned short team)
{
	if(!normal_team_exists(team)) return false;

	Point kingPoint = team_king_point(kings, team);

	if(kingPoint == POINT_NONE) return false;


	if(!king_inside_check(board, info, kingPoint)) return false;

	if(team_pieces_movable(board, info, kings, team)) return false;

	return true;
}

bool check_draw_ending(const Piece board[], Info info, Kings kings, unsigned short team)
{
	if(!normal_team_exists(team)) return false;

	Point kingPoint = team_king_point(kings, team);

	if(kingPoint == POINT_NONE) return false;


	if(king_inside_check(board, info, kingPoint)) return false;

	if(team_pieces_movable(board, info, kings, team)) return false;

	return true;
}

bool team_pieces_movable(const Piece board[], Info info, Kings kings, unsigned short team)
{
	if(!normal_team_exists(team)) return false;

	for(Point point = 0; point < BOARD_LENGTH; point += 1)
	{
		unsigned short currentTeam = PIECE_TEAM_MACRO(board[point]);

		if(!normal_teams_team(currentTeam, team)) continue;

		if(chess_piece_movable(board, info, kings, point)) return true;
	}
	return false;
}

// This function can be optimized
bool chess_piece_movable(const Piece board[], Info info, Kings kings, Point piecePoint)
{
	if(!point_inside_board(piecePoint)) return false;

	Piece piece = board[piecePoint];

	for(Point point = 0; point < BOARD_LENGTH; point += 1)
	{
		Move move = (START_MOVE_MACRO(piecePoint) | STOP_MOVE_MACRO(point));

		if(!correct_move_flag(&move, piece, info)) continue;

		if(move_fully_legal(board, info, kings, move)) return true;
	}
	return false;
}

bool move_deliver_check(const Piece board[], Info info, Kings kings, Move move)
{
	if(!move_inside_board(move)) return false;

	Piece* boardCopy = malloc(sizeof(Piece) * BOARD_LENGTH);
	memcpy(boardCopy, board, sizeof(Piece) * BOARD_LENGTH);

	Info infoCopy = info; Kings kingsCopy = kings;

	bool result = deliver_check_test(boardCopy, infoCopy, kingsCopy, move);

	free(boardCopy); return result;
}

bool deliver_check_test(Piece* boardCopy, Info infoCopy, Kings kingsCopy, Move move)
{
	Point startPoint = MOVE_START_MACRO(move);

	unsigned short startTeam = PIECE_TEAM_MACRO(boardCopy[startPoint]);
	unsigned short enemyTeam = normal_team_enemy(startTeam);

	if(!execute_chess_move(boardCopy, &infoCopy, &kingsCopy, move)) return false;

	Point kingPoint = team_king_point(kingsCopy, enemyTeam);

	if(kingPoint == POINT_NONE) return false;

	return king_inside_check(boardCopy, infoCopy, kingPoint);
}

bool move_deliver_mate(const Piece board[], Info info, Kings kings, Move move)
{
	if(!move_inside_board(move)) return false;

	Piece* boardCopy = malloc(sizeof(Piece) * BOARD_LENGTH);
	memcpy(boardCopy, board, sizeof(Piece) * BOARD_LENGTH);

	Info infoCopy = info; Kings kingsCopy = kings;

	bool result = deliver_mate_test(boardCopy, infoCopy, kingsCopy, move);

	free(boardCopy); return result;
}

bool deliver_mate_test(Piece* boardCopy, Info infoCopy, Kings kingsCopy, Move move)
{
	Point startPoint = MOVE_START_MACRO(move);

	unsigned short startTeam = PIECE_TEAM_MACRO(boardCopy[startPoint]);
	unsigned short enemyTeam = normal_team_enemy(startTeam);

	if(!execute_chess_move(boardCopy, &infoCopy, &kingsCopy, move)) return false;

	Point kingPoint = team_king_point(kingsCopy, enemyTeam);

	if(kingPoint == POINT_NONE) return false;

	return check_mate_ending(boardCopy, infoCopy, kingsCopy, enemyTeam);
}
