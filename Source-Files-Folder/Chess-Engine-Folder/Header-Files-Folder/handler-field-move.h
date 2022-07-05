
#ifndef HANDLER_FIELD_MOVE_H
#define HANDLER_FIELD_MOVE_H

Move start_stop_move(Point, Point);

bool move_inside_board(Move);

bool move_points_team(const Piece[], Move);

bool move_points_enemy(const Piece[], Move);

short move_rank_offset(Move, unsigned short);

short move_file_offset(Move, unsigned short);

short normal_rank_offset(Move);

short normal_file_offset(Move);

unsigned short move_array_amount(const Move[]);

Move* create_move_array(unsigned short);

signed short board_move_pattern(Move);

bool create_move_string(char*, const Piece[], Info, Kings, Move);

bool create_point_string(char*, Point);

#endif
