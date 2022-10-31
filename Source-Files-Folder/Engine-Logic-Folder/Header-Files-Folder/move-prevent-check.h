
#ifndef MOVE_PREVENT_CHECK_H
#define MOVE_PREVENT_CHECK_H

bool move_prevent_check(const Piece board[], Info info, Move move);

bool prevent_check_test(Piece* boardCopy, Info infoCopy, Move move);

bool move_check_handler(const Piece board[], Info info, Move move);

bool castle_prevent_check(const Piece board[], Info info, Move castleMove);

Move castle_middle_move(Move castleMove);

Point castle_middle_point(Move castleMove);

#endif
