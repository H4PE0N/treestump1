
#ifndef GAME_SCREEN_ACTIONS_H
#define GAME_SCREEN_ACTIONS_H

bool screen_user_handler(Piece*, State*, Move*, Screen*);

bool screen_engine_handler(Piece*, State*, Entry* hashTable, Move*, Screen);

bool screen_result_handler(Screen*, const Piece[], State);

#endif
