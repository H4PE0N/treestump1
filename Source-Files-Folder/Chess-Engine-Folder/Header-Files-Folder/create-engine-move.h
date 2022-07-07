
#ifndef CREATE_ENGINE_MOVE_H
#define CREATE_ENGINE_MOVE_H

bool amount_engine_moves(Move**, const Piece[], Info, Kings, unsigned short, short, short);

void paste_engine_moves(Move**, short, const Move[], short);

bool sorted_engine_moves(Move**, const Piece[], Info, Kings, unsigned short, short);

bool move_array_values(short**, const Piece[], Info, Kings, unsigned short, short, const Move[], short);

short* create_short_array(unsigned short);


bool chess_move_value(signed short*, const Piece[], Info, Kings, unsigned short, short, signed short, signed short, Move);

bool simulate_move_value(signed short*, Piece*, Info, Kings, unsigned short, short, signed short, signed short, Move);


bool create_engine_move(Move*, const Piece[], Info, Kings, unsigned short, short);

bool choose_engine_move(Move*, const Piece[], Info, Kings, unsigned short, short, const Move[], short);


unsigned short board_depth_value(const Piece[], Info, Kings, unsigned short, short, signed short, signed short);

signed short choose_move_value(const Piece[], Info, Kings, unsigned short, short, signed short, signed short, const Move[], short);


void update_best_value(signed short, signed short*, unsigned short);

void update_alpha_beta(signed short, signed short*, signed short*, unsigned short);


bool optimal_depth_move(Move*, const Piece[], Info, Kings, unsigned short, short);

bool search_depths_move(Move*, const Piece[], Info, Kings, unsigned short, short, const Move[], short);

bool choose_timing_move(Move*, signed short*, const Piece[], Info, Kings, unsigned short, short, long, short, const Move[], short);

#endif
