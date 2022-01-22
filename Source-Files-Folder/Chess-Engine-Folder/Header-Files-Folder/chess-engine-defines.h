
#ifndef CHESS_ENGINE_DEFINES_H
#define CHESS_ENGINE_DEFINES_H

extern const unsigned short TEAM_NONE;
extern const unsigned short TEAM_WHITE;
extern const unsigned short TEAM_BLACK;

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

extern const Kings KINGS_WHITE_MASK;
extern const Kings KINGS_BLACK_MASK;

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

extern const unsigned short KINGS_WHITE_SHIFT;
extern const unsigned short KINGS_BLACK_SHIFT;

// ==========================================

#define MOVE_STOP_MACRO(MOVE)             ( (MOVE & MOVE_STOP_MASK) >> MOVE_STOP_SHIFT)
#define MOVE_START_MACRO(MOVE)            ( (MOVE & MOVE_START_MASK) >> MOVE_START_SHIFT)

#define INFO_TEAM_MACRO(INFO)             ( (INFO & INFO_TEAM_MASK) >> INFO_TEAM_SHIFT)
#define INFO_PASSANT_MACRO(INFO)          ( (INFO & INFO_PASSANT_MASK) >> INFO_PASSANT_SHIFT)
#define INFO_TURNS_MACRO(INFO)            ( (INFO & INFO_TURNS_MASK) >> INFO_TURNS_SHIFT)
#define INFO_COUNTER_MACRO(INFO)          ( (INFO & INFO_COUNTER_MASK) >> INFO_COUNTER_SHIFT)

#define POINT_RANK_MACRO(POINT)           ( (POINT & POINT_RANK_MASK) >> POINT_RANK_SHIFT)
#define POINT_FILE_MACRO(POINT)           ( (POINT & POINT_FILE_MASK) >> POINT_FILE_SHIFT)

#define PIECE_TEAM_MACRO(PIECE)           ( (PIECE & PIECE_TEAM_MASK) >> PIECE_TEAM_SHIFT)
#define PIECE_TYPE_MACRO(PIECE)           ( (PIECE & PIECE_TYPE_MASK) >> PIECE_TYPE_SHIFT)

#define KINGS_WHITE_MACRO(KINGS)          ( (KINGS & KINGS_WHITE_MASK) >> KINGS_WHITE_SHIFT)
#define KINGS_BLACK_MACRO(KINGS)          ( (KINGS & KINGS_BLACK_MASK) >> KINGS_BLACK_SHIFT)

// ==========================================

#define STOP_MOVE_MACRO(STOP)             ( (STOP << MOVE_STOP_SHIFT) & MOVE_STOP_MASK)
#define START_MOVE_MACRO(START)           ( (START << MOVE_START_SHIFT) & MOVE_START_MASK)

#define TEAM_INFO_MACRO(TEAM)             ( (TEAM << INFO_TEAM_SHIFT) & INFO_TEAM_MASK)
#define PASSANT_INFO_MACRO(PASSANT)       ( (PASSANT << INFO_PASSANT_SHIFT) & INFO_PASSANT_MASK)
#define TURNS_INFO_MACRO(TURNS)           ( (TURNS << INFO_TURNS_SHIFT) & INFO_TURNS_MASK)
#define COUNTER_INFO_MACRO(COUNTER)       ( (COUNTER << INFO_COUNTER_SHIFT) & INFO_COUNTER_MASK)

#define RANK_POINT_MACRO(RANK)            ( (RANK << POINT_RANK_SHIFT) & POINT_RANK_MASK)
#define FILE_POINT_MACRO(FILE)            ( (FILE << POINT_FILE_SHIFT) & POINT_FILE_MASK)

#define TEAM_PIECE_MACRO(TEAM)            ( (TEAM << PIECE_TEAM_SHIFT) & PIECE_TEAM_MASK)
#define TYPE_PIECE_MACRO(TYPE)            ( (TYPE << PIECE_TYPE_SHIFT) & PIECE_TYPE_MASK)

#define WHITE_KINGS_MACRO(WHITE)          ( (WHITE << KINGS_WHITE_SHIFT) & KINGS_WHITE_MASK)
#define BLACK_KINGS_MACRO(BLACK)          ( (BLACK << KINGS_BLACK_SHIFT) & KINGS_BLACK_MASK)

// ==========================================

#define ALLOC_MOVE_FLAG(MOVE, FLAG)       ( (MOVE & ~MOVE_FLAG_MASK) | (FLAG & MOVE_FLAG_MASK) )
#define ALLOC_MOVE_STOP(MOVE, STOP)       ( (MOVE & ~MOVE_STOP_MASK) | (STOP & MOVE_STOP_MASK) )
#define ALLOC_MOVE_START(MOVE, START)     ( (MOVE & ~MOVE_START_MASK) | (START & MOVE_START_MASK) )

#define ALLOC_INFO_TEAM(INFO, TEAM)       ( (INFO & ~INFO_TEAM_MASK) | (TEAM & INFO_TEAM_MASK) )
#define ALLOC_INFO_PASSANT(INFO, PASSANT) ( (INFO & ~INFO_PASSANT_MASK) | (PASSANT & INFO_PASSANT_MASK) )
#define ALLOC_INFO_TURNS(INFO, TURNS)     ( (INFO & ~INFO_TURNS_MASK) | (TURNS & INFO_TURNS_MASK) )
#define ALLOC_INFO_COUNTER(INFO, COUNTER) ( (INFO & ~INFO_COUNTER_MASK) | (COUNTER & INFO_COUNTER_MASK) )
#define ALLOC_INFO_CASTLES(INFO, CASTLES) ( (INFO & ~INFO_CASTLES_MASK) | (CASTLES & INFO_CASTLES_MASK) )

#define ALLOC_POINT_RANK(POINT, RANK)     ( (POINT & ~POINT_RANK_MASK) | (RANK & POINT_RANK_MASK) )
#define ALLOC_POINT_FILE(POINT, FILE)     ( (POINT & ~POINT_FILE_MASK) | (FILE & POINT_FILE_MASK) )

#define ALLOC_PIECE_TEAM(PIECE, TEAM)     ( (PIECE & ~PIECE_TEAM_MASK) | (TEAM & PIECE_TEAM_MASK) )
#define ALLOC_PIECE_TYPE(PIECE, TYPE)     ( (PIECE & ~PIECE_TYPE_MASK) | (TYPE & PIECE_TYPE_MASK) )

#define ALLOC_KINGS_WHITE(KINGS, WHITE)   ( (KINGS & ~KINGS_WHITE_MASK) | (WHITE & KINGS_WHITE_MASK) )
#define ALLOC_KINGS_BLACK(KINGS, BLACK)   ( (KINGS & ~KINGS_BLACK_MASK) | (BLACK & KINGS_BLACK_MASK) )

// This will set whites king-side-castle to false:
// INFO = INFO & ~INFO_WHITE_KING
// INFO &= ~INFO_WHITE_KING

// This will set whites king-side-castle to true:
// INFO = INFO | INFO_WHITE_KING
// INFO |= INFO_WHITE_KING

// ==========================================

extern const unsigned short BOARD_RANKS;
extern const unsigned short BOARD_FILES;
extern const unsigned short BOARD_LENGTH;

// ==========================================

extern const Point POINT_NONE;
extern const Piece PIECE_NONE;
extern const Move MOVE_NONE;
extern const Info INFO_NONE;
extern const Kings KINGS_NONE;

extern const signed short SHORT_NONE;
extern const signed short INDEX_NONE;

extern const Point POINT_BLANK;
extern const Piece PIECE_BLANK;
extern const Move MOVE_BLANK;
extern const Info INFO_BLANK;
extern const Kings KINGS_BLANK;

extern const signed short MIN_BOARD_VALUE;
extern const signed short MAX_BOARD_VALUE;

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

extern const signed short BLACK_MOVE_VALUE;
extern const signed short WHITE_MOVE_VALUE;

// ==========================================

extern const unsigned short WHITE_START_RANK; // This is the index rank, not the notation rank
extern const unsigned short BLACK_START_RANK; // This is the index rank, not the notation rank

extern const unsigned short WHITE_PAWN_RANK;
extern const unsigned short BLACK_PAWN_RANK;

// These values are set knowing that WHITE is at the bottom and BLACK is at the top of the board:

extern const unsigned short KING_START_FILE;

extern const signed short KING_CASTLE_PAT;
extern const signed short QUEEN_CASTLE_PAT;

extern const unsigned short SHORT_ABS;

// ==========================================

#define NUMBER_IN_BOUNDS(NUMBER, MINIMUM, MAXIMUM) (NUMBER >= MINIMUM && NUMBER <= MAXIMUM)

#define ABS_SHORT_NUMBER(NUMBER) (((NUMBER) >> SHORT_ABS) ^ (NUMBER)) - ((NUMBER) >> SHORT_ABS)

#endif
