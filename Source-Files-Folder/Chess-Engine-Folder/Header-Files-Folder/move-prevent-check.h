
#ifndef MOVE_PREVENT_CHECK_H
#define MOVE_PREVENT_CHECK_H

bool move_prevent_check(const Piece[], Info, Kings, Move);

bool prevent_check_test(Piece*, Info, Kings, Move);

bool move_check_handler(const Piece[], Info, Kings, Move);

bool castle_prevent_check(const Piece[], Info, Kings, Move);

Point castle_middle_move(Move);

#endif
