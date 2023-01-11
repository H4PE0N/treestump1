
#ifndef EXECUTE_CHESS_MOVES_H
#define EXECUTE_CHESS_MOVES_H

#define PAWN_PASSANT_POINT(MOVE) RANK_FILE_POINT(MOVE_START_RANK(move), MOVE_STOP_FILE(move))

bool execute_chess_move(Piece* board, Info* info, Move move);

bool execute_passant_move(Piece* board, Move move);

bool execute_castle_move(Piece* board, Move kingMove);

bool execute_promote_move(Piece* board, Move move);

Piece move_promote_piece(Move move);

Piece promote_piece_team(Move move);

Piece promote_piece_type(Move move);

bool reset_king_ability(Info* info, Piece kingPiece);

bool reset_rook_ability(Info* info, Piece rookPiece, Point rookPoint);

bool execute_board_move(Piece* board, Move move);

Point pawn_passant_point(Move move);

bool moved_reset_castle(Info* info, const Piece board[], Move move);

void update_info_values(Info* info, const Piece board[], Move move);

#endif
