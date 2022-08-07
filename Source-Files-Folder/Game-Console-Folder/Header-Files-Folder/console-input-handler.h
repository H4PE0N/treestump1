
#ifndef CONSOLE_INPUT_HANDLER_H
#define CONSOLE_INPUT_HANDLER_H

bool input_console_move(Move*, const Piece[], Info);

bool input_stdin_string(char*, const char[]);

bool parse_string_move(Move*, const char[]);

#endif
