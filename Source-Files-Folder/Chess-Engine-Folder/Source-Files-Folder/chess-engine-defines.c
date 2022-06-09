
#include "../Header-Files-Folder/engine-include-file.h"

const unsigned short BOARD_RANKS = 8;
const unsigned short BOARD_FILES = 8;
const unsigned short BOARD_LENGTH = 64;

const unsigned short PIECE_TYPE_SPAN = 7;
const unsigned short PIECE_TEAM_SPAN = 3;

const signed short BLACK_MOVE_VALUE = +1;
const signed short WHITE_MOVE_VALUE = -1;

const unsigned short WHITE_START_RANK = 7; // This is the index rank, not the notation rank
const unsigned short BLACK_START_RANK = 0; // This is the index rank, not the notation rank

const unsigned short WHITE_PAWN_RANK = 6;
const unsigned short BLACK_PAWN_RANK = 1;

const unsigned short KING_START_FILE = 4; // This is the index file, not the notation file

const signed short KING_CASTLE_PAT = +2;
const signed short QUEEN_CASTLE_PAT = -2;
