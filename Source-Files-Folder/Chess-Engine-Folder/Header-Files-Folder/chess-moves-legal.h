
#ifndef CHESS_MOVES_LEGAL_H
#define CHESS_MOVES_LEGAL_H

bool move_fully_legal(const Piece[], Info, Kings, Move);

bool move_pseudo_legal(const Piece[], Info, Move);

bool move_pattern_fits(const Piece[], Info, Move);

bool clear_moving_path(const Piece[], Move, Piece);

bool move_ability_valid(Move, Piece, Info);

bool move_prevent_check(const Piece[], Info, Kings, Move);

bool current_team_move(Info, Piece);

#endif
