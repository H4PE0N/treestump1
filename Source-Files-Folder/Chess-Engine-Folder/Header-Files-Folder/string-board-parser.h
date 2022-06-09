
#ifndef BOARD_PARSER_H
#define BOARD_PARSER_H

bool parse_game_string(Piece**, Info*, Kings*, const char[]);

bool parse_string_board(Piece**, const char[]);

bool parse_board_piece(Piece*, char);

bool parse_string_counter(unsigned short*, const char[]);

bool parse_string_turns(unsigned short*, const char[]);

bool parse_string_passant(unsigned short*, const char[]);

bool parse_string_point(Point*, const char[]);

bool parse_string_castles(Info*, const char[]);

bool parse_string_short(unsigned short*, const char[]);

bool parse_string_current(Info*, const char[]);

bool parse_king_points(Kings*, const Piece[]);

char chess_piece_symbol(Piece);

bool parse_board_files(Piece**, unsigned short, const char[], unsigned short);

bool parse_board_symbol(Piece**, unsigned short, unsigned short*, char);

bool parse_board_blanks(Piece**, unsigned short, unsigned short*, unsigned short);

#endif
