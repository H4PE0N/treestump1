
#ifndef STRING_BOARD_PARSER_H
#define STRING_BOARD_PARSER_H

bool parse_create_board(Piece** board, State* state, const char fenString[]);

bool parse_fen_string(Piece* board, State* state, const char fenString[]);

bool parse_string_board(Piece* board, const char stringToken[]);

bool parse_board_piece(Piece* piece, char symbol);

bool parse_string_array(Piece* board, State* state, char* stringArray[]);

bool parse_string_state(State* state, char* stringArray[]);

bool parse_string_clock(State* state, const char stringToken[]);

bool parse_string_turns(State* state, const char stringToken[]);

bool parse_string_passant(State* state, const char stringToken[]);

bool parse_string_point(Point* point, const char string[]);

bool string_basic_move(Move* move, const char stringMove[]);

bool parse_string_castles(State* state, const char stringToken[]);

bool parse_castle_symbol(State* stateCastle, char symbol);

bool parse_string_current(State* state, const char stringToken[]);

bool parse_board_files(Piece* board, uint8_t rank, const char rankString[], int length);

bool parse_board_symbol(Piece* board, uint8_t rank, uint8_t* file, char symbol);

bool parse_board_blanks(Piece* board, uint8_t rank, uint8_t* file, short blanks);

char chess_piece_symbol(Piece piece);

#endif
