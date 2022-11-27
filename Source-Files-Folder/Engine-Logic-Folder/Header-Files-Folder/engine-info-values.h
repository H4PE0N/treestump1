
#ifndef ENGINE_INFO_VALUES_H
#define ENGINE_INFO_VALUES_H

typedef unsigned int Info;

extern const Info INFO_TEAM_MASK;
extern const Info INFO_PASSANT_MASK;
extern const Info INFO_CASTLES_MASK;
extern const Info INFO_TURNS_MASK;
extern const Info INFO_COUNTER_MASK;

extern const Info INFO_WHITE_KSIDE;
extern const Info INFO_WHITE_QSIDE;
extern const Info INFO_BLACK_KSIDE;
extern const Info INFO_BLACK_QSIDE;

extern const Info INFO_TEAM_NONE;
extern const Info INFO_TEAM_WHITE;
extern const Info INFO_TEAM_BLACK;

extern const unsigned short INFO_TEAM_SHIFT;
extern const unsigned short INFO_PASSANT_SHIFT;
extern const unsigned short INFO_TURNS_SHIFT;
extern const unsigned short INFO_COUNTER_SHIFT;

extern const Info INFO_NONE;
extern const Info INFO_BLANK;

#endif