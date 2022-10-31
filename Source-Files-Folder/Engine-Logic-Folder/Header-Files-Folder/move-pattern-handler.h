
#ifndef MOVE_PATTERN_HANDLER_H
#define MOVE_PATTERN_HANDLER_H

bool move_pattern_valid(Move move, Piece piece);

bool pawn_pattern_handler(Move move, unsigned short team);

bool knight_pattern_handler(Move move, unsigned short team);

bool bishop_pattern_handler(Move move, unsigned short team);

bool queen_pattern_handler(Move move, unsigned short team);

bool king_pattern_handler(Move move, unsigned short team);

bool rook_pattern_handler(Move move, unsigned short team);

#endif
