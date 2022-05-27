
#include "../Header-Files-Folder/engine-include-file.h"

signed short team_state_value(const Piece board[], Info info, Kings kings, unsigned short team)
{
	if(!normal_team_exists(team)) return 0;

	unsigned short enemy = normal_team_enemy(team);

	signed short enemyValue = board_state_value(board, info, kings, enemy);
	signed short teamValue = board_state_value(board, info, kings, team);

	return (teamValue - enemyValue);
}

signed short team_pieces_value(const Piece board[], unsigned short team)
{
	// If the team does not exist:
	if(!normal_team_exists(team)) return 0;

	signed short piecesValue = 0;

	for(Point point = 0; point < BOARD_LENGTH; point += 1)
	{
		Piece piece = board[point];

		// If the piece does not exist for some reason:
		if(!chess_piece_exists(piece)) continue;

    unsigned short currentTeam = PIECE_TEAM_MACRO(piece);
    unsigned short currentType = PIECE_TYPE_MACRO(piece);

		if(!normal_teams_team(team, currentTeam)) continue;

		// Adding the value of the piece
		piecesValue += PIECE_VALUES[currentType];

		// Adding extra value for the piece location
		signed short matrixValue = piece_matrix_value(piece, point);

		piecesValue += matrixValue;
	}

	return piecesValue;
}

signed short piece_matrix_value(Piece piece, Point point)
{
	// This is a error catcher. If the point insn't inside the board, segfault is going to happen next
	if(!point_inside_board(point) || !chess_piece_exists(piece)) return 0;

	Piece pieceTeam = (piece & PIECE_TEAM_MASK);
  Piece pieceType = (piece & PIECE_TYPE_MASK);

  unsigned short rank = POINT_RANK_MACRO(point);

	unsigned short teamRank = team_matrix_rank(rank, pieceTeam);
	unsigned short teamFile = POINT_FILE_MACRO(point);

	signed short value = type_matrix_value(pieceType, teamRank, teamFile);

	return (signed short) ( (float) value * MATRIX_FACTOR);
}

unsigned short team_matrix_rank(unsigned short rank, Piece pieceTeam)
{
	return (pieceTeam == PIECE_TEAM_BLACK) ? (BOARD_RANKS-rank-1) : rank;
}

signed short type_matrix_value(Piece pieceType, unsigned short rank, unsigned short file)
{
	if(pieceType == PIECE_TYPE_PAWN) return PAWN_MATRIX[rank][file];

	else if(pieceType == PIECE_TYPE_KNIGHT) return KNIGHT_MATRIX[rank][file];

	else if(pieceType == PIECE_TYPE_BISHOP) return BISHOP_MATRIX[rank][file];

	else if(pieceType == PIECE_TYPE_ROOK) return ROOK_MATRIX[rank][file];

	else if(pieceType == PIECE_TYPE_QUEEN) return QUEEN_MATRIX[rank][file];

	else if(pieceType == PIECE_TYPE_KING) return KING_MATRIX[rank][file];

	return 0;
}

signed short check_mate_value(const Piece board[], Info info, Kings kings, unsigned short team)
{
	if(!normal_team_exists(team)) return 0;

	unsigned short enemy = normal_team_enemy(team);

	signed short mateValue = 0;

	// If the teamKing (own king) is in check mate
	if(check_mate_ending(board, info, kings, team)) mateValue = MIN_BOARD_VALUE;

	// If the enemyKing (opponent) is in check mate
	else if(check_mate_ending(board, info, kings, enemy)) mateValue = MAX_BOARD_VALUE;

	return mateValue;
}

signed short check_draw_value(const Piece board[], Info info, Kings kings, unsigned short team)
{
	if(!normal_team_exists(team)) return 0;

	unsigned short enemy = normal_team_enemy(team);

	signed short drawValue = 0;

	// If the own king cant move (oppenent did draw)
	if(check_draw_ending(board, info, kings, team)) drawValue = MAX_BOARD_VALUE;

	// If the opponent cant move (you did draw)
	else if(check_draw_ending(board, info, kings, enemy)) drawValue = MIN_BOARD_VALUE;

	return drawValue;
}

signed short board_state_value(const Piece board[], Info info, Kings kings, unsigned short team)
{
	if(!normal_team_exists(team)) return 0;

	signed short boardValue = 0;

	boardValue += team_pieces_value(board, team);

	boardValue += check_mate_value(board, info, kings, team);

	boardValue += check_draw_value(board, info, kings, team);

	return boardValue;
}
