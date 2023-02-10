
#ifndef ENGINE_STATE_VALUES_H
#define ENGINE_STATE_VALUES_H

typedef uint32_t State;

extern const State STATE_TEAM_MASK;
extern const State STATE_PASSANT_MASK;
extern const State STATE_CASTLES_MASK;
extern const State STATE_TURNS_MASK;
extern const State STATE_COUNTER_MASK;

extern const State STATE_WHITE_KSIDE;
extern const State STATE_WHITE_QSIDE;
extern const State STATE_BLACK_KSIDE;
extern const State STATE_BLACK_QSIDE;

extern const State STATE_TEAM_NONE;
extern const State STATE_TEAM_WHITE;
extern const State STATE_TEAM_BLACK;

extern const uint8_t STATE_TEAM_SHIFT;
extern const uint8_t STATE_PASSANT_SHIFT;
extern const uint8_t STATE_TURNS_SHIFT;
extern const uint8_t STATE_COUNTER_SHIFT;

extern const State STATE_NONE;
extern const State STATE_BLANK;

#endif
