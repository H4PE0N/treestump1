
#include "../Header-Files-Folder/englog-include-file.h"

bool move_fully_legal(const Piece board[], Info info, Move move)
{
	unsigned short startTeam = MOVE_START_TEAM(board, move);
	if(!current_team_move(info, startTeam)) return false;

	if(!move_pseudo_legal(board, info, move)) return false;

	return move_check_handler(board, info, move);
}

bool move_pseudo_legal(const Piece board[], Info info, Move move)
{
	if(!move_ability_valid(move, info)) return false;

	return board_move_legal(board, move);
}

bool board_move_legal(const Piece board[], Move move)
{
	if(!MOVE_INSIDE_BOARD(move)) return false;

	Piece startPiece = MOVE_START_PIECE(board, move);

	if(!move_pattern_valid(move, startPiece)) return false;

	return move_pattern_fits(board, move);
}

bool piece_legal_moves(Move** moveArray, const Piece board[], Info info, Point piecePoint)
{
	if(!POINT_INSIDE_BOARD(piecePoint)) return false;

	Move* pattMoves;
	if(!piece_pattern_moves(&pattMoves, board, piecePoint)) return false;

	unsigned short pattAmount = move_array_amount(pattMoves);

	*moveArray = create_move_array(32); short moveAmount = 0;

	Piece pieceType = MASK_PIECE_TYPE(board[piecePoint]);

	for(unsigned short index = 0; index < pattAmount; index += 1)
	{
		Move currentMove = pattMoves[index];

		if(!pattern_move_legal(&currentMove, board, info)) continue;

		if((pieceType == PIECE_TYPE_PAWN) && MOVE_PROMOTE_FLAG(currentMove))
			append_promote_moves(*moveArray, &moveAmount, currentMove);

		else (*moveArray)[moveAmount++] = currentMove;
	}
	free(pattMoves); return true;
}

bool piece_legal_points(Point** pointArray, const Piece board[], Info info, Point piecePoint)
{
	if(!POINT_INSIDE_BOARD(piecePoint)) return false;

	Move* pattMoves;
	if(!piece_pattern_moves(&pattMoves, board, piecePoint)) return false;

	unsigned short pattAmount = move_array_amount(pattMoves);

	*pointArray = create_point_array(32); short pointAmount = 0;

	for(unsigned short index = 0; index < pattAmount; index += 1)
	{
		Move currentMove = pattMoves[index];

		if(!pattern_move_legal(&currentMove, board, info)) continue;

		(*pointArray)[pointAmount++] = MOVE_STOP_MACRO(currentMove);
	}
	free(pattMoves); return true;
}

bool pattern_move_legal(Move* patternMove, const Piece board[], Info info)
{
	if(MOVE_POINTS_TEAM(board, *patternMove)) return false;

	if(!correct_move_flag(patternMove, board, info)) return false;

	return move_fully_legal(board, info, *patternMove);
}

void append_promote_moves(Move* moveArray, short* moveAmount, Move promoteMove)
{
	moveArray[(*moveAmount)++] = ALLOC_MOVE_FLAG(promoteMove, MOVE_FLAG_KNIGHT);

	moveArray[(*moveAmount)++] = ALLOC_MOVE_FLAG(promoteMove, MOVE_FLAG_BISHOP);

	moveArray[(*moveAmount)++] = ALLOC_MOVE_FLAG(promoteMove, MOVE_FLAG_ROOK);

	moveArray[(*moveAmount)++] = ALLOC_MOVE_FLAG(promoteMove, MOVE_FLAG_QUEEN);
}

bool team_legal_moves(Move** moveArray, const Piece board[], Info info, unsigned short team)
{
	if(!NORMAL_TEAM_EXISTS(team)) return false;

	*moveArray = create_move_array(256); short moveAmount = 0;

	for(Point point = 0; point < BOARD_LENGTH; point += 1)
	{
		unsigned short currentTeam = PIECE_TEAM_MACRO(board[point]);
		if(!NORMAL_TEAMS_TEAM(currentTeam, team)) continue;

		Move* pieceMoves;
		if(!piece_legal_moves(&pieceMoves, board, info, point)) continue;

		append_piece_moves(*moveArray, &moveAmount, pieceMoves);

		free(pieceMoves);
	}
	return true;
}

void append_piece_moves(Move* moveArray, short* moveAmount, const Move pieceMoves[])
{
	unsigned short addingAmount = move_array_amount(pieceMoves);

	for(short index = 0; index < addingAmount; index += 1)
		moveArray[(*moveAmount)++] = pieceMoves[index];
}
