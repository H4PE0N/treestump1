
#ifndef MOVE_PREVENT_CHECK_H
#define MOVE_PREVENT_CHECK_H

bool move_prevent_check(const Piece[], Info, Move);

bool prevent_check_test(Piece*, Info, Move);

bool move_check_handler(const Piece[], Info, Move);

bool castle_prevent_check(const Piece[], Info, Move);

Point castle_middle_move(Move);

#endif
