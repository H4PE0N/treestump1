
#ifndef IDENT_BOARD_MOVES_H
#define IDENT_BOARD_MOVES_H

bool castle_move_ident(State state, Move move, Piece piece);

bool passant_move_ident(State state, Move move, Piece piece);

bool promote_move_ident(State state, Move move, Piece piece);

bool double_move_ident(State state, Move move, Piece piece);

#endif
