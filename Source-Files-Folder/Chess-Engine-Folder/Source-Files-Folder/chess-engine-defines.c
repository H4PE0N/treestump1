
#include "../Header-Files-Folder/chess-engine-includer.h"

// ==========================================

const Piece PIECE_TYPE_NONE 	= 0b00000;
const Piece PIECE_TYPE_PAWN 	= 0b00001;
const Piece PIECE_TYPE_KNIGHT 	= 0b00010;
const Piece PIECE_TYPE_BISHOP 	= 0b00011;
const Piece PIECE_TYPE_ROOK 	= 0b00100;
const Piece PIECE_TYPE_QUEEN 	= 0b00101;
const Piece PIECE_TYPE_KING 	= 0b00110;

const Piece PIECE_TEAM_NONE 	= 0b00000;
const Piece PIECE_TEAM_WHITE 	= 0b01000;
const Piece PIECE_TEAM_BLACK 	= 0b10000;

const Piece PIECE_TEAM_MASK 	= 0b11000;
const Piece PIECE_TYPE_MASK 	= 0b00111;

// ==========================================

const Point POINT_RANK_MASK = 0b000111;
const Point POINT_FILE_MASK = 0b111000;

// ==========================================

// 000000 000000 0000 0000 00

const Info INFO_TEAM_MASK 		= 0b0000000000000000000011;
const Info INFO_CASTLES_MASK 	= 0b0000000000000000111100;
const Info INFO_PASSANT_MASK 	= 0b0000000000001111000000;
const Info INFO_COUNTER_MASK 	= 0b0000001111110000000000;
const Info INFO_TURNS_MASK 	 	= 0b1111110000000000000000;

const Info INFO_WHITE_KING 		= 0b0000000000000000100000;
const Info INFO_WHITE_QUEEN 	= 0b0000000000000000010000;
const Info INFO_BLACK_KING 		= 0b0000000000000000001000;
const Info INFO_BLACK_QUEEN 	= 0b0000000000000000000100;

const Info INFO_TEAM_NONE		= 0b0000000000000000000000;
const Info INFO_TEAM_WHITE		= 0b0000000000000000000001;
const Info INFO_TEAM_BLACK		= 0b0000000000000000000010;

// ==========================================

const unsigned int PIECE_TEAM_SHIFT = 3;
const unsigned int PIECE_TYPE_SHIFT = 0;

const unsigned int POINT_FILE_SHIFT = 3;
const unsigned int POINT_RANK_SHIFT = 0;

const unsigned int INFO_TEAM_SHIFT = 0;
const unsigned int INFO_PASSANT_SHIFT = 6;
const unsigned int INFO_COUNTER_SHIFT = 10;
const unsigned int INFO_TURNS_SHIFT   = 16;

// ==========================================

const unsigned int BOARD_RANKS = 8;
const unsigned int BOARD_FILES = 8;
const unsigned int BOARD_LENGTH = 64;

// ==========================================

const int INDEX_NONE = -1;