
#ifndef GAME_SCREEN_ACTIONS_H
#define GAME_SCREEN_ACTIONS_H

bool input_promote_move(Move*, Screen, unsigned short);

bool input_screen_move(Move*, Screen, const Piece[], Info, Kings, const Move[]);

bool screen_move_parser(Move*, Screen, const Piece[], Info, Kings, const Move[], Event);

#endif
