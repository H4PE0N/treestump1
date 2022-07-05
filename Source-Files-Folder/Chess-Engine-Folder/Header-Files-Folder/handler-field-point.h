
#ifndef HANDLER_FIELD_POINT_H
#define HANDLER_FIELD_POINT_H

bool point_inside_board(Point);

bool board_points_team(const Piece[], Point, Point);

bool board_points_enemy(const Piece[], Point, Point);

bool board_point_exists(const Piece[], Point);

signed short array_point_index(const Point[], unsigned short, Point);

bool delete_array_point(Point*, unsigned short, short);

unsigned short point_array_amount(const Point[]);

Point* create_point_array(unsigned short);

Point rank_file_point(unsigned short, unsigned short);

Point board_piece_point(const Piece[], Piece);

#endif
