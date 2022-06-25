
#ifndef GAME_ACTIONS_HANDLER_H
#define GAME_ACTIONS_HANDLER_H

bool screen_user_handler(Piece*, Info*, Kings*, Move*, Screen, bool*);

bool screen_computer_handler(Piece*, Info*, Kings*, Move*, Screen);

bool screen_single_game(Piece*, Info*, Kings*, Move*, Screen, bool*, bool);

bool screen_cheat_handler(Piece*, Info*, Kings*, Move*, Screen, bool*);

bool screen_cheat_game(Piece*, Info*, Kings*, Move*, Screen, bool*);

bool screen_multi_game(Piece*, Info*, Kings*, Move*, Screen, bool*);

bool game_result_handler(Screen, const Piece[], Info, Kings, bool*);

#endif
