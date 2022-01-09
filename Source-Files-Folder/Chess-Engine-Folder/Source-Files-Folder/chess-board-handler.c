
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
	return short_inside_bounds(point, 0, BOARD_LENGTH);
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

bool team_move_value(short* teamPattern, Piece pieceTeam)
{
	if(pieceTeam == PIECE_TEAM_WHITE)
	{
		*teamPattern = WHITE_MOVE_VALUE;
	}
	else if(pieceTeam == PIECE_TEAM_BLACK)
	{
		*teamPattern = BLACK_MOVE_VALUE;
	}
	else
	{
		return false;
	}

	return true;
}

bool team_file_offset(short* fileOffset, Point startPoint, Point stopPoint, Piece pieceTeam)
{
	short moveValue;

	if(!team_move_value(&moveValue, pieceTeam))
	{
		return false;
	}

	File startFile = POINT_FILE_MACRO(startPoint);
	File stopFile = POINT_FILE_MACRO(stopPoint);

	*fileOffset = (stopFile - startFile) * moveValue;

	return true;
}

bool team_rank_offset(short* rankOffset, Point startPoint, Point stopPoint, Piece pieceTeam)
{
	short moveValue;

	if(!team_move_value(&moveValue, pieceTeam))
	{
		return false;
	}

	File startRank = POINT_RANK_MACRO(startPoint);
	File stopRank = POINT_RANK_MACRO(stopPoint);

	*rankOffset = (stopRank - startRank) * moveValue;

	return true;
}

bool team_pawn_rank(Rank* pawnRank, Piece pieceTeam)
{
	if(pieceTeam == PIECE_TEAM_WHITE)
	{
		*pawnRank = WHITE_PAWN_RANK;
	}
	else if(pieceTeam == PIECE_TEAM_BLACK)
	{
		*pawnRank = BLACK_PAWN_RANK;
	}
	else
	{
		return false;
	}

	return true;
}

bool team_starting_rank(Rank* startRank, Piece pieceTeam)
{
	if(pieceTeam == PIECE_TEAM_WHITE)
	{
		*startRank = WHITE_START_RANK;
	}
	else if(pieceTeam == PIECE_TEAM_BLACK)
	{
		*startRank = BLACK_START_RANK;
	}
	else
	{
		return false;
	}

	return true;
}

bool short_inside_bounds(short number, short minimum, short maximum)
{
	return (number >= minimum && number <= maximum);
}

short positive_short_value(short number)
{
	short shortMask = (number >> SHORT_BITS);

	return (shortMask ^ number) - shortMask;
}