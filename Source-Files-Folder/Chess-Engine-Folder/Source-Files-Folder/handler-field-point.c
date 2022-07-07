
#include "../Header-Files-Folder/engine-include-file.h"

Point board_king_point(const Piece board[], unsigned short team)
{
	Piece kingPiece = (PIECE_TYPE_KING | TEAM_PIECE_MACRO(team));

	for(unsigned short index = 0; index < BOARD_LENGTH; index += 1)
	{
		Point point = (team == TEAM_WHITE) ? (BOARD_LENGTH - index - 1) : index;
		if(board[point] == kingPiece) return point;
	}
	return POINT_NONE;
}

Point rank_file_point(unsigned short rank, unsigned short file)
{
	return (RANK_POINT_MACRO(rank) | FILE_POINT_MACRO(file));
}

bool point_inside_board(Point point)
{
	return NUMBER_IN_BOUNDS(point, 0, BOARD_LENGTH - 1);
}

bool board_points_team(const Piece board[], Point firstPoint, Point secondPoint)
{
	Piece firstPiece = board[firstPoint];
	Piece secondPiece = board[secondPoint];

	return chess_pieces_team(firstPiece, secondPiece);
}

bool board_points_enemy(const Piece board[], Point firstPoint, Point secondPoint)
{
	Piece firstPiece = board[firstPoint];
	Piece secondPiece = board[secondPoint];

	return chess_pieces_enemy(firstPiece, secondPiece);
}

bool board_point_exists(const Piece board[], Point point)
{
	Piece piece = board[point];

	return chess_piece_exists(piece);
}

short array_point_index(const Point pointArray[], short amount, Point point)
{
	short pointIndex = -1;

	for(unsigned short index = 0; index < amount; index += 1)
	{
		if(pointArray[index] == point) { pointIndex = index; break; }
	}
	return pointIndex;
}

bool delete_array_point(Point* pointArray, short amount, short delIndex)
{
	if(!(delIndex >= 0 && delIndex < amount)) return false;

	for(int index = delIndex; index < (amount - 1); index += 1)
	{
		pointArray[index] = pointArray[index + 1];
	}
	pointArray[amount - 1] = POINT_NONE; return true;
}

Point* create_point_array(short amount)
{
	Point* pointArray = malloc(sizeof(Point) * (amount + 1));

	for(short index = 0; index < (amount + 1); index += 1)
	{
		pointArray[index] = POINT_NONE;
	}
	return pointArray;
}

unsigned short point_array_amount(const Point pointArray[])
{
	unsigned short amount = 0;

	while(pointArray[amount] != POINT_NONE) amount += 1;

	return amount;
}
