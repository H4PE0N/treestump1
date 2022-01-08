
#include "../Header-Files-Folder/engine-include-file.h"

bool move_inside_board(Move move)
{
	Point start = MOVE_START_MACRO(move);
	Point stop = MOVE_STOP_MACRO(move);

	bool startInside = point_inside_board(start);
	bool stopInside = point_inside_board(stop);

	return (startInside && stopInside);
}

bool point_inside_board(Point point)
{
	return number_inside_bounds(point, 0, BOARD_LENGTH);
}

bool board_points_team(const Piece board[], Point first, Point second)
{
	Piece firstPiece = board[first];
	Piece secondPiece = board[second];

	return board_pieces_team(firstPiece, secondPiece);
}

bool board_pieces_team(Piece firstPiece, Piece secondPiece)
{
	Piece firstTeam = firstPiece & PIECE_TEAM_MASK;
	Piece secondTeam = secondPiece & PIECE_TEAM_MASK;

	return board_teams_team(firstTeam, secondTeam);
}

bool board_teams_team(Piece firstTeam, Piece secondTeam)
{
	bool bothBlack = (firstTeam == PIECE_TEAM_BLACK && secondTeam == PIECE_TEAM_BLACK);
	bool bothWhite = (firstTeam == PIECE_TEAM_WHITE && secondTeam == PIECE_TEAM_WHITE);

	return (bothBlack || bothWhite);
}

bool board_teams_enemy(Piece firstTeam, Piece secondTeam)
{
	bool bothBlack = (firstTeam == PIECE_TEAM_BLACK && secondTeam == PIECE_TEAM_BLACK);
	bool bothWhite = (firstTeam == PIECE_TEAM_WHITE && secondTeam == PIECE_TEAM_WHITE);

	return (!bothBlack && !bothWhite);
}

// bool board_points_enemy()
// {
// 
// }

bool number_inside_bounds(int number, int minimum, int maximum)
{
	return (number >= minimum && number <= maximum);
}