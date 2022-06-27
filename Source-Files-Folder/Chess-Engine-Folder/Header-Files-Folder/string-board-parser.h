
#ifndef STRING_BOARD_PARSER_H
#define STRING_BOARD_PARSER_H

bool parse_game_string(Piece**, Info*, Kings*, const char[]);

bool parse_string_board(Piece**, const char[]);

bool parse_board_piece(Piece*, char);

bool parse_string_array(Piece**, Info*, Kings*, char*[]);

bool parse_string_info(Info*, char*[]);

bool parse_string_counter(Info*, const char[]);

bool parse_string_turns(Info*, const char[]);

bool parse_string_passant(Info*, const char[]);

bool parse_string_point(Point*, const char[]);

bool parse_string_castles(Info*, const char[]);

bool parse_castle_symbol(Info*, char);

bool parse_string_short(unsigned short*, const char[]);

bool parse_string_current(Info*, const char[]);

bool parse_king_points(Kings*, const Piece[]);

char chess_piece_symbol(Piece);

bool parse_board_files(Piece**, unsigned short, const char[], unsigned short);

bool parse_board_symbol(Piece**, unsigned short, unsigned short*, char);

bool parse_board_blanks(Piece**, unsigned short, unsigned short*, unsigned short);


bool create_game_string(char**, const Piece[], Info);

bool create_string_info(char*[], Info);

bool create_string_counter(char*, Info);

bool create_string_turns(char*, Info);

bool create_string_passant(char*, Info);

bool create_string_castles(char*, Info);

bool create_string_current(char*, Info);

bool create_string_board(char*, const Piece[]);

bool create_board_files(char*, const Piece[], unsigned short);

bool create_blank_symbol(char*, unsigned short, unsigned short*, const Piece[]);


Point passant_pawn_point(Info);

#endif
