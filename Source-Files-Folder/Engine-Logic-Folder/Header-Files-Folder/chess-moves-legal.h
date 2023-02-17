
#ifndef CHESS_MOVES_LEGAL_H
#define CHESS_MOVES_LEGAL_H

bool move_fully_legal(const Piece board[], State state, Move move);

bool move_pseudo_legal(const Piece board[], State state, Move move);

bool board_move_legal(const Piece board[], Move move);

bool piece_legal_moves(Move** moveArray, int* moveAmount, const Piece board[], State state, Point piecePoint);

bool piece_legal_points(Point** pointArray, int* pointAmount, const Piece board[], State state, Point piecePoint);

bool team_legal_moves(Move** moveArray, int* moveAmount, const Piece board[], State state);

bool append_piece_moves(Move* moveArray, int* moveAmount, const Piece board[], State state, uint8_t team, Point point);

void append_promote_moves(Move* moveArray, int* moveAmount, Move promoteMove);

bool pattern_move_legal(Move* patternMove, const Piece board[], State state);

#endif
