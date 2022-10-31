
#ifndef SEARCH_DEPTH_NODES_H
#define SEARCH_DEPTH_NODES_H

long search_depth_nodes(const Piece board[], Info info, unsigned short currentTeam, short depth, long startClock, short seconds);

long search_move_nodes(const Piece board[], Info info, unsigned short currentTeam, short depth, Move move, long startClock, short seconds);

#endif
