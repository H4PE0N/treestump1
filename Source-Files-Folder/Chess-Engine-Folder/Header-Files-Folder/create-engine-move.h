
#ifndef CREATE_COMPUTER_MOVE_H
#define CREATE_COMPUTER_MOVE_H

bool amount_engine_moves(Move**, const Piece[], Info, Kings, unsigned short, signed short, unsigned short);

void paste_engine_moves(Move**, unsigned short, const Move[]);

bool sorted_engine_moves(Move**, const Piece[], Info, Kings, unsigned short, signed short);

bool move_array_values(short**, const Piece[], Info, Kings, unsigned short, signed short, const Move[]);

short* create_short_array(unsigned short);


bool chess_move_value(signed short*, const Piece[], Info, Kings, unsigned short, signed short, signed short, signed short, Move);

bool simulate_move_value(signed short*, Piece*, Info, Kings, unsigned short, signed short, signed short, signed short, Move);


bool create_engine_move(Move*, const Piece[], Info, Kings, unsigned short, signed short);

bool choose_engine_move(Move*, const Piece[], Info, Kings, unsigned short, signed short, const Move[]);


unsigned short board_depth_value(const Piece[], Info, Kings, unsigned short, signed short, signed short, signed short);

signed short choose_move_value(const Piece[], Info, Kings, unsigned short, signed short, signed short, signed short, const Move[]);


void update_best_value(signed short, signed short*, unsigned short);

void update_alpha_beta(signed short, signed short*, signed short*, unsigned short);

#endif
