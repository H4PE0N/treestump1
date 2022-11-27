
#ifndef CHESS_GAME_LOGIC_H
#define CHESS_GAME_LOGIC_H

bool piece_does_check(const Piece board[], Point kingPoint, Point point);

bool king_inside_check(const Piece board[], Point kingPoint);

bool team_pieces_movable(const Piece board[], Info info, unsigned short team);

bool chess_piece_movable(const Piece board[], Info info, Point piecePoint);

bool piece_movable_test(const Piece board[], Info info, const Move moveArray[], short moveAmount);

bool check_draw_ending(const Piece board[], Info info, unsigned short team);

bool check_mate_ending(const Piece board[], Info info, unsigned short team);

bool game_still_running(const Piece board[], Info info);

bool move_deliver_mate(const Piece[], Info, Move);

bool move_deliver_check(const Piece board[], Info info, Move move);

bool move_deliver_mate(const Piece board[], Info info, Move move);

bool deliver_check_test(Piece* boardCopy, Info infoCopy, Move move);

bool deliver_mate_test(Piece* boardCopy, Info infoCopy, Move move);

#endif
