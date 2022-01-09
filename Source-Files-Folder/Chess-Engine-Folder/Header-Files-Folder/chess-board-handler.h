
#ifndef CHESS_BOARD_HANDLER_H
#define CHESS_BOARD_HANDLER_H

bool short_inside_bounds(short, short, short);

bool move_inside_board(Move);

bool point_inside_board(Point);

bool board_points_team(const Piece[], Point, Point);

bool board_pieces_team(Piece, Piece);

bool board_teams_team(Piece, Piece);

bool board_teams_enemy(Piece, Piece);

short positive_short_value(short);

bool team_move_value(short*, Piece);

bool team_starting_rank(Rank*, Piece);

bool team_pawn_rank(Rank*, Piece);

bool team_rank_offset(short*, Point, Point, Piece);

bool team_file_offset(short*, Point, Point, Piece);

#endif