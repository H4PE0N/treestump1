
#ifndef BOARD_SCORE_DEFINES_H
#define BOARD_SCORE_DEFINES_H

extern const signed short PAWN_MATRIX[8][8];

extern const signed short KNIGHT_MATRIX[8][8];

extern const signed short BISHOP_MATRIX[8][8];

extern const signed short ROOK_MATRIX[8][8];

extern const signed short QUEEN_MATRIX[8][8];

extern const signed short KING_MATRIX[8][8];

extern const signed short PIECE_TYPE_SCORES[7];

extern const signed short MATE_SCORE;
extern const signed short DRAW_SCORE;

extern const float MATRIX_FACTOR;
extern const float PIECE_FACTOR;

extern const signed short MIN_STATE_SCORE;
extern const signed short MAX_STATE_SCORE;

#endif
