
#ifndef OPTIMAL_DEPTH_MOVE_H
#define OPTIMAL_DEPTH_MOVE_H

bool optimal_depth_move(Move* move, const Piece board[], Info info, Entry* hashTable, short seconds);

bool search_depths_move(Move* move, const Piece board[], Info info, Entry* hashTable, int playerSign, short seconds, const Move moveArray[], int moveAmount);

bool choose_timing_move(Move* move, signed short* score, const Piece board[], Info info, Entry* hashTable, short depth, int playerSign, long startClock, short seconds, const Move moveArray[], int moveAmount);

bool timing_limit_ended(long startClock, short seconds);

double time_passed_since(long startClock);

#endif
