
#ifndef GAME_CONSOLE_ACTIONS_H
#define GAME_CONSOLE_ACTIONS_H

bool console_result_handler(const Piece board[], State state);

bool console_user_handler(Piece* board, State* state);

bool console_engine_handler(Piece* board, State* state, Entry* hashTable);

#endif
