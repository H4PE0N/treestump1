
#include "../Header-Files-Folder/engine-include-file.h"

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

const Point POINT_RANK_MASK 	= 0b000111;
const Point POINT_FILE_MASK 	= 0b111000;

// ==========================================

const Move MOVE_FLAG_NONE		= 0b000000000000000;

const Move MOVE_FLAG_KNIGHT		= 0b001000000000000;
const Move MOVE_FLAG_BISHOP		= 0b010000000000000;
const Move MOVE_FLAG_ROOK		= 0b011000000000000;
const Move MOVE_FLAG_QUEEN		= 0b100000000000000;

const Move MOVE_FLAG_DOUBLE		= 0b101000000000000;
const Move MOVE_FLAG_CASTLE		= 0b110000000000000;
const Move MOVE_FLAG_PASSANT	= 0b111000000000000; // Capture En-Passant Pawn

const Move MOVE_STOP_MASK		= 0b000000000111111;
const Move MOVE_START_MASK		= 0b000111111000000;
const Move MOVE_FLAG_MASK		= 0b111000000000000;

// ==========================================

// 0000000 000000 0000 0000 00 (23 bits out of 32 - int)

const Info INFO_TEAM_MASK 		= 0b00000000000000000000011;
const Info INFO_CASTLES_MASK 	= 0b00000000000000000111100;
const Info INFO_PASSANT_MASK 	= 0b00000000000001111000000;
const Info INFO_COUNTER_MASK 	= 0b00000001111110000000000;
const Info INFO_TURNS_MASK 	 	= 0b11111110000000000000000;

const Info INFO_WHITE_KING 		= 0b00000000000000000100000;
const Info INFO_WHITE_QUEEN 	= 0b00000000000000000010000;
const Info INFO_BLACK_KING 		= 0b00000000000000000001000;
const Info INFO_BLACK_QUEEN 	= 0b00000000000000000000100;

const Info INFO_TEAM_NONE		= 0b00000000000000000000000;
const Info INFO_TEAM_WHITE		= 0b00000000000000000000001;
const Info INFO_TEAM_BLACK		= 0b00000000000000000000010;

// ==========================================

const unsigned short PIECE_TEAM_SHIFT 	= 3;
const unsigned short PIECE_TYPE_SHIFT 	= 0;

const unsigned short POINT_FILE_SHIFT 	= 3;
const unsigned short POINT_RANK_SHIFT 	= 0;

const unsigned short INFO_TEAM_SHIFT 	= 0;
const unsigned short INFO_PASSANT_SHIFT = 6;
const unsigned short INFO_COUNTER_SHIFT = 10;
const unsigned short INFO_TURNS_SHIFT   = 16;

const unsigned short MOVE_STOP_SHIFT	= 0;
const unsigned short MOVE_START_SHIFT	= 6;

// ==========================================

const unsigned short BOARD_RANKS 	= 8;
const unsigned short BOARD_FILES 	= 8;
const unsigned short BOARD_LENGTH 	= 64;

// ==========================================

const signed short INDEX_NONE 	= -1;
const Point POINT_NONE 			= -1;

const Piece PIECE_NONE 			= 0b00000;
const Move MOVE_NONE 			= 0b000000000000000;
const Info INFO_NONE 			= 0b00000000000000000000000;

// ==========================================

const char WHITE_SYMBOLS[] = {'X', 'P', 'N', 'B', 'R', 'Q', 'K'};
const char BLACK_SYMBOLS[] = {'x', 'p', 'n', 'b', 'r', 'q', 'k'};

const unsigned short TEAM_AMOUNT = 7;

const char RANK_SYMBOLS[] = {'8', '7', '6', '5', '4', '3', '2', '1'};
const char FILE_SYMBOLS[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};

const char WHITE_SYMBOL = 'w';
const char BLACK_SYMBOL = 'b';

const char STRING_DELIM[] = " ";
const char RANK_DELIM[] = "/";

const char PASSANT_NONE[] = "-";
const char CASTLES_NONE[] = "-";

// ==========================================

// These values must be inverted using the WHITE / BLACK - MOVE_VALUE:

const signed short PAWN_MOVE_DIRS[]		= {+7, +8, +9, +16}; // pawn takes + double jump
const signed short KNIGHT_MOVE_DIRS[]	= {-17, -15, -10, -6, +6, +10, +15, +17};
const signed short BISHOP_MOVE_DIRS[]	= {-9, -7, +7, +9};
const signed short ROOK_MOVE_DIRS[]		= {-8, -1, +1, +8};
const signed short QUEEN_MOVE_DIRS[]	= {-9, -8, -7, -1, +1, +7, +8, +9};
const signed short KING_MOVE_DIRS[]		= {-9, -8, -7, -2, -1, +1, +2, +7, +8, +9}; // castling

const signed short CATSLE_MOVE_DIRS[]	= {-2, +2};
const signed short PAWN_TAKE_DIRS[]		= {+7, +9};
const signed short PAWN_DOUBLE_DIR		= +16;

// ==========================================

const unsigned short PAWN_DIRS_AMOUNT 	= sizeof(PAWN_MOVE_DIRS) / sizeof(PAWN_MOVE_DIRS[0]);
const unsigned short KNIGHT_DIRS_AMOUNT = sizeof(KNIGHT_MOVE_DIRS) / sizeof(KNIGHT_MOVE_DIRS[0]);
const unsigned short BISHOP_DIRS_AMOUNT = sizeof(BISHOP_MOVE_DIRS) / sizeof(BISHOP_MOVE_DIRS[0]);
const unsigned short ROOK_DIRS_AMOUNT 	= sizeof(ROOK_MOVE_DIRS) / sizeof(ROOK_MOVE_DIRS[0]);
const unsigned short QUEEN_DIRS_AMOUNT 	= sizeof(QUEEN_MOVE_DIRS) / sizeof(QUEEN_MOVE_DIRS[0]);
const unsigned short KING_DIRS_AMOUNT 	= sizeof(KING_MOVE_DIRS) / sizeof(KING_MOVE_DIRS[0]);

const unsigned short TAKE_DIRS_AMOUNT	= sizeof(PAWN_TAKE_DIRS) / sizeof(PAWN_TAKE_DIRS[0]);
const unsigned short CASTLE_DIRS_AMOUNT	= sizeof(CATSLE_MOVE_DIRS) / sizeof(CATSLE_MOVE_DIRS[0]);

// ==========================================

const signed short BLACK_MOVE_VALUE 	= 1;
const signed short WHITE_MOVE_VALUE 	= -1;

// ==========================================

const unsigned short WHITE_START_RANK	= 7; // This is the index rank, not the notation rank
const unsigned short BLACK_START_RANK	= 0; // This is the index rank, not the notation rank

const unsigned short WHITE_PAWN_RANK	= 6;
const unsigned short BLACK_PAWN_RANK	= 1;

// These values are set knowing that WHITE is at the bottom and BLACK is at the top of the board:

const unsigned short KING_START_FILE	= 4; // This is the index file, not the notation file