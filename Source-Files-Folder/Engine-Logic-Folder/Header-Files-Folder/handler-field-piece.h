
#ifndef HANDLER_FIELD_PIECE_H
#define HANDLER_FIELD_PIECE_H

bool chess_piece_exists(Piece piece);

bool piece_team_exists(Piece pieceTeam);

bool piece_type_exists(Piece pieceType);

bool piece_teams_team(Piece pieceTeam1, Piece pieceTeam2);

bool piece_teams_enemy(Piece pieceTeam1, Piece pieceTeam2);

bool chess_pieces_team(Piece piece1, Piece piece2);

bool chess_pieces_enemy(Piece piece1, Piece piece2);

Piece piece_team_enemy(Piece pieceTeam);

// These may should not be here:
unsigned short board_point_team(Point point, const Piece board[]);

unsigned short move_start_team(Move move, const Piece board[]);

Piece* copy_chess_board(const Piece board[]);

Piece point_piece_type(Point point, const Piece board[]);

unsigned short move_start_enemy(Move move, const Piece board[]);

#endif
