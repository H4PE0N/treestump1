
#ifndef PIECE_PATTERN_MOVES_H
#define PIECE_PATTERN_MOVES_H

bool piece_pattern_moves(Move** moves, int* moveAmount, const Piece board[], Point piecePoint);

bool pawn_pattern_moves(Move** moves, int* moveAmount, const Piece board[], Point piecePoint);

bool knight_pattern_moves(Move** moves, int* moveAmount, const Piece board[], Point piecePoint);

bool bishop_pattern_moves(Move** moves, int* moveAmount, const Piece board[], Point piecePoint);

bool rook_pattern_moves(Move** moves, int* moveAmount, const Piece board[], Point piecePoint);

bool queen_pattern_moves(Move** moves, int* moveAmount, const Piece board[], Point piecePoint);

bool king_pattern_moves(Move** moves, int* moveAmount, const Piece board[], Point piecePoint);

bool diagonal_pattern_moves(Move** moves, int* moveAmount, const Piece board[], Point piecePoint);

bool straight_pattern_moves(Move** moves, int* moveAmount, const Piece board[], Point piecePoint);

#endif
