
#ifndef CHESS_GAME_LOGIC_H
#define CHESS_GAME_LOGIC_H

bool piece_does_check(const Piece[], Info, Point, Point);

bool king_inside_check(const Piece[], Info, Point);

bool team_prevent_check(const Piece[], Info, Piece);

bool team_pieces_movable(const Piece[], Info, Piece);

bool check_draw_ending(const Piece[], Info, Point);

bool check_mate_ending(const Piece[], Info, Point);

bool game_still_running(const Piece[], Info, Kings);

#endif
