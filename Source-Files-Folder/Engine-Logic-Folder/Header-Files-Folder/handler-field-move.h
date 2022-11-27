
#ifndef HANDLER_FIELD_MOVE_H
#define HANDLER_FIELD_MOVE_H

short move_rank_offset(Move move, unsigned short team);

short move_file_offset(Move move, unsigned short team);

unsigned short abs_move_roffset(Move move, unsigned short team);

unsigned short abs_move_foffset(Move move, unsigned short team);

short normal_rank_offset(Move move);

short normal_file_offset(Move move);

Move* create_move_array(short arrayLength);

bool create_move_string(char* moveString, const Piece board[], Info info, Move move);

bool create_point_string(char* pointString, Point point);

unsigned short move_array_amount(const Move moveArray[]);

void append_moves_array(Move* moveArray, const Move addingArray[]);

char piece_move_symbol(Piece piece);

bool chess_move_capture(Move move, const Piece board[], Info info);

bool castle_move_string(char* moveString, Move move);

bool piece_place_string(char* placeString, const Piece board[], Point point);

bool equal_piece_rank(const Piece board[], Point point);

bool equal_piece_file(const Piece board[], Point point);

bool equal_piece_attack(const Piece board[], Info info, Move move);

bool pattern_moves_equal(Move move1, Move move2);

bool equal_pattern_moves(Move** moves, const Piece board[], Move move);

bool target_pattern_moves(Move** moves, const Piece board[], Move move);

bool start_pieces_equal(const Piece board[], Move move1, Move move2);

#endif
