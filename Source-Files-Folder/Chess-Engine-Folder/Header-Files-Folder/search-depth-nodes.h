
#ifndef SEARCH_DEPTH_NODES_H
#define SEARCH_DEPTH_NODES_H

long search_depth_nodes(const Piece board[], Info info, uint8_t currentTeam, int depth, long startClock, int seconds);

long search_move_nodes(const Piece board[], Info info, uint8_t currentTeam, int depth, Move move, long startClock, int seconds);

#endif
