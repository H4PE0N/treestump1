
#ifndef CHESS_GAME_ACTIONS_H
#define CHESS_GAME_ACTIONS_H

bool move_chess_piece(Piece*, Info*, Move);

bool piece_legal_moves(Move**, const Piece[], Info, Point);

#endif
