
#ifndef CHESS_GAME_LOGIC_H
#define CHESS_GAME_LOGIC_H

bool piece_does_check(const Piece board[], Point kingPoint, Point point);

bool king_inside_check(const Piece board[], Point kingPoint);

bool team_pieces_movable(const Piece board[], State state, uint8_t team);

bool chess_piece_movable(const Piece board[], State state, Point piecePoint);

bool piece_movable_test(const Piece board[], State state, const Move moveArray[], int moveAmount);

bool check_draw_ending(const Piece board[], State state, uint8_t team);

bool check_mate_ending(const Piece board[], State state, uint8_t team);

bool little_material_draw(const Piece board[]);

bool game_still_running(const Piece board[], State state);

bool move_deliver_mate(const Piece[], State, Move);

bool move_deliver_check(const Piece board[], State state, Move move);

bool move_deliver_mate(const Piece board[], State state, Move move);

bool deliver_check_test(Piece* boardCopy, State stateCopy, Move move);

bool deliver_mate_test(Piece* boardCopy, State stateCopy, Move move);

#endif
