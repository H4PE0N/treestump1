
#ifndef IDENT_BOARD_MOVES_H
#define IDENT_BOARD_MOVES_H

bool castle_move_ident(Info, Move, Piece);

bool passant_move_ident(Info, Move, Piece);

bool promote_move_ident(Info, Move, Piece);

bool double_move_ident(Info, Move, Piece);

#endif
