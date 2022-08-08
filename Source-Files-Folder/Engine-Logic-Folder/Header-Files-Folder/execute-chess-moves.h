
#ifndef EXECUTE_CHESS_MOVES_H
#define EXECUTE_CHESS_MOVES_H

bool execute_chess_move(Piece*, Info*, Move);

bool execute_passant_move(Piece*, Info*, Move);

bool execute_castle_move(Piece*, Info*, Move);

bool execute_double_move(Piece*, Info*, Move);

bool execute_promote_move(Piece*, Info*, Move);

bool execute_normal_move(Piece*, Info*, Move);

Piece move_promote_piece(Move);

Piece promote_piece_type(Move);

bool reset_king_ability(Info*, Piece);

bool reset_rook_ability(Info*, Piece, Point);

bool execute_board_move(Piece*, Move);

bool execute_start_stop(Piece*, Point, Point);

Point pawn_passant_point(Move);

bool moved_reset_castle(Info*, const Piece[], Move);

#endif
