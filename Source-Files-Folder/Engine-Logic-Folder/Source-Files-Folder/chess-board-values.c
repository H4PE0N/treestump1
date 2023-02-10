
#include "../Header-Files-Folder/englog-include-file.h"

const uint8_t BOARD_RANKS = 8;
const uint8_t BOARD_FILES = 8;
const uint8_t BOARD_POINTS = 64;

const uint8_t PIECE_TYPE_SPAN = 7;
const uint8_t PIECE_TEAM_SPAN = 3;

const int8_t BLACK_MOVE_VALUE = +1;
const int8_t WHITE_MOVE_VALUE = -1;

const Point WHITE_KING_POINT = 0b111100;
const Point BLACK_KING_POINT = 0b000100;

const Point BROOK_QSIDE_POINT = 0b000000;
const Point BROOK_KSIDE_POINT = 0b000111;
const Point WROOK_QSIDE_POINT = 0b111000;
const Point WROOK_KSIDE_POINT = 0b111111;

const int8_t KSIDE_FILE_OFFSET = +2;
const int8_t QSIDE_FILE_OFFSET = -2;

const uint8_t WHITE_START_RANK = 0b111;
const uint8_t BLACK_START_RANK = 0b000;

const uint8_t WHITE_PAWN_RANK = 0b110;
const uint8_t BLACK_PAWN_RANK = 0b001;

const uint8_t KING_START_FILE = 0b100;
