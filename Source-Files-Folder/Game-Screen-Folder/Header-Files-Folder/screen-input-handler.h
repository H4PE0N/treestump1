
#ifndef SCREEN_INPUT_HANDLER_H
#define SCREEN_INPUT_HANDLER_H

bool input_promote_flag(Move*, Screen, unsigned short);

bool input_mark_parser(Point*, Screen, const Piece[], Info, const Move[], Event, bool);

bool input_screen_move(Move*, Screen, const Piece[], Info, const Move[], bool*);

bool input_move_parser(Move*, Screen, const Piece[], Info, const Move[], Event, bool);

bool input_single_move(Move*, Screen, const Piece[], Info, const Move[], bool*);

bool input_legal_move(Move*, Screen, const Piece[], Info, const Move[], bool*);

#endif
