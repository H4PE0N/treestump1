
#ifndef SCREEN_PROGRAM_H
#define SCREEN_PROGRAM_H

#include "../../Chess-Engine-Folder/Header-Files-Folder/engine-include-file.h"
#include "../../Game-Screen-Folder/Header-Files-Folder/screen-includer.h"

bool screen_user_handler(Piece*, Info*, Kings*, Screen);

bool input_screen_move(Move*, Screen, const Piece[], Info, Kings);

bool screen_move_parser(Move*, Screen, const Piece[], Info, Kings, Event);

Point parse_mouse_point(Event, Screen);

bool screen_single_game(Piece*, Info*, Kings*, Screen);

#endif
