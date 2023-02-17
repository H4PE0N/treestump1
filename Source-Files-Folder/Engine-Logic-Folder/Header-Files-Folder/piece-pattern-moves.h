
#ifndef PIECE_PATTERN_MOVES_H
#define PIECE_PATTERN_MOVES_H

bool piece_pattern_moves(Move** moveArray, int* moveAmount, const Piece board[], Point piecePoint);

bool pawn_pattern_moves(Move** moveArray, int* moveAmount, const Piece board[], Point piecePoint);

void append_pawn_pmoves(Move* moveArray, int* moveAmount, uint8_t team, Point piecePoint, uint8_t pieceRank, uint8_t pieceFile);

bool append_pawn_pmove(Move* moveArray, int* moveAmount, uint8_t team, Point piecePoint, uint8_t pieceRank, uint8_t pieceFile, uint8_t rank, uint8_t file);

bool knight_pattern_moves(Move** moveArray, int* moveAmount, const Piece board[], Point piecePoint);

void append_knight_pmoves(Move* moveArray, int* moveAmount, Point piecePoint, uint8_t pieceRank, uint8_t pieceFile);

bool append_knight_pmove(Move* moveArray, int* moveAmount, Point piecePoint, uint8_t pieceRank, uint8_t pieceFile, uint8_t rank, uint8_t file);

bool bishop_pattern_moves(Move** moveArray, int* moveAmount, const Piece board[], Point piecePoint);

bool rook_pattern_moves(Move** moveArray, int* moveAmount, const Piece board[], Point piecePoint);

bool queen_pattern_moves(Move** moveArray, int* moveAmount, const Piece board[], Point piecePoint);

bool king_pattern_moves(Move** moveArray, int* moveAmount, const Piece board[], Point piecePoint);

void append_king_pmoves(Move* moveArray, int* moveAmount, Point piecePoint, uint8_t pieceRank, uint8_t pieceFile);

bool append_king_pmove(Move* moveArray, int* moveAmount, Point piecePoint, uint8_t pieceRank, uint8_t pieceFile, uint8_t rank, uint8_t file);

bool diagonal_pattern_moves(Move** moveArray, int* moveAmount, const Piece board[], Point piecePoint);

void append_d2type_pmoves(Move* moveArray, int* moveAmount, Point piecePoint, uint8_t pieceRank, uint8_t pieceFile);

void append_d1type_pmoves(Move* moveArray, int* moveAmount, Point piecePoint, uint8_t pieceRank, uint8_t pieceFile);

bool append_diagonal_pmove(Move* moveArray, int* moveAmount, Point piecePoint, uint8_t realRank, uint8_t realFile);

bool straight_pattern_moves(Move** moveArray, int* moveAmount, const Piece board[], Point piecePoint);

void append_s1type_pmoves(Move* moveArray, int* moveAmount, Point piecePoint, uint8_t pieceFile);

void append_s2type_pmoves(Move* moveArray, int* moveAmount, Point piecePoint, uint8_t pieceRank);

#endif
