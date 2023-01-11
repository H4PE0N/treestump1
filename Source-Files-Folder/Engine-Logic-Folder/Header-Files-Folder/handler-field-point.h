
#ifndef HANDLER_FIELD_POINT_H
#define HANDLER_FIELD_POINT_H

bool board_points_team(const Piece board[], Point point1, Point point2);

bool board_points_enemy(const Piece board[], Point point1, Point point2);

int array_point_index(const Point pointArray[], int amount, Point point);

bool delete_array_point(Point* pointArray, int amount, int delIndex);

uint point_array_amount(const Point pointArray[]);

Point* create_point_array(int amount);

Point board_king_point(const Piece board[], uint8_t team);

#endif
