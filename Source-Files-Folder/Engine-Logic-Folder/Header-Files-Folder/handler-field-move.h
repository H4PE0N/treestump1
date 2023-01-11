
#ifndef HANDLER_FIELD_MOVE_H
#define HANDLER_FIELD_MOVE_H

int8_t move_rank_offset(Move move, uint8_t team);

int8_t move_file_offset(Move move, uint8_t team);

int8_t normal_rank_offset(Move move);

int8_t normal_file_offset(Move move);

Move* create_move_array(int arrayLength);

bool create_move_string(char* moveString, const Piece board[], Info info, Move move);

bool create_point_string(char* pointString, Point point);

int move_array_amount(const Move moveArray[]);

char piece_move_symbol(Piece piece);

bool chess_move_capture(Move move, const Piece board[], Info info);

bool castle_move_string(char* moveString, Move move);

bool piece_place_string(char* placeString, const Piece board[], Point point);

bool equal_piece_rank(const Piece board[], Point point);

bool equal_piece_file(const Piece board[], Point point);

bool equal_piece_attack(const Piece board[], Info info, Move move);

bool pattern_moves_equal(Move move1, Move move2);

bool equal_pattern_moves(Move** moves, int* moveAmount, const Piece board[], Move move);

bool target_pattern_moves(Move** moves, int* moveAmount, const Piece board[], Move move);

bool start_pieces_equal(const Piece board[], Move move1, Move move2);

void append_move_array(Move* moves1, int* amount1, const Move moves2[], int amount2);

void paste_capped_moves(Move* moves1, int amount1, const Move moves2[], int amount2);

void paste_move_array(Move* moves1, const Move moves2[], int moveAmount);

Move* copy_move_array(const Move moveArray[], int moveAmount);

#endif
