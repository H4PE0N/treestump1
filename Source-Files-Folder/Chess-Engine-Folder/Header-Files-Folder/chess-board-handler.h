
#ifndef CHESS_BOARD_HANDLER_H
#define CHESS_BOARD_HANDLER_H

// ##############################################################################

bool chess_piece_exists(Piece);

bool piece_team_exists(Piece);

bool piece_type_exists(Piece);




bool piece_teams_team(Piece, Piece);

bool piece_teams_enemy(Piece, Piece);



bool chess_pieces_team(Piece, Piece);

bool chess_pieces_enemy(Piece, Piece);



Piece piece_team_enemy(Piece);


Point board_piece_point(const Piece[], Piece);

Point rank_file_point(unsigned short, unsigned short);

// ##############################################################################

bool point_inside_board(Point);

bool board_points_team(const Piece[], Point, Point);

bool board_points_enemy(const Piece[], Point, Point);

bool board_point_exists(const Piece[], Point);

signed short array_point_index(const Point[], unsigned short, Point);

bool delete_array_point(Point*, unsigned short, short);

unsigned short point_array_amount(const Point[]);

Point* create_point_array(unsigned short);

// ##############################################################################

bool info_team_exists(Info);

Info info_team_enemy(Info);

// ##############################################################################

bool move_inside_board(Move);

bool move_points_team(const Piece[], Move);

bool move_points_enemy(const Piece[], Move);

short move_rank_offset(Move, unsigned short);

short move_file_offset(Move, unsigned short);

short normal_rank_offset(Move);

short normal_file_offset(Move);

unsigned short move_array_amount(const Move[]);

Move* create_move_array(unsigned short);

signed short board_move_pattern(Move);

bool create_move_string(char*, const Piece[], Info, Kings, Move);

bool create_point_string(char*, Point);

// ##############################################################################

Point team_king_point(Kings, unsigned short);

// ##############################################################################

unsigned short normal_team_enemy(unsigned short);

bool normal_team_exists(unsigned short);

bool normal_teams_team(unsigned short, unsigned short);

bool normal_teams_enemy(unsigned short, unsigned short);

#endif
