
#ifndef GAME_SCREEN_ACTIONS_H
#define GAME_SCREEN_ACTIONS_H

bool screen_user_handler(Piece*, Info*, Move*, Screen*);

bool screen_engine_handler(Piece*, Info*, Entry* hashTable, Move*, Screen);

bool screen_result_handler(Screen*, const Piece[], Info);

#endif
