
#ifndef CHESS_GAME_ACTIONS_H
#define CHESS_GAME_ACTIONS_H

bool move_chess_piece(Piece*, Info*, Kings*, Move);

bool piece_legal_moves(Move**, const Piece[], Info, Kings, Point);

bool correct_move_flag(Move*, Piece, Info);

bool castle_move_ident(Info, Move, Piece);

bool passant_move_ident(Info, Move, Piece);

bool promote_move_ident(Info, Move, Piece);

bool double_move_ident(Info, Move, Piece);

bool best_computer_move(Move*, const Piece[], Info, Kings, unsigned short, signed short);

unsigned short board_depth_value(const Piece[], Info, Kings, signed short, signed short, signed short, unsigned short, unsigned short);

signed short team_state_value(const Piece[], Info, Kings, unsigned short);

#endif
