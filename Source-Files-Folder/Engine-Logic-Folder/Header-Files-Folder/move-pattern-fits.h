
#ifndef MOVE_PATTERN_FITS_H
#define MOVE_PATTERN_FITS_H

bool move_pattern_fits(const Piece board[], Move move);

bool normal_pattern_fits(const Piece board[], Move move);

bool clear_moving_path(const Piece board[], Move move);

bool testing_clear_path(const Piece board[], const Point movePoints[], int amount, Move move);

bool moving_path_points(Point** movePoints, Move move);

bool moving_path_values(int8_t* rankFactor, int8_t* fileFactor, int8_t* moveSteps, Move move);

bool passant_pattern_fits(const Piece board[], Move move);

bool castle_pattern_fits(const Piece board[], Move castleMove);

bool pawn_pattern_fits(const Piece board[], Move move);

Point castle_rook_point(Move castleMove);

#endif
