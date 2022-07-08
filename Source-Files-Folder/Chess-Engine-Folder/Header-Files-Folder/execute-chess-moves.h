
#ifndef EXECUTE_CHESS_MOVES_H
#define EXECUTE_CHESS_MOVES_H

bool execute_chess_move(Piece*, Info*, Move);

bool execute_passant_move(Piece*, Info*, Move);

bool execute_castle_move(Piece*, Info*, Move);

bool execute_double_move(Piece*, Info*, Move);

bool execute_promote_move(Piece*, Info*, Move);

bool execute_normal_move(Piece*, Info*, Move);

Piece move_promote_piece(Move, unsigned short);

Piece promote_piece_type(Move);

#endif
