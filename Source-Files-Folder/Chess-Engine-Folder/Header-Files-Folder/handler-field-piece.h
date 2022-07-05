
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

#endif
