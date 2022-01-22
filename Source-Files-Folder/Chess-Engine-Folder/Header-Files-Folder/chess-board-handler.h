
#ifndef CHESS_BOARD_HANDLER_H
#define CHESS_BOARD_HANDLER_H

bool move_inside_board(Move);

bool point_inside_board(Point);

bool board_points_team(const Piece[], Point, Point);

bool board_pieces_team(Piece, Piece);

bool board_teams_team(Piece, Piece);

bool board_teams_enemy(Piece, Piece);

short move_rank_offset(Move, Piece);

short move_file_offset(Move, Piece);

bool chess_piece_empty(Piece);

bool board_piece_exists(Piece);

bool piece_team_exists(Piece);

bool piece_type_exists(Piece);

unsigned short move_array_amount(const Move[]);

bool info_team_exists(Info);

Info info_team_enemy(Info);

unsigned short normal_team_enemy(unsigned short);

bool normal_team_exists(unsigned short);

#endif
