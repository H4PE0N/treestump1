
#include "../Header-Files-Folder/engine-include-file.h"

// The score of the board is positive for whites favour and negative for blacks favour
signed short board_state_score(const Piece board[], Info info)
{
	signed short boardScore = 0;

	boardScore += board_pieces_score(board);

	// boardScore = DRAW_SCORE (not higher or lower);
	boardScore += check_draw_score(board, info);

	// boardScore = MATE_SCORE (not higher or lower);
	boardScore += check_mate_score(board, info);

	return boardScore;
}

signed short board_pieces_score(const Piece board[])
{
	signed short piecesScore = 0;
	for(Point point = 0; point < BOARD_LENGTH; point += 1)
	{
		Piece piece = board[point];

		if(!CHESS_PIECE_EXISTS(piece)) continue;

		piecesScore += chess_piece_score(piece) * PIECE_FACTOR;

		piecesScore += piece_matrix_score(piece, point) * MATRIX_FACTOR;
	}
	return piecesScore;
}

signed short check_mate_score(const Piece board[], Info info)
{
	signed short mateScore = 0;

	if(check_mate_ending(board, info, TEAM_WHITE)) mateScore -= MATE_SCORE;

	else if(check_mate_ending(board, info, TEAM_BLACK)) mateScore += MATE_SCORE;

	return mateScore;
}

signed short check_draw_score(const Piece board[], Info info)
{
	signed short drawScore = 0;

	if(check_draw_ending(board, info, TEAM_WHITE)) drawScore -= DRAW_SCORE;

	else if(check_draw_ending(board, info, TEAM_BLACK)) drawScore += DRAW_SCORE;

	return drawScore;
}


signed short chess_piece_score(Piece piece)
{
	if(!CHESS_PIECE_EXISTS(piece)) return 0;

	unsigned short team = PIECE_TEAM_MACRO(piece);
	unsigned short type = PIECE_TYPE_MACRO(piece);

	signed short pieceScore = PIECE_TYPE_SCORES[type];

	return team_weight_score(pieceScore, team);
}

signed short team_weight_score(signed short score, unsigned short team)
{
	if(team == TEAM_BLACK) return -score;
	if(team == TEAM_WHITE) return +score;

	return 0;
}

signed short piece_matrix_score(Piece piece, Point point)
{
	if(!POINT_INSIDE_BOARD(point) || !CHESS_PIECE_EXISTS(piece)) return 0;

	Piece pieceTeam = (piece & PIECE_TEAM_MASK);
  Piece pieceType = (piece & PIECE_TYPE_MASK);

  unsigned short rank = POINT_RANK_MACRO(point);

	unsigned short teamRank = team_matrix_rank(rank, pieceTeam);
	unsigned short teamFile = POINT_FILE_MACRO(point);

	signed short matrixScore = type_matrix_score(pieceType, teamRank, teamFile);

	unsigned short team = PIECE_TEAM_MACRO(piece);

	return team_weight_score(matrixScore, team);
}

unsigned short team_matrix_rank(unsigned short rank, Piece pieceTeam)
{
	return ((pieceTeam == PIECE_TEAM_BLACK) ? (BOARD_RANKS - rank - 1) : rank);
}

signed short type_matrix_score(Piece pieceType, unsigned short rank, unsigned short file)
{
	if(pieceType == PIECE_TYPE_PAWN) return PAWN_MATRIX[rank][file];

	if(pieceType == PIECE_TYPE_KNIGHT) return KNIGHT_MATRIX[rank][file];

	if(pieceType == PIECE_TYPE_BISHOP) return BISHOP_MATRIX[rank][file];

	if(pieceType == PIECE_TYPE_ROOK) return ROOK_MATRIX[rank][file];

	if(pieceType == PIECE_TYPE_QUEEN) return QUEEN_MATRIX[rank][file];

	if(pieceType == PIECE_TYPE_KING) return KING_MATRIX[rank][file];

	return 0;
}
