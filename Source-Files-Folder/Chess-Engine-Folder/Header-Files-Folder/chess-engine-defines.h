
#ifndef CHESS_ENGINE_DEFINES_H
#define CHESS_ENGINE_DEFINES_H

extern const unsigned short BOARD_RANKS;
extern const unsigned short BOARD_FILES;
extern const unsigned short BOARD_LENGTH;

extern const signed short MIN_BOARD_VALUE;
extern const signed short MAX_BOARD_VALUE;

extern const signed short BLACK_MOVE_VALUE;
extern const signed short WHITE_MOVE_VALUE;

extern const unsigned short WHITE_START_RANK; // This is the index rank, not the notation rank
extern const unsigned short BLACK_START_RANK; // This is the index rank, not the notation rank

extern const unsigned short WHITE_PAWN_RANK;
extern const unsigned short BLACK_PAWN_RANK;

extern const unsigned short KING_START_FILE;

extern const signed short KING_CASTLE_PAT;
extern const signed short QUEEN_CASTLE_PAT;

#endif
