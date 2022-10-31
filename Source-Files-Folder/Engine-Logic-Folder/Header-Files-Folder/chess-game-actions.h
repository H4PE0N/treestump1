
#ifndef CHESS_GAME_ACTIONS_H
#define CHESS_GAME_ACTIONS_H

bool move_chess_piece(Piece* board, Info* info, Move move);

bool correct_move_flag(Move* move, const Piece board[], Info info);

Move extract_pawn_flag(Move move, Piece piece, Info info);

Move extract_king_flag(Move move, Piece piece, Info info);

#endif
