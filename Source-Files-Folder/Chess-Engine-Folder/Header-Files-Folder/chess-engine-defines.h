
#ifndef CHESS_ENGINE_DEFINES_H
#define CHESS_ENGINE_DEFINES_H

// ==========================================

extern const Piece PIECE_TYPE_NONE;
extern const Piece PIECE_TYPE_PAWN;
extern const Piece PIECE_TYPE_KNIGHT;
extern const Piece PIECE_TYPE_BISHOP;
extern const Piece PIECE_TYPE_ROOK;
extern const Piece PIECE_TYPE_QUEEN;
extern const Piece PIECE_TYPE_KING;

extern const Piece PIECE_TEAM_NONE;
extern const Piece PIECE_TEAM_WHITE;
extern const Piece PIECE_TEAM_BLACK;

extern const Piece PIECE_TEAM_MASK;
extern const Piece PIECE_TYPE_MASK;

// ==========================================

extern const Point POINT_RANK_MASK;
extern const Point POINT_FILE_MASK;

// ==========================================

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

// ==========================================

extern const Info INFO_TEAM_MASK;
extern const Info INFO_PASSANT_MASK;
extern const Info INFO_CASTLES_MASK;
extern const Info INFO_TURNS_MASK;
extern const Info INFO_COUNTER_MASK;

extern const Info INFO_WHITE_KING;
extern const Info INFO_WHITE_QUEEN;
extern const Info INFO_BLACK_KING;
extern const Info INFO_BLACK_QUEEN;

extern const Info INFO_TEAM_NONE;
extern const Info INFO_TEAM_WHITE;
extern const Info INFO_TEAM_BLACK;

// ==========================================

extern const unsigned short PIECE_TEAM_SHIFT;
extern const unsigned short PIECE_TYPE_SHIFT;

extern const unsigned short POINT_RANK_SHIFT;
extern const unsigned short POINT_FILE_SHIFT;

extern const unsigned short INFO_TEAM_SHIFT;
extern const unsigned short INFO_PASSANT_SHIFT;
extern const unsigned short INFO_TURNS_SHIFT;
extern const unsigned short INFO_COUNTER_SHIFT;

extern const unsigned short MOVE_STOP_SHIFT;
extern const unsigned short MOVE_START_SHIFT;

// ==========================================

#define MOVE_STOP_MACRO(MOVE) 		(MOVE & MOVE_STOP_MASK) >> MOVE_STOP_SHIFT
#define MOVE_START_MACRO(MOVE) 		(MOVE & MOVE_START_MASK) >> MOVE_START_SHIFT

#define INFO_TEAM_MACRO(INFO) 		(INFO & INFO_TEAM_MASK) >> INFO_TEAM_SHIFT
#define INFO_PASSANT_MACRO(INFO) 	(INFO & INFO_PASSANT_MASK) >> INFO_PASSANT_SHIFT
#define INFO_TURNS_MACRO(INFO) 		(INFO & INFO_TURNS_MASK) >> INFO_TURNS_SHIFT
#define INFO_COUNTER_MACRO(INFO) 	(INFO & INFO_COUNTER_MASK) >> INFO_COUNTER_SHIFT

#define POINT_RANK_MACRO(POINT)		(POINT & POINT_RANK_MASK) >> POINT_RANK_SHIFT
#define POINT_FILE_MACRO(POINT)		(POINT & POINT_FILE_MASK) >> POINT_FILE_SHIFT

#define PIECE_TEAM_MACRO(PIECE)		(PIECE & PIECE_TEAM_MASK) >> PIECE_TEAM_SHIFT
#define PIECE_TYPE_MACRO(PIECE)		(PIECE & PIECE_TYPE_MASK) >> PIECE_TYPE_SHIFT

// ==========================================

extern const unsigned short BOARD_RANKS;
extern const unsigned short BOARD_FILES;
extern const unsigned short BOARD_LENGTH;

// ==========================================

extern const signed short INDEX_NONE;
extern const Point POINT_NONE;

extern const Piece PIECE_NONE;
extern const Move MOVE_NONE;
extern const Info INFO_NONE;

// ==========================================

extern const char WHITE_SYMBOLS[];
extern const char BLACK_SYMBOLS[];

extern const unsigned short SYMBOL_AMOUNT;

extern const char RANK_SYMBOLS[];
extern const char FILE_SYMBOLS[];

extern const char WHITE_SYMBOL;
extern const char BLACK_SYMBOL;

extern const char STRING_DELIM[];
extern const char RANK_DELIM[];

extern const char PASSANT_NONE[];
extern const char CASTLES_NONE[];

// ==========================================

extern const signed short PAWN_MOVE_DIRS[];
extern const signed short KNIGHT_MOVE_DIRS[];
extern const signed short BISHOP_MOVE_DIRS[];
extern const signed short ROOK_MOVE_DIRS[];
extern const signed short QUEEN_MOVE_DIRS[];
extern const signed short KING_MOVE_DIRS[];

extern const signed short CATSLE_MOVE_DIRS[];
extern const signed short PAWN_TAKE_DIRS[];
extern const signed short PAWN_DOUBLE_DIR;

// ==========================================

extern const unsigned short PAWN_DIRS_AMOUNT;
extern const unsigned short KNIGHT_DIRS_AMOUNT;
extern const unsigned short BISHOP_DIRS_AMOUNT;
extern const unsigned short ROOK_DIRS_AMOUNT;
extern const unsigned short QUEEN_DIRS_AMOUNT;
extern const unsigned short KING_DIRS_AMOUNT;

extern const unsigned short TAKE_DIRS_AMOUNT; // Pawn take (PAWN_TAKE_DIRS)
extern const unsigned short CASTLE_DIRS_AMOUNT;

// ==========================================

extern const signed short BLACK_MOVE_VALUE;
extern const signed short WHITE_MOVE_VALUE;

// ==========================================

extern const unsigned short WHITE_START_RANK; // This is the index rank, not the notation rank
extern const unsigned short BLACK_START_RANK; // This is the index rank, not the notation rank

extern const unsigned short WHITE_PAWN_RANK;
extern const unsigned short BLACK_PAWN_RANK;

// These values are set knowing that WHITE is at the bottom and BLACK is at the top of the board:

extern const unsigned short KING_START_FILE;

#endif