
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

#endif