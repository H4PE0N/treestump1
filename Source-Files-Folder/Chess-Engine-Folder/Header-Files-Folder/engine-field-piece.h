
#ifndef ENGINE_FIELD_PIECE_H
#define ENGINE_FIELD_PIECE_H

typedef unsigned short Piece;

#define PIECE_TEAM_MACRO(PIECE) ( (PIECE & PIECE_TEAM_MASK) >> PIECE_TEAM_SHIFT)
#define PIECE_TYPE_MACRO(PIECE) ( (PIECE & PIECE_TYPE_MASK) >> PIECE_TYPE_SHIFT)

#define TEAM_PIECE_MACRO(TEAM) ( (TEAM << PIECE_TEAM_SHIFT) & PIECE_TEAM_MASK)
#define TYPE_PIECE_MACRO(TYPE) ( (TYPE << PIECE_TYPE_SHIFT) & PIECE_TYPE_MASK)

#define ALLOC_PIECE_TEAM(PIECE, TEAM) ( (PIECE & ~PIECE_TEAM_MASK) | (TEAM & PIECE_TEAM_MASK) )
#define ALLOC_PIECE_TYPE(PIECE, TYPE) ( (PIECE & ~PIECE_TYPE_MASK) | (TYPE & PIECE_TYPE_MASK) )

#define MASK_PIECE_TYPE(PIECE) (PIECE & PIECE_TYPE_MASK)

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

extern const unsigned short PIECE_TEAM_SHIFT;
extern const unsigned short PIECE_TYPE_SHIFT;

extern const Piece PIECE_NONE;
extern const Piece PIECE_BLANK;

#endif
