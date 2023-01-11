
#include "../Header-Files-Folder/engine-include-file.h"

// The score of the board is positive for whites favour and negative for blacks favour
int board_state_score(const Piece board[], Info info)
{
	int boardScore = 0;

	boardScore += board_pieces_score(board);

	// boardScore = DRAW_SCORE (not higher or lower);
	boardScore += check_draw_score(board, info);

	// boardScore = MATE_SCORE (not higher or lower);
	boardScore += check_mate_score(board, info);

	return boardScore;
}

int board_pieces_score(const Piece board[])
{
	int piecesScore = 0;
	for(Point point = 0; point < BOARD_LENGTH; point += 1)
	{
		Piece piece = board[point];

		if(!CHESS_PIECE_EXISTS(piece)) continue;

		piecesScore += chess_piece_score(piece) * PIECE_FACTOR;

		piecesScore += piece_matrix_score(piece, point) * MATRIX_FACTOR;
	}
	return piecesScore;
}

int check_mate_score(const Piece board[], Info info)
{
	int mateScore = 0;

	if(check_mate_ending(board, info, TEAM_WHITE)) mateScore -= MATE_SCORE;

	else if(check_mate_ending(board, info, TEAM_BLACK)) mateScore += MATE_SCORE;

	return mateScore;
}

int check_draw_score(const Piece board[], Info info)
{
	int drawScore = 0;

	if(check_draw_ending(board, info, TEAM_WHITE)) drawScore -= DRAW_SCORE;

	else if(check_draw_ending(board, info, TEAM_BLACK)) drawScore += DRAW_SCORE;

	return drawScore;
}


int chess_piece_score(Piece piece)
{
	if(!CHESS_PIECE_EXISTS(piece)) return 0;

	uint8_t team = PIECE_TEAM_MACRO(piece);
	uint8_t type = PIECE_TYPE_MACRO(piece);

	int pieceScore = PIECE_TYPE_SCORES[type];

	return TEAM_WEIGHT_SCORE(pieceScore, team);
}

int piece_matrix_score(Piece piece, Point point)
{
	if(!POINT_INSIDE_BOARD(point) || !CHESS_PIECE_EXISTS(piece)) return 0;

	Piece pieceTeam = (piece & PIECE_TEAM_MASK);
  Piece pieceType = (piece & PIECE_TYPE_MASK);

  uint8_t rank = POINT_RANK_MACRO(point);

	uint8_t teamRank = team_matrix_rank(rank, pieceTeam);
	uint8_t teamFile = POINT_FILE_MACRO(point);

	int matrixScore = type_matrix_score(pieceType, teamRank, teamFile);

	uint8_t team = PIECE_TEAM_MACRO(piece);

	return TEAM_WEIGHT_SCORE(matrixScore, team);
}

uint8_t team_matrix_rank(uint8_t rank, Piece pieceTeam)
{
	return ((pieceTeam == PIECE_TEAM_BLACK) ? (BOARD_RANKS - rank - 1) : rank);
}

int type_matrix_score(Piece pieceType, uint8_t rank, uint8_t file)
{
	if(pieceType == PIECE_TYPE_PAWN) return PAWN_MATRIX[rank][file];

	if(pieceType == PIECE_TYPE_KNIGHT) return KNIGHT_MATRIX[rank][file];

	if(pieceType == PIECE_TYPE_BISHOP) return BISHOP_MATRIX[rank][file];

	if(pieceType == PIECE_TYPE_ROOK) return ROOK_MATRIX[rank][file];

	if(pieceType == PIECE_TYPE_QUEEN) return QUEEN_MATRIX[rank][file];

	if(pieceType == PIECE_TYPE_KING) return KING_MATRIX[rank][file];

	return 0;
}
