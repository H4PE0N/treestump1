
#ifndef SCREEN_INPUT_HANDLER_H
#define SCREEN_INPUT_HANDLER_H

bool input_promote_flag(Move* promoteFlag, Screen* screen, unsigned short team);

bool input_promote_flagX(Move* promoteFlag, Screen* screen, unsigned short team);

bool input_mark_parser(Point*, Screen, const Piece[], Info, const Move[], Event);

bool input_screen_move(Move*, Screen*, const Piece[], Info, const Move[]);

bool input_move_parser(Move*, Screen, const Piece[], Info, const Move[], Event);

bool input_single_move(Move*, Screen*, const Piece[], Info, const Move[]);

bool input_legal_move(Move*, Screen*, const Piece[], Info, const Move[]);

#endif
