
#ifndef CHESS_MOVES_LEGAL_H
#define CHESS_MOVES_LEGAL_H

bool move_fully_legal(const Piece[], Info, Move);

bool move_pseudo_legal(const Piece[], Info, Move);

bool move_pattern_fits(const Piece[], Info, Move);

bool move_pattern_valid(Move, Piece);

bool pattern_list_valid(const signed short[], unsigned short, Move, Piece);

bool clear_moving_path(const Piece[], Move);

#endif