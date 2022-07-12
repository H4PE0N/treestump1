
#ifndef OPTIMAL_DEPTH_MOVE_H
#define OPTIMAL_DEPTH_MOVE_H

bool optimal_depth_move(Move*, const Piece[], Info, unsigned short, short);

bool search_depths_move(Move*, const Piece[], Info, unsigned short, short, const Move[], short);

bool choose_timing_move(Move*, signed short*, const Piece[], Info, unsigned short, short, long, short, const Move[], short);

bool timing_limit_ended(long, short);

double time_passed_since(long);

#endif
