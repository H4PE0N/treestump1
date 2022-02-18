
#ifndef CHESS_ENGINE_STRUCTS_H
#define CHESS_ENGINE_STRUCTS_H

typedef unsigned short Piece; // 00 000

typedef signed short Point; // 000 000

typedef unsigned int Info; // 0000000 000000 0000 0000 00

typedef signed short Move; // 000 000000 000000

typedef unsigned short Kings; // 000000 000000


extern const unsigned short TEAM_NONE;
extern const unsigned short TEAM_WHITE;
extern const unsigned short TEAM_BLACK;


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


extern const Point POINT_RANK_MASK;
extern const Point POINT_FILE_MASK;


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


extern const Kings KINGS_WHITE_MASK;
extern const Kings KINGS_BLACK_MASK;


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

extern const unsigned short KINGS_WHITE_SHIFT;
extern const unsigned short KINGS_BLACK_SHIFT;


extern const Point POINT_NONE;
extern const Piece PIECE_NONE;
extern const Move MOVE_NONE;
extern const Info INFO_NONE;
extern const Kings KINGS_NONE;


extern const Point POINT_BLANK;
extern const Piece PIECE_BLANK;
extern const Move MOVE_BLANK;
extern const Info INFO_BLANK;
extern const Kings KINGS_BLANK;


extern const signed short SHORT_NONE;
extern const signed short INDEX_NONE;

#endif
