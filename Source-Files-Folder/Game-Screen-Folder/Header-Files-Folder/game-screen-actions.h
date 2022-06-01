
#ifndef GAME_SCREEN_ACTIONS_H
#define GAME_SCREEN_ACTIONS_H

bool input_promote_flag(Move*, Screen, unsigned short);

bool parse_promote_point(Move*, Point);

bool input_mark_parser(Point*, Screen, const Piece[], Info, Kings, const Move[], Event);

bool input_screen_move(Move*, Screen, const Piece[], Info, Kings, const Move[]);

bool input_move_parser(Move*, Screen, const Piece[], Info, Kings, const Move[], Event);

bool input_single_move(Move*, Screen, const Piece[], Info, Kings, const Move[]);

bool input_legal_move(Move*, Screen, const Piece[], Info, Kings, const Move[]);

bool mouse_event_check(Event, Uint8, Uint32);

#endif
