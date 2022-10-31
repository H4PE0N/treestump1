
#ifndef OPTIMAL_DEPTH_MOVE_H
#define OPTIMAL_DEPTH_MOVE_H

bool optimal_depth_move(Move* move, const Piece board[], Info info, unsigned short team, short seconds);

bool search_depths_move(Move* move, const Piece board[], Info info, unsigned short team, short seconds, const Move moveArray[], short moveAmount);

bool choose_timing_move(Move* move, signed short* value, const Piece board[], Info info, unsigned short team, short depth, long startClock, short seconds, const Move moveArray[], short moveAmount);

bool timing_limit_ended(long startClock, short seconds);

double time_passed_since(long startClock);

#endif
