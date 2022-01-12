
#include "../Header-Files-Folder/engine-include-file.h"

bool move_inside_board(Move move)
{
	Point start = MOVE_START_MACRO(move);
	Point stop = MOVE_STOP_MACRO(move);

	bool startInside = point_inside_board(start);
	bool stopInside = point_inside_board(stop);

	return (startInside && stopInside);
}

bool point_inside_board(Point point)
{
	return NUMBER_IN_BOUNDS(point, 0, BOARD_LENGTH);
}

bool board_points_team(const Piece board[], Point first, Point second)
{
	Piece firstPiece = board[first];
	Piece secondPiece = board[second];

	return board_pieces_team(firstPiece, secondPiece);
}

bool board_pieces_team(Piece firstPiece, Piece secondPiece)
{
	Piece firstTeam = firstPiece & PIECE_TEAM_MASK;
	Piece secondTeam = secondPiece & PIECE_TEAM_MASK;

	return board_teams_team(firstTeam, secondTeam);
}

bool board_teams_team(Piece firstTeam, Piece secondTeam)
{
	bool bothBlack = (firstTeam == PIECE_TEAM_BLACK && secondTeam == PIECE_TEAM_BLACK);
	bool bothWhite = (firstTeam == PIECE_TEAM_WHITE && secondTeam == PIECE_TEAM_WHITE);

	return (bothBlack || bothWhite);
}

bool board_teams_enemy(Piece firstTeam, Piece secondTeam)
{
	bool bothBlack = (firstTeam == PIECE_TEAM_BLACK && secondTeam == PIECE_TEAM_BLACK);
	bool bothWhite = (firstTeam == PIECE_TEAM_WHITE && secondTeam == PIECE_TEAM_WHITE);

	return (!bothBlack && !bothWhite);
}

// bool board_points_enemy()
// {
// 
// }

short move_file_offset(Move move, Piece pieceTeam)
{
	Point startPoint = MOVE_START_MACRO(move);
	Point stopPoint = MOVE_STOP_MACRO(move);

	File startFile = POINT_FILE_MACRO(startPoint);
	File stopFile = POINT_FILE_MACRO(stopPoint);

	short fileOffset = (stopFile - startFile);

	if(pieceTeam == PIECE_TEAM_WHITE) return fileOffset;// * WHITE_MOVE_VALUE;

	if(pieceTeam == PIECE_TEAM_BLACK) return fileOffset;// * BLACK_MOVE_VALUE;

	return SHORT_NONE;
}

short move_rank_offset(Move move, Piece pieceTeam)
{
	Point startPoint = MOVE_START_MACRO(move);
	Point stopPoint = MOVE_STOP_MACRO(move);

	Rank startRank = POINT_RANK_MACRO(startPoint);
	Rank stopRank = POINT_RANK_MACRO(stopPoint);

	short rankOffset = (stopRank - startRank);

	if(pieceTeam == PIECE_TEAM_WHITE) return rankOffset * WHITE_MOVE_VALUE;

	if(pieceTeam == PIECE_TEAM_BLACK) return rankOffset * BLACK_MOVE_VALUE;

	return SHORT_NONE;
}

bool chess_piece_empty(Piece piece)
{
	Piece pieceTeam = (piece & PIECE_TEAM_MASK);
	Piece pieceType = (piece & PIECE_TYPE_MASK);

	return (pieceTeam == PIECE_TEAM_NONE && pieceType == PIECE_TYPE_NONE);
}