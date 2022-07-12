
#ifndef CREATE_ENGINE_MOVE_H
#define CREATE_ENGINE_MOVE_H

bool chess_move_value(signed short*, const Piece[], Info, unsigned short, short, signed short, signed short, Move);

bool simulate_move_value(signed short*, Piece*, Info, unsigned short, short, signed short, signed short, Move);

bool engine_depth_move(Move*, const Piece[], Info, unsigned short, short);

bool choose_engine_move(Move*, const Piece[], Info, unsigned short, short, const Move[], short);

void update_move_value(Move, signed short, Move*, signed short*, unsigned short);

bool update_mate_value(Move, signed short, Move*, signed short*, unsigned short);

signed short board_depth_value(const Piece[], Info, unsigned short, short, signed short, signed short);

signed short choose_move_value(const Piece[], Info, unsigned short, short, signed short, signed short, const Move[], short);

void update_best_value(signed short, signed short*, unsigned short);

void update_alpha_beta(signed short, signed short*, signed short*, unsigned short);

bool current_mate_value(signed short, unsigned short);

#endif
