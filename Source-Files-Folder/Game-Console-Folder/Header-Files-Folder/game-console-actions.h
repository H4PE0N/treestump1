
#ifndef GAME_CONSOLE_ACTIONS_H
#define GAME_CONSOLE_ACTIONS_H

bool console_result_handler(const Piece board[], Info info);

bool console_user_handler(Piece* board, Info* info);

bool console_engine_handler(Piece* board, Info* info, Entry* hashTable);

#endif
