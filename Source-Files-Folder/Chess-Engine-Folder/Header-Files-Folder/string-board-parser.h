
#ifndef BOARD_PARSER_H
#define BOARD_PARSER_H

bool parse_game_string(Piece**, Info*, char[]);

bool parse_string_board(Piece**, char[]);

bool parse_board_piece(Piece*, char);

bool parse_string_counter(Counter*, char[]);

bool parse_string_turns(Turns*, char[]);

bool parse_string_passant(Passant*, char[]);

//bool parse_string_point(Point*, char[]);

//bool parse_string_move(Move*, char[]);

bool parse_string_castles(Info*, char[]);

bool parse_string_short(unsigned short*, char[]);

bool parse_string_current(Info*, char[]);

#endif