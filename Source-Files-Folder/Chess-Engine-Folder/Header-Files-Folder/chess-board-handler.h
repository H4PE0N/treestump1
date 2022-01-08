
#ifndef CHESS_BOARD_HANDLER_H
#define CHESS_BOARD_HANDLER_H

bool number_inside_bounds(int, int, int);

bool move_inside_board(Move);

bool point_inside_board(Point);

bool board_points_team(const Piece[], Point, Point);

bool board_pieces_team(Piece, Piece);

bool board_teams_team(Piece, Piece);

bool board_teams_enemy(Piece, Piece);

#endif