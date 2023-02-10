
#include "../Header-Files-Folder/englog-include-file.h"

const State STATE_TEAM_MASK = 0b000000000000000000000011;
const State STATE_CASTLES_MASK = 0b000000000000000000111100;
const State STATE_PASSANT_MASK = 0b000000000000001111000000;
const State STATE_COUNTER_MASK = 0b000000011111110000000000;
const State STATE_TURNS_MASK = 0b111111100000000000000000;

const State STATE_WHITE_KSIDE = 0b000000000000000000100000;
const State STATE_WHITE_QSIDE = 0b000000000000000000010000;
const State STATE_BLACK_KSIDE = 0b000000000000000000001000;
const State STATE_BLACK_QSIDE = 0b000000000000000000000100;

const State STATE_TEAM_NONE = 0b000000000000000000000000;
const State STATE_TEAM_WHITE = 0b000000000000000000000001;
const State STATE_TEAM_BLACK = 0b000000000000000000000010;

const uint8_t STATE_TEAM_SHIFT = 0;
const uint8_t STATE_PASSANT_SHIFT = 6;
const uint8_t STATE_COUNTER_SHIFT = 10;
const uint8_t STATE_TURNS_SHIFT = 17;

const State STATE_NONE = 0;
const State STATE_BLANK = 0b000000000000000000000000;
