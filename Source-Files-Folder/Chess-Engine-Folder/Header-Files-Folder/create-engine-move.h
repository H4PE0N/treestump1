
#ifndef CREATE_ENGINE_MOVE_H
#define CREATE_ENGINE_MOVE_H

// bool chess_move_value(signed short* moveValue, const Piece board[], Info info, unsigned short currentTeam, short depth, signed short alpha, signed short beta, Move move);
//
// bool simulate_move_value(signed short* moveValue, Piece* boardCopy, Info infoCopy, unsigned short currentTeam, short depth, signed short alpha, signed short beta, Move move);
//
// bool engine_depth_move(Move* move, const Piece board[], Info info, unsigned short team, signed short depth);
//
// bool choose_engine_move(Move* move, const Piece board[], Info info, unsigned short team, short depth, const Move moveArray[], short moveAmount);
//
// void update_move_value(Move currentMove, signed short currentValue, Move* bestMove, signed short* bestValue, unsigned short team);
//
// bool update_mate_value(Move currentMove, signed short currentValue, Move* bestMove, signed short* bestValue, unsigned short team);
//
// signed short board_depth_value(const Piece board[], Info info, unsigned short currentTeam, short depth, signed short alpha, signed short beta);
//
// signed short choose_move_value(const Piece board[], Info info, unsigned short currentTeam, short depth, signed short alpha, signed short beta, const Move moveArray[], short moveAmount);
//
// void update_best_value(signed short currentValue, signed short* bestValue, unsigned short team);
//
// void update_alpha_beta(signed short currentValue, signed short* alpha, signed short* beta, unsigned short team);
//
// bool current_mate_value(signed short currentValue, unsigned short team);

bool engine_depth_move(Move* bestMove, const Piece board[], Info info, int depth);

bool choose_engine_move(Move* bestMove, const Piece board[], Info info, int depth, int playerSign, const Move moveArray[], short moveAmount);

int board_depth_score(const Piece board[], Info info, int depth, int alpha, int beta, int playerSign);

int choose_move_score(const Piece board[], Info info, int depth, int alpha, int beta, int playerSign, const Move moveArray[], short moveAmount);

int chess_move_score(const Piece board[], Info info, int depth, int alpha, int beta, int playerSign, Move move);

int simulate_move_score(Piece* boardCopy, Info infoCopy, int depth, int alpha, int beta, int playerSign, Move move);

#endif
