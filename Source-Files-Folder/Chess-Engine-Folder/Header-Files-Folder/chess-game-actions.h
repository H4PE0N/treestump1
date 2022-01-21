
#ifndef CHESS_GAME_ACTIONS_H
#define CHESS_GAME_ACTIONS_H

bool move_chess_piece(Piece*, Info*, Kings*, Move*, Move);

bool piece_legal_moves(Move**, const Piece[], Info, Kings, Point);

bool correct_move_flag(Move*, Piece, Info);

#endif
