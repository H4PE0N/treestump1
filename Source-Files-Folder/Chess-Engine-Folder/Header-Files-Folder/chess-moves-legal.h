
#ifndef CHESS_MOVES_LEGAL_H
#define CHESS_MOVES_LEGAL_H

bool move_fully_legal(const Piece[], Info, Move);

bool move_pseudo_legal(const Piece[], Info, Move);

bool board_move_legal(const Piece[], Move);

bool piece_legal_moves(Move**, const Piece[], Info, Point);

bool piece_legal_points(Point**, const Piece[], Info, Point);

bool team_legal_moves(Move**, const Piece[], Info, unsigned short);

void append_promote_moves(Move*, short*, Move);

#endif
