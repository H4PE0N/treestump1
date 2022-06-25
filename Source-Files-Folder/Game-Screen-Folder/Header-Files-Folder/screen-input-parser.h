
#ifndef SCREEN_INPUT_PARSER_H
#define SCREEN_INPUT_PARSER_H

bool mouse_event_check(Event, Uint8, Uint32);

bool board_point_position(Rect*, Screen, Point, bool);

Point parse_mouse_point(Event, Screen, bool);

bool parse_quit_input(Event);

bool parse_promote_point(Move*, Point);

#endif
