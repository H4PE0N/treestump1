
#ifndef SCREEN_INPUT_PARSER_H
#define SCREEN_INPUT_PARSER_H

bool mouse_event_check(Event, Uint8, Uint32);

bool board_point_position(Rect*, Screen, Point);

Point parse_mouse_point(Event, Screen);

bool parse_quit_input(Event);

bool parse_promote_point(Move*, Point);

bool key_event_check(Event event, int keyCode, Uint32 keyMove);

#endif
