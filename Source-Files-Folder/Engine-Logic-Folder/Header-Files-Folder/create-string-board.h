
#ifndef CREATE_STRING_BOARD_H
#define CREATE_STRING_BOARD_H

bool create_fen_string(char*, const Piece[], Info);

bool create_string_info(char*[], Info);

bool create_string_counter(char*, Info);

bool create_string_turns(char*, Info);

bool create_string_passant(char*, Info);

bool create_string_castles(char*, Info);

bool create_string_current(char*, Info);

bool create_string_board(char*, const Piece[]);

bool create_board_files(char*, const Piece[], unsigned short);

bool create_blank_symbol(char*, unsigned short, unsigned short*, const Piece[]);

bool create_string_move(char*, Move);

bool create_string_point(char*, Point);

#endif
