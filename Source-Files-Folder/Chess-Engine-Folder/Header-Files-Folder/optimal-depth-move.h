
#ifndef OPTIMAL_DEPTH_MOVE_H
#define OPTIMAL_DEPTH_MOVE_H

bool optimal_depth_move(Move* move, const Piece board[], State state, Entry* hashTable, int seconds);

bool search_depths_move(Move* move, const Piece board[], State state, Entry* hashTable, int seconds, const Move moveArray[], int moveAmount);

bool choose_timing_move(Move* move, int* score, const Piece board[], State state, Entry* hashTable, int depth, int playerSign, long startClock, int seconds, const Move moveArray[], int moveAmount);

bool timing_limit_ended(long startClock, int seconds);

double time_passed_since(long startClock);

#endif
