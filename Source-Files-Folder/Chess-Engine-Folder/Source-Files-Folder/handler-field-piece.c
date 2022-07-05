
#include "../Header-Files-Folder/engine-include-file.h"

bool piece_team_exists(Piece pieceTeam)
{
	unsigned short team = PIECE_TEAM_MACRO(pieceTeam);

	return (team == TEAM_WHITE || team == TEAM_BLACK);
}

bool piece_type_exists(Piece pieceType)
{
	unsigned short type = PIECE_TYPE_MACRO(pieceType);

	return NUMBER_IN_BOUNDS(type, 1, 6);
}

bool chess_piece_exists(Piece piece)
{
	bool pieceTeamExists = piece_team_exists(piece);
	bool pieceTypeExists = piece_type_exists(piece);

	return (pieceTeamExists && pieceTypeExists);
}

bool piece_teams_team(Piece firstPieceTeam, Piece secondPieceTeam)
{
	bool bothBlack = (firstPieceTeam == PIECE_TEAM_BLACK && secondPieceTeam == PIECE_TEAM_BLACK);
	bool bothWhite = (firstPieceTeam == PIECE_TEAM_WHITE && secondPieceTeam == PIECE_TEAM_WHITE);

	return (bothBlack || bothWhite);
}

bool piece_teams_enemy(Piece firstPieceTeam, Piece secondPieceTeam)
{
	bool enemyWhite = (firstPieceTeam == PIECE_TEAM_BLACK && secondPieceTeam == PIECE_TEAM_WHITE);
	bool enemyBlack = (firstPieceTeam == PIECE_TEAM_WHITE && secondPieceTeam == PIECE_TEAM_BLACK);

	return (enemyWhite || enemyBlack);
}

bool chess_pieces_team(Piece firstPiece, Piece secondPiece)
{
	Piece firstPieceTeam = (firstPiece & PIECE_TEAM_MASK);
	Piece secondPieceTeam = (secondPiece & PIECE_TEAM_MASK);

	return piece_teams_team(firstPieceTeam, secondPieceTeam);
}

bool chess_pieces_enemy(Piece firstPiece, Piece secondPiece)
{
	Piece firstPieceTeam = (firstPiece & PIECE_TEAM_MASK);
	Piece secondPieceTeam = (secondPiece & PIECE_TEAM_MASK);

	return piece_teams_enemy(firstPieceTeam, secondPieceTeam);
}

Piece piece_team_enemy(Piece pieceTeam)
{
	if(pieceTeam == PIECE_TEAM_WHITE) return PIECE_TEAM_BLACK;

	else if(pieceTeam == PIECE_TEAM_BLACK) return PIECE_TEAM_WHITE;

	return PIECE_TEAM_NONE;
}
