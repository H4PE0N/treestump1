
#ifndef CREATE_COMPUTER_MOVE_H
#define CREATE_COMPUTER_MOVE_H

bool best_computer_move(Move*, const Piece[], Info, Kings, unsigned short, signed short);

unsigned short board_depth_value(const Piece[], Info, Kings, signed short, signed short, signed short, unsigned short, unsigned short);

#endif
