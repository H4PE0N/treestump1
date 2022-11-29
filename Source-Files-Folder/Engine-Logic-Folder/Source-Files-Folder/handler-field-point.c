
#include "../Header-Files-Folder/englog-include-file.h"

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

short array_point_index(const Point pointArray[], short amount, Point point)
{
	for(unsigned short index = 0; index < amount; index += 1)
		if(pointArray[index] == point) return index;

	return INDEX_NONE;
}

bool delete_array_point(Point* pointArray, short amount, short delIndex)
{
	if(!((delIndex >= 0) && (delIndex < amount))) return false;

	for(int index = delIndex; index < (amount - 1); index += 1)
		pointArray[index] = pointArray[index + 1];

	pointArray[amount - 1] = POINT_NONE; return true;
}

Point* create_point_array(short amount)
{
	Point* pointArray = malloc(sizeof(Point) * (amount + 1));
	memset(pointArray, POINT_NONE, sizeof(Point) * (amount + 1));

	return pointArray;
}

unsigned short point_array_amount(const Point pointArray[])
{
	unsigned short amount = 0;

	while(pointArray[amount] != POINT_NONE) amount += 1;

	return amount;
}
