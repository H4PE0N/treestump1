
#ifndef CHESS_BOARD_HANDLER_H
#define CHESS_BOARD_HANDLER_H

// ##############################################################################

bool board_pieces_team(Piece, Piece);

bool board_teams_team(Piece, Piece);

bool board_teams_enemy(Piece, Piece);

bool chess_piece_empty(Piece);

bool board_piece_exists(Piece);

bool piece_team_exists(Piece);

bool piece_type_exists(Piece);

// ##############################################################################

bool point_inside_board(Point);

bool board_points_team(const Piece[], Point, Point);

// ##############################################################################

bool info_team_exists(Info);

Info info_team_enemy(Info);

// ##############################################################################

bool move_inside_board(Move);

short move_rank_offset(Move, unsigned short);

short move_file_offset(Move, unsigned short);

unsigned short move_array_amount(const Move[]);

// ##############################################################################

// Kings

// ##############################################################################

unsigned short normal_team_enemy(unsigned short);

bool normal_team_exists(unsigned short);

#endif
