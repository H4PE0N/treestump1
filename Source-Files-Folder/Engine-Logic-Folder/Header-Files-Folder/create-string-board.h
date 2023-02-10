
#ifndef CREATE_STRING_BOARD_H
#define CREATE_STRING_BOARD_H

bool create_fen_string(char* fenString, const Piece board[], State state);

bool create_fen_string_t(char* fenString, char** stringArray, const Piece board[], State state);

bool create_string_state(char* stringArray[], State state);

bool create_string_clock(char* string, State state);

bool create_string_turns(char* string, State state);

bool create_string_passant(char* string, State state);

bool create_string_castles(char* string, State state);

bool create_string_current(char* string, State state);

bool create_string_board(char* string, const Piece board[]);

bool create_string_board_t(char* string, char** stringArray, const Piece board[]);

bool create_board_files(char* string, const Piece board[], uint8_t rank);

bool create_blank_symbol(char* symbol, uint8_t rank, uint8_t* file, const Piece board[]);

bool create_string_move(char* string, Move move);

bool create_string_point(char* string, Point point);

bool create_fenstr_parts(char* stringArray[], const Piece board[], State state);

bool promote_piece_symbol(char* symbol, Move move);

bool append_piece_symbol(char* string, const Piece board[], Point point);

bool append_blank_symbol(char* string, const Piece board[], uint8_t rank, uint8_t* file);

#endif
