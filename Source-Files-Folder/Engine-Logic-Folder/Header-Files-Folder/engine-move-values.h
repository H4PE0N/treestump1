
#ifndef ENGINE_MOVE_VALUES_H
#define ENGINE_MOVE_VALUES_H

typedef int16_t Move;

extern const Move MOVE_FLAG_NONE;
extern const Move MOVE_FLAG_KNIGHT;
extern const Move MOVE_FLAG_BISHOP;
extern const Move MOVE_FLAG_ROOK;
extern const Move MOVE_FLAG_QUEEN;
extern const Move MOVE_FLAG_DOUBLE;
extern const Move MOVE_FLAG_CASTLE;
extern const Move MOVE_FLAG_PASSANT;

extern const Move MOVE_STOP_MASK;
extern const Move MOVE_START_MASK;
extern const Move MOVE_FLAG_MASK;

extern const uint8_t MOVE_STOP_SHIFT;
extern const uint8_t MOVE_START_SHIFT;

extern const Move MOVE_NONE;
extern const Move MOVE_BLANK;

#endif
