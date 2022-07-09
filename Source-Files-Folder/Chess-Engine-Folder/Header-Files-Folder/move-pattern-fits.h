
#ifndef MOVE_PATTERN_FITS_H
#define MOVE_PATTERN_FITS_H

bool move_pattern_fits(const Piece[], Move);

bool normal_pattern_fits(const Piece[], Move);

bool clear_moving_path(const Piece[], Move);

bool testing_clear_path(const Piece[], const Point[], short, Move);

bool moving_path_points(Point**, Move);

bool moving_path_values(signed short*, signed short*, short*, Move);

bool passant_pattern_fits(const Piece[], Move);

bool castle_pattern_fits(const Piece[], Move);

bool pawn_pattern_fits(const Piece[], Move);

Point castle_rook_point(Move);

#endif
