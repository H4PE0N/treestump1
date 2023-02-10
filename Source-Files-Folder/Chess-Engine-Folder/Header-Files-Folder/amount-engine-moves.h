
#ifndef AMOUNT_ENGINE_MOVES_H
#define AMOUNT_ENGINE_MOVES_H

bool amount_engine_moves(Move** moveArray, const Piece board[], State state, Entry* hashTable, uint8_t team, int depth, int amount);

void paste_engine_moves(Move** moveArray, int amount, const Move engineMoves[], int engineAmount);

bool sorted_engine_moves(Move** moveArray, int* moveAmount, const Piece board[], State state, Entry* hashTable, uint8_t evalTeam, int depth);

bool move_array_scores(int** moveScores, const Piece board[], State state, Entry* hashTable, uint8_t team, int depth, const Move moveArray[], int moveAmount);

#endif
