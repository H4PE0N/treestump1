
#ifndef ENGINE_FIELD_MOVE_H
#define ENGINE_FIELD_MOVE_H

typedef signed short Move;

#define MOVE_STOP_MACRO(MOVE) ( (MOVE & MOVE_STOP_MASK) >> MOVE_STOP_SHIFT)
#define MOVE_START_MACRO(MOVE) ( (MOVE & MOVE_START_MASK) >> MOVE_START_SHIFT)

#define STOP_MOVE_MACRO(STOP) ( (STOP << MOVE_STOP_SHIFT) & MOVE_STOP_MASK)
#define START_MOVE_MACRO(START) ( (START << MOVE_START_SHIFT) & MOVE_START_MASK)

#define ALLOC_MOVE_FLAG(MOVE, FLAG) ( (MOVE & ~MOVE_FLAG_MASK) | (FLAG & MOVE_FLAG_MASK) )
#define ALLOC_MOVE_STOP(MOVE, STOP) ( (MOVE & ~MOVE_STOP_MASK) | (STOP & MOVE_STOP_MASK) )
#define ALLOC_MOVE_START(MOVE, START) ( (MOVE & ~MOVE_START_MASK) | (START & MOVE_START_MASK) )

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

extern const unsigned short MOVE_STOP_SHIFT;
extern const unsigned short MOVE_START_SHIFT;

extern const Move MOVE_NONE;
extern const Move MOVE_BLANK;

#endif
