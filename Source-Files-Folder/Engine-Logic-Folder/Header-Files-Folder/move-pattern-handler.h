
#ifndef MOVE_PATTERN_HANDLER_H
#define MOVE_PATTERN_HANDLER_H

bool move_pattern_valid(Move move, Piece piece);

bool pawn_pattern_handler(Move move, uint8_t team);

bool knight_pattern_handler(Move move, uint8_t team);

bool bishop_pattern_handler(Move move, uint8_t team);

bool queen_pattern_handler(Move move, uint8_t team);

bool king_pattern_handler(Move move, uint8_t team);

bool rook_pattern_handler(Move move, uint8_t team);

#endif
