
#ifndef CHESS_MOVES_LEGAL_H
#define CHESS_MOVES_LEGAL_H

bool move_fully_legal(const Piece[], Info, Kings, Move);

bool move_pseudo_legal(const Piece[], Info, Move);

bool move_pattern_fits(const Piece[], Move);

bool clear_moving_path(const Piece[], Move);

bool move_ability_valid(Move, Piece, Info);

bool move_prevent_check(const Piece[], Info, Kings, Move);

bool current_team_move(Info, Piece);

Point castle_rook_point(Move, unsigned short);

bool passant_ability_valid(Move, Info);

bool castle_ability_valid(Move, Info, Piece);

bool passant_pattern_fits(const Piece[], Move);

bool castle_pattern_fits(const Piece[], Move);

bool pawn_pattern_fits(const Piece[], Move);

bool piece_legal_moves(Move**, const Piece[], Info, Kings, Point);

bool team_legal_moves(Move**, const Piece[], Info, Kings, unsigned short);

#endif
