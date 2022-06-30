
#ifndef CHESS_GAME_LOGIC_H
#define CHESS_GAME_LOGIC_H

bool piece_does_check(const Piece[], Info, Point, Point);

bool king_inside_check(const Piece[], Info, Point);

bool team_pieces_movable(const Piece[], Info, Kings, unsigned short);

bool chess_piece_movable(const Piece[], Info, Kings, Point);

bool piece_movable_test(const Piece[], Info, Kings, const Move[], Piece);

bool check_draw_ending(const Piece[], Info, Kings, unsigned short);

bool check_mate_ending(const Piece[], Info, Kings, unsigned short);

bool game_still_running(const Piece[], Info, Kings);

bool move_deliver_mate(const Piece[], Info, Kings, Move);

bool move_deliver_check(const Piece[], Info, Kings, Move);

bool deliver_mate_test(Piece*, Info, Kings, Move);

bool deliver_check_test(Piece*, Info, Kings, Move);

#endif
