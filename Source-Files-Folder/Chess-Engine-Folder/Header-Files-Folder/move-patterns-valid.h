
#ifndef MOVE_PATTERNS_VALID_H
#define MOVE_PATTERNS_VALID_H

bool move_pattern_valid(Move, Piece);


bool pawn_pattern_handler(Move, unsigned short);

bool knight_pattern_handler(Move, unsigned short);

bool bishop_pattern_handler(Move, unsigned short);

bool queen_pattern_handler(Move, unsigned short);

bool king_pattern_handler(Move, unsigned short);

bool rook_pattern_handler(Move, unsigned short);


bool pawn_pattern_valid(Move, unsigned short);

bool knight_pattern_valid(Move, unsigned short);

bool bishop_pattern_valid(Move, unsigned short);

bool queen_pattern_valid(Move, unsigned short);

bool king_pattern_valid(Move, unsigned short);

bool rook_pattern_valid(Move, unsigned short);


bool castle_pattern_valid(Move, unsigned short);

bool double_pattern_valid(Move, unsigned short);

bool passant_pattern_valid(Move, unsigned short);

bool promote_pattern_valid(Move, unsigned short);

#endif
