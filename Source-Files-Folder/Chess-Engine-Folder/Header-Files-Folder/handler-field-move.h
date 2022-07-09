
#ifndef HANDLER_FIELD_MOVE_H
#define HANDLER_FIELD_MOVE_H

bool move_inside_board(Move);

bool move_points_team(const Piece[], Move);

bool move_points_enemy(const Piece[], Move);

short move_rank_offset(Move, unsigned short);

short move_file_offset(Move, unsigned short);

unsigned short abs_move_roffset(Move, unsigned short);

unsigned short abs_move_foffset(Move, unsigned short);

short normal_rank_offset(Move);

short normal_file_offset(Move);

unsigned short move_array_amount(const Move[]);

Move* create_move_array(short);

signed short board_move_pattern(Move);

bool create_move_string(char*, const Piece[], Info, Move);

bool create_point_string(char*, Point);

signed short move_offset_factor(signed short);

Piece move_start_piece(Move, const Piece[]);

Piece move_stop_piece(Move, const Piece[]);

Piece start_piece_type(Move, const Piece[]);

Piece stop_piece_type(Move, const Piece[]);

bool start_stop_team(Move, const Piece[]);

#endif
