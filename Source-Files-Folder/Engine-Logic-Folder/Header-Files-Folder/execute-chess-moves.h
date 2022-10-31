
#ifndef EXECUTE_CHESS_MOVES_H
#define EXECUTE_CHESS_MOVES_H

bool execute_chess_move(Piece* board, Info* info, Move move);

bool execute_passant_move(Piece* board, Info* info, Move move);

bool execute_castle_move(Piece* board, Info* info, Move kingMove);

bool execute_double_move(Piece* board, Info* info, Move move);

bool execute_promote_move(Piece* board, Info* info, Move move);

bool execute_normal_move(Piece* board, Info* info, Move move);

Piece move_promote_piece(Move move);

Piece promote_piece_team(Move move);

Piece promote_piece_type(Move move);

bool reset_king_ability(Info* info, Piece kingPiece);

bool reset_rook_ability(Info* info, Piece rookPiece, Point rookPoint);

bool execute_board_move(Piece* board, Move move);

bool execute_start_stop(Piece* board, Point startPoint, Point stopPoint);

Point pawn_passant_point(Move move);

bool moved_reset_castle(Info* info, const Piece board[], Move move);

#endif
