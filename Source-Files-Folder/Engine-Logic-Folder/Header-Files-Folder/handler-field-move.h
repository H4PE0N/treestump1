
#ifndef HANDLER_FIELD_MOVE_H
#define HANDLER_FIELD_MOVE_H

bool move_inside_board(Move move);

bool move_points_team(const Piece board[], Move move);

bool move_points_enemy(const Piece board[], Move move);

short move_rank_offset(Move move, unsigned short team);

short move_file_offset(Move move, unsigned short team);

unsigned short abs_move_roffset(Move move, unsigned short team);

unsigned short abs_move_foffset(Move move, unsigned short team);

short normal_rank_offset(Move move);

short normal_file_offset(Move move);

Move* create_move_array(short arrayLength);

signed short board_move_pattern(Move move);

bool create_move_string(char* moveString, const Piece board[], Info info, Move move);

bool create_point_string(char* pointString, Point point);

signed short move_offset_factor(signed short moveOffset);

Piece move_start_piece(Move move, const Piece board[]);

Piece move_stop_piece(Move move, const Piece board[]);

Piece start_piece_type(Move move, const Piece board[]);

Piece stop_piece_type(Move move, const Piece board[]);

bool start_stop_team(Move move, const Piece board[]);

unsigned short move_array_amount(const Move moveArray[]);

void append_moves_array(Move* moveArray, const Move addingArray[]);

#endif
