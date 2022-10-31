
#ifndef STRING_BOARD_PARSER_H
#define STRING_BOARD_PARSER_H

bool parse_create_board(Piece** board, Info* info, const char fenString[]);

bool parse_fen_string(Piece* board, Info* info, const char fenString[]);

bool parse_string_board(Piece* board, const char stringToken[]);

bool parse_board_piece(Piece* piece, char symbol);

bool parse_string_array(Piece* board, Info* info, char* stringArray[]);

bool parse_string_info(Info* info, char* stringArray[]);

bool parse_string_counter(Info* info, const char stringToken[]);

bool parse_string_turns(Info* info, const char stringToken[]);

bool parse_string_passant(Info* info, const char stringToken[]);

bool parse_string_point(Point* point, const char string[]);

bool parse_string_move(Move* move, const char stringMove[]);

bool parse_string_castles(Info* info, const char stringToken[]);

bool parse_castle_symbol(Info* infoCastle, char symbol);

bool parse_string_current(Info* info, const char stringToken[]);

bool parse_board_files(Piece* board, unsigned short rank, const char rankString[], short length);

bool parse_board_symbol(Piece* board, unsigned short rank, unsigned short* file, char symbol);

bool parse_board_blanks(Piece* board, unsigned short rank, unsigned short* file, short blanks);



char chess_piece_symbol(Piece piece);

#endif
