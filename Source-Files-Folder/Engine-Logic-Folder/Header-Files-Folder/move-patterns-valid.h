
#ifndef MOVE_PATTERNS_VALID_H
#define MOVE_PATTERNS_VALID_H

bool pawn_pattern_valid(Move move, unsigned short team);

bool knight_pattern_valid(Move move, unsigned short team);

bool bishop_pattern_valid(Move move, unsigned short team);

bool queen_pattern_valid(Move move, unsigned short team);

bool king_pattern_valid(Move move, unsigned short team);

bool rook_pattern_valid(Move move, unsigned short team);

bool castle_pattern_valid(Move move, unsigned short team);

bool double_pattern_valid(Move move, unsigned short team);

bool passant_pattern_valid(Move move, unsigned short team);

bool promote_pattern_valid(Move move, unsigned short team);

#endif
