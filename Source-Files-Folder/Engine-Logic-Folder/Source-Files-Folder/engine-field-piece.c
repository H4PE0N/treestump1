
#include "../Header-Files-Folder/englog-include-file.h"

const Piece PIECE_TYPE_NONE = 0b00000;
const Piece PIECE_TYPE_PAWN = 0b00001;
const Piece PIECE_TYPE_KNIGHT = 0b00010;
const Piece PIECE_TYPE_BISHOP = 0b00011;
const Piece PIECE_TYPE_ROOK = 0b00100;
const Piece PIECE_TYPE_QUEEN = 0b00101;
const Piece PIECE_TYPE_KING = 0b00110;

const Piece PIECE_TEAM_NONE = 0b00000;
const Piece PIECE_TEAM_WHITE = 0b01000;
const Piece PIECE_TEAM_BLACK = 0b10000;

const Piece PIECE_TEAM_MASK = 0b11000;
const Piece PIECE_TYPE_MASK = 0b00111;

const unsigned short PIECE_TEAM_SHIFT = 3;
const unsigned short PIECE_TYPE_SHIFT = 0;

const Piece PIECE_NONE = 0;
const Piece PIECE_BLANK = 0b00000;
