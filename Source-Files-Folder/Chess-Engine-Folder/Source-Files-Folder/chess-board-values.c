
#include "../Header-Files-Folder/engine-include-file.h"

const unsigned short BOARD_RANKS = 8;
const unsigned short BOARD_FILES = 8;
const unsigned short BOARD_LENGTH = 64;

const unsigned short PIECE_TYPE_SPAN = 7;
const unsigned short PIECE_TEAM_SPAN = 3;

const signed short BLACK_MOVE_VALUE = +1;
const signed short WHITE_MOVE_VALUE = -1;

const Point WHITE_KING_POINT = 0b111100;
const Point BLACK_KING_POINT = 0b000100;

const Point BROOK_QSIDE_POINT = 0b000000;
const Point BROOK_KSIDE_POINT = 0b000111;
const Point WROOK_QSIDE_POINT = 0b111000;
const Point WROOK_KSIDE_POINT = 0b111111;

const signed short KSIDE_FILE_OFFSET = +2;
const signed short QSIDE_FILE_OFFSET = -2;

const unsigned short WHITE_START_RANK = 0b111;
const unsigned short BLACK_START_RANK = 0b000;

const unsigned short WHITE_PAWN_RANK = 0b110;
const unsigned short BLACK_PAWN_RANK = 0b001;

const unsigned short KING_START_FILE = 0b100;
