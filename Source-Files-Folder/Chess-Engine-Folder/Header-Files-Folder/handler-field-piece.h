
#ifndef HANDLER_FIELD_PIECE_H
#define HANDLER_FIELD_PIECE_H

bool chess_piece_exists(Piece);

bool piece_team_exists(Piece);

bool piece_type_exists(Piece);

bool piece_teams_team(Piece, Piece);

bool piece_teams_enemy(Piece, Piece);

bool chess_pieces_team(Piece, Piece);

bool chess_pieces_enemy(Piece, Piece);

Piece piece_team_enemy(Piece);

// These may should not be here:
unsigned short board_point_team(Point, const Piece[]);
unsigned short move_start_team(Move, const Piece[]);
Piece* copy_chess_board(const Piece[]);
Piece point_piece_type(Point, const Piece[]);

#endif
