
#ifndef MOVE_PATTERN_HANDLER_H
#define MOVE_PATTERN_HANDLER_H

bool move_pattern_valid(Move, Piece);

bool pawn_pattern_handler(Move, unsigned short);

bool knight_pattern_handler(Move, unsigned short);

bool bishop_pattern_handler(Move, unsigned short);

bool queen_pattern_handler(Move, unsigned short);

bool king_pattern_handler(Move, unsigned short);

bool rook_pattern_handler(Move, unsigned short);

#endif
