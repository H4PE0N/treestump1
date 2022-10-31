
#ifndef CONSOLE_INPUT_HANDLER_H
#define CONSOLE_INPUT_HANDLER_H

bool input_console_move(Move* move, const Piece board[], Info info);

bool input_stdin_string(char* string, const char inputPromt[]);

#endif
