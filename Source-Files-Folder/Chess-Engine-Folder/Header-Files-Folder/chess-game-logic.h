
#ifndef CHESS_GAME_LOGIC_H
#define CHESS_GAME_LOGIC_H

bool piece_does_check(const Piece[], Info, Point, Point);

bool king_inside_check(const Piece[], Info, Point);

bool team_pieces_movable(const Piece[], Info, Kings, Piece);

bool chess_piece_movable(const Piece[], Info, Kings, Point);

bool check_draw_ending(const Piece[], Info, Kings, Piece);

bool check_mate_ending(const Piece[], Info, Kings, Piece);

bool game_still_running(const Piece[], Info, Kings);

#endif
