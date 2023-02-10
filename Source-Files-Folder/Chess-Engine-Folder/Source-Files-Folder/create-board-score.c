
#include "../Header-Files-Folder/engine-include-file.h"

// The score of the board is positive for whites favour and negative for blacks favour
int board_state_score(const Piece board[], State state)
{
	uint8_t team = STATE_TEAM_MACRO(state);

	if(check_mate_ending(board, state, team))
	{
		return TEAM_WEIGHT_SCORE(MATE_SCORE, team);
	}
	else if(check_draw_ending(board, state, team))
	{
		return TEAM_WEIGHT_SCORE(DRAW_SCORE, team);
	}
	return board_pieces_score(board);
}

int board_pieces_score(const Piece board[])
{
	int piecesScore = 0;
	for(Point point = 0; point < BOARD_LENGTH; point += 1)
	{
		if(!CHESS_PIECE_EXISTS(board[point])) continue;

		piecesScore += chess_piece_score(board[point], point);
	}
	return piecesScore;
}

int chess_piece_score(Piece piece, Point point)
{
	uint8_t team = PIECE_TEAM_MACRO(piece);
	uint8_t type = PIECE_TYPE_MACRO(piece);

	uint8_t rank = TEAM_MATRIX_RANK(POINT_RANK_MACRO(point), team);
	uint8_t file = POINT_FILE_MACRO(point);

	int typeScore = PIECE_TYPE_SCORES[type];
	int matrixScore = TYPE_SCORE_MATRIX[type][rank][file];

	int pieceScore = (typeScore * TYPE_FACTOR + matrixScore * MATRIX_FACTOR);

	return TEAM_WEIGHT_SCORE(pieceScore, team);
}
