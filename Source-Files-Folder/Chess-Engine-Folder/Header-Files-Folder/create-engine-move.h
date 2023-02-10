
#ifndef CREATE_ENGINE_MOVE_H
#define CREATE_ENGINE_MOVE_H

bool engine_depth_move(Move* bestMove, const Piece board[], State state, Entry* hashTable, int depth);

bool choose_engine_move(Move* bestMove, const Piece board[], State state, Entry* hashTable, int depth, int playerSign, const Move moveArray[], int moveAmount);

int board_depth_score(const Piece board[], State state, Entry* hashTable, int depth, int alpha, int beta, int playerSign);

int storgryta(const Piece board[], State state, Entry* hashTable, int depth, int alpha, int beta, int playerSign);

int choose_move_score(const Piece board[], State state, Entry* hashTable, int depth, int alpha, int beta, int playerSign, const Move moveArray[], int moveAmount);

int chess_move_score(const Piece board[], State state, Entry* hashTable, int depth, int alpha, int beta, int playerSign, Move move);

int simulate_move_score(Piece* boardCopy, State stateCopy, Entry* hashTable, int depth, int alpha, int beta, int playerSign, Move move);

#endif
