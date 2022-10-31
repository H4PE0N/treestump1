
#ifndef CHESS_MOVES_LEGAL_H
#define CHESS_MOVES_LEGAL_H

bool move_fully_legal(const Piece board[], Info info, Move move);

bool move_pseudo_legal(const Piece board[], Info info, Move move);

bool board_move_legal(const Piece board[], Move move);

bool piece_legal_moves(Move** moveArray, const Piece board[], Info info, Point piecePoint);

bool piece_legal_points(Point** pointArray, const Piece board[], Info info, Point piecePoint);

bool team_legal_moves(Move** moveArray, const Piece board[], Info info, unsigned short team);

void append_promote_moves(Move* moveArray, short* moveAmount, Move promoteMove);

#endif
