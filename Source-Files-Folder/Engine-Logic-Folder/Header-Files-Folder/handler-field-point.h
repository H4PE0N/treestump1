
#ifndef HANDLER_FIELD_POINT_H
#define HANDLER_FIELD_POINT_H

bool board_points_team(const Piece board[], Point point1, Point point2);

bool board_points_enemy(const Piece board[], Point point1, Point point2);

bool board_point_exists(const Piece board[], Point point);

short array_point_index(const Point pointArray[], short amount, Point point);

bool delete_array_point(Point* pointArray, short amount, short delIndex);

unsigned short point_array_amount(const Point pointArray[]);

Point* create_point_array(short amount);

Point board_king_point(const Piece board[], unsigned short team);

#endif
