
#ifndef HANDLER_FIELD_POINT_H
#define HANDLER_FIELD_POINT_H

bool board_points_team(const Piece[], Point, Point);

bool board_points_enemy(const Piece[], Point, Point);

bool board_point_exists(const Piece[], Point);

short array_point_index(const Point[], short, Point);

bool delete_array_point(Point*, short, short);

unsigned short point_array_amount(const Point[]);

Point* create_point_array(short);

Point board_king_point(const Piece[], unsigned short);

#endif
