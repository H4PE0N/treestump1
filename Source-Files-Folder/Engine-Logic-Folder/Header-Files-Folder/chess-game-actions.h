
#ifndef CHESS_GAME_ACTIONS_H
#define CHESS_GAME_ACTIONS_H

bool move_chess_piece(Piece* board, State* state, Move move);

bool correct_move_flag(Move* move, const Piece board[], State state);

Move extract_pawn_flag(Move move, Piece piece, State state);

Move extract_king_flag(Move move, Piece piece, State state);

#endif
