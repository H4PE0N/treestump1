
#ifndef CHESS_MOVES_LEGAL_H
#define CHESS_MOVES_LEGAL_H

bool move_fully_legal(const Piece[], Info, Kings, Move);

bool move_pseudo_legal(const Piece[], Info, Move);

bool move_pattern_fits(const Piece[], Move);

bool clear_moving_path(const Piece[], Move);

bool testing_clear_path(const Piece[], const Point[], unsigned short, Move);

bool moving_path_points(Point**, const Piece[], Move);

bool moving_path_values(signed short*, signed short*, unsigned short*, Move);

bool move_ability_valid(Move, Piece, Info);

bool move_prevent_check(const Piece[], Info, Kings, Move);

bool prevent_check_test(Piece*, Info, Kings, Move);

bool move_check_handler(const Piece[], Info, Kings, Move);

bool castle_prevent_check(const Piece[], Info, Kings, Move);

Point castle_middle_move(Move);

bool current_team_move(Info, Piece);

Point castle_rook_point(Move, unsigned short);

bool passant_ability_valid(Move, Info);

bool castle_ability_valid(Move, Info, Piece);

bool passant_pattern_fits(const Piece[], Move);

bool castle_pattern_fits(const Piece[], Move);

bool pawn_pattern_fits(const Piece[], Move);

bool piece_legal_moves(Move**, const Piece[], Info, Kings, Point);

bool team_legal_moves(Move**, const Piece[], Info, Kings, unsigned short);

signed short move_offset_factor(signed short);

#endif
