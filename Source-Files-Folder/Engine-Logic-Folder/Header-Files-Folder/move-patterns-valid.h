
#ifndef MOVE_PATTERNS_VALID_H
#define MOVE_PATTERNS_VALID_H

bool pawn_pattern_valid(Move move, uint8_t team);

bool knight_pattern_valid(Move move, uint8_t team);

bool bishop_pattern_valid(Move move, uint8_t team);

bool queen_pattern_valid(Move move, uint8_t team);

bool king_pattern_valid(Move move, uint8_t team);

bool rook_pattern_valid(Move move, uint8_t team);

bool castle_pattern_valid(Move move, uint8_t team);

bool double_pattern_valid(Move move, uint8_t team);

bool passant_pattern_valid(Move move, uint8_t team);

bool promote_pattern_valid(Move move, uint8_t team);

#endif
