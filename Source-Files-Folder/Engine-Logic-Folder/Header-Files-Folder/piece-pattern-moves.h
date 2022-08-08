
#ifndef PIECE_PATTERN_MOVES_H
#define PIECE_PATTERN_MOVES_H

bool piece_pattern_moves(Move**, const Piece[], Point);

bool pawn_pattern_moves(Move**, const Piece[], Point);

bool knight_pattern_moves(Move**, const Piece[], Point);

bool bishop_pattern_moves(Move**, const Piece[], Point);

bool rook_pattern_moves(Move**, const Piece[], Point);

bool queen_pattern_moves(Move**, const Piece[], Point);

bool king_pattern_moves(Move**, const Piece[], Point);

bool diagonal_pattern_moves(Move**, const Piece[], Point);

bool straight_pattern_moves(Move**, const Piece[], Point);

#endif
