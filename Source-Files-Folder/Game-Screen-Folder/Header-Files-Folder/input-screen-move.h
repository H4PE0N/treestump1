
#ifndef INPUT_SCREEN_MOVE_H
#define INPUT_SCREEN_MOVE_H

bool input_screen_move(Move*, Screen, const Piece[], Info, Kings, const Move[]);

bool screen_move_parser(Move*, Screen, const Piece[], Info, Kings, const Move[], Event);

#endif
