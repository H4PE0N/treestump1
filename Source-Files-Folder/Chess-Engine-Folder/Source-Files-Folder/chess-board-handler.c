
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

bool number_inside_bounds(int number, int minimum, int maximum)
{
	return (number >= minimum && number <= maximum);
}