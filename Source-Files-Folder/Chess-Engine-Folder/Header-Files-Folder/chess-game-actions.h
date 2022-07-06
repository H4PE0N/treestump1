
#ifndef CHESS_GAME_ACTIONS_H
#define CHESS_GAME_ACTIONS_H

bool move_chess_piece(Piece*, Info*, Kings*, Move);

bool correct_move_flag(Move*, Piece, Info);

Move extract_pawn_flag(Move, Piece, Info);

Move extract_king_flag(Move, Piece, Info);

#endif
