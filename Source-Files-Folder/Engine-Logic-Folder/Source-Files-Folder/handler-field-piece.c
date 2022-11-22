
#include "../Header-Files-Folder/englog-include-file.h"

Piece* copy_chess_board(const Piece board[])
{
	Piece* boardCopy = malloc(sizeof(Piece) * BOARD_LENGTH);
	memcpy(boardCopy, board, sizeof(Piece) * BOARD_LENGTH);

	return boardCopy;
}

unsigned short board_point_team(Point point, const Piece board[])
{
	if(!POINT_INSIDE_BOARD(point)) return TEAM_NONE;

	return PIECE_TEAM_MACRO(board[point]);
}

Piece point_piece_type(Point point, const Piece board[])
{
	if(!POINT_INSIDE_BOARD(point)) return PIECE_TYPE_NONE;

	return MASK_PIECE_TYPE(board[point]);
}

unsigned short move_start_team(Move move, const Piece board[])
{
	if(!move_inside_board(move)) return TEAM_NONE;

	return board_point_team(MOVE_START_MACRO(move), board);
}

unsigned short move_start_enemy(Move move, const Piece board[])
{
	if(!move_inside_board(move)) return TEAM_NONE;

	return normal_team_enemy(move_start_team(move, board));
}

bool piece_team_exists(Piece pieceTeam)
{
	unsigned short team = PIECE_TEAM_MACRO(pieceTeam);

	return ((team == TEAM_WHITE) || (team == TEAM_BLACK));
}

bool piece_type_exists(Piece pieceType)
{
	return NUMBER_IN_BOUNDS(PIECE_TYPE_MACRO(pieceType), 1, 6);
}

bool chess_piece_exists(Piece piece)
{
	bool pieceTeamExists = piece_team_exists(piece);
	bool pieceTypeExists = piece_type_exists(piece);

	return (pieceTeamExists && pieceTypeExists);
}

bool piece_teams_team(Piece pieceTeam1, Piece pieceTeam2)
{
	if((pieceTeam1 == PIECE_TEAM_BLACK) && (pieceTeam2 == PIECE_TEAM_BLACK)) return true;
	if((pieceTeam1 == PIECE_TEAM_WHITE) && (pieceTeam2 == PIECE_TEAM_WHITE)) return true;

	return false;
}

bool piece_teams_enemy(Piece pieceTeam1, Piece pieceTeam2)
{
	if((pieceTeam1 == PIECE_TEAM_BLACK) && (pieceTeam2 == PIECE_TEAM_WHITE)) return true;
	if((pieceTeam1 == PIECE_TEAM_WHITE) && (pieceTeam2 == PIECE_TEAM_BLACK)) return true;

	return false;
}

bool chess_pieces_team(Piece piece1, Piece piece2)
{
	Piece pieceTeam1 = MASK_PIECE_TEAM(piece1);
	Piece pieceTeam2 = MASK_PIECE_TEAM(piece2);

	return piece_teams_team(pieceTeam1, pieceTeam2);
}

bool chess_pieces_enemy(Piece piece1, Piece piece2)
{
	Piece pieceTeam1 = MASK_PIECE_TEAM(piece1);
	Piece pieceTeam2 = MASK_PIECE_TEAM(piece2);

	return piece_teams_enemy(pieceTeam1, pieceTeam2);
}

Piece piece_team_enemy(Piece pieceTeam)
{
	if(pieceTeam == PIECE_TEAM_WHITE) return PIECE_TEAM_BLACK;
	if(pieceTeam == PIECE_TEAM_BLACK) return PIECE_TEAM_WHITE;

	return PIECE_TEAM_NONE;
}
