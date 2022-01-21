
#ifndef MOVE_PATTERNS_VALID_H
#define MOVE_PATTERNS_VALID_H

bool move_pattern_valid(Move, Piece);


bool pawn_pattern_handler(Move, Piece);

bool knight_pattern_handler(Move, Piece);

bool bishop_pattern_handler(Move, Piece);

bool queen_pattern_handler(Move, Piece);

bool king_pattern_handler(Move, Piece);

bool rook_pattern_handler(Move, Piece);


bool pawn_pattern_valid(Move, Piece);

bool knight_pattern_valid(Move, Piece);

bool bishop_pattern_valid(Move, Piece);

bool queen_pattern_valid(Move, Piece);

bool king_pattern_valid(Move, Piece);

bool rook_pattern_valid(Move, Piece);


bool castle_pattern_valid(Move, Piece);

bool double_pattern_valid(Move, Piece);

bool passant_pattern_valid(Move, Piece);

bool promote_pattern_valid(Move, Piece);

#endif
