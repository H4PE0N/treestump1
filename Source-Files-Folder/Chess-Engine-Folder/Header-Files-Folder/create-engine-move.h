
#ifndef CREATE_ENGINE_MOVE_H
#define CREATE_ENGINE_MOVE_H

bool amount_engine_moves(Move**, const Piece[], Info, unsigned short, short, short);

void paste_engine_moves(Move**, short, const Move[], short);

bool sorted_engine_moves(Move**, const Piece[], Info, unsigned short, short);

bool move_array_values(short**, const Piece[], Info, unsigned short, short, const Move[], short);

short* create_short_array(unsigned short);


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


bool optimal_depth_move(Move*, const Piece[], Info, unsigned short, short);

bool search_depths_move(Move*, const Piece[], Info, unsigned short, short, const Move[], short);

bool choose_timing_move(Move*, signed short*, const Piece[], Info, unsigned short, short, long, short, const Move[], short);

bool timing_limit_ended(long, short);

double time_passed_since(long);


bool guess_moves_values(signed short**, const Move[], short, const Piece[], Info);

signed short guess_move_value(const Piece[], Info, Move);

bool guess_order_moves(Move*, short, const Piece[], Info);


bool ordered_legal_moves(Move**, const Piece[], Info, unsigned short);


long search_depth_nodes(const Piece[], Info, unsigned short, short, long, short);

long search_move_nodes(const Piece[], Info, unsigned short, short, Move, long, short);

#endif
