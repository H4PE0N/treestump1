
#include "../Header-Files-Folder/englog-include-file.h"

bool move_fully_legal(const Piece board[], Info info, Move move)
{
	if(!move_pseudo_legal(board, info, move)) return false;

	return move_check_handler(board, info, move);
}


// bool move_fully_legal(const Piece board[], Info info, Move move)
// {
// 	Piece startPiece = move_start_piece(move, board);
// 	unsigned short startTeam = PIECE_TEAM_MACRO(startPiece);
//
// 	if(!current_team_move(info, startTeam)) return false;
//
// 	if(!move_pseudo_legal(board, info, move)) return false;
//
// 	return move_check_handler(board, info, move);
// }

bool move_pseudo_legal(const Piece board[], Info info, Move move)
{
	if(!move_ability_valid(move, info)) return false;

	return board_move_legal(board, move);
}

bool board_move_legal(const Piece board[], Move move)
{
	if(!move_inside_board(move)) return false;

	Piece startPiece = move_start_piece(move, board);

	if(!move_pattern_valid(move, startPiece)) return false;

	return move_pattern_fits(board, move);
}

bool piece_legal_moves(Move** moveArray, const Piece board[], Info info, Point piecePoint)
{
	if(!POINT_INSIDE_BOARD(piecePoint)) return false;

	Move* pattMoves;
	if(!piece_pattern_moves(&pattMoves, board, piecePoint)) return false;

	unsigned short pattAmount = move_array_amount(pattMoves);

	*moveArray = create_move_array(32);
	short moveAmount = 0;

	Piece startPiece = board[piecePoint];
	Piece pieceType = MASK_PIECE_TYPE(startPiece);

	for(unsigned short index = 0; index < pattAmount; index += 1)
	{
		Move currentMove = pattMoves[index];
		Piece stopPiece = move_stop_piece(currentMove, board);

		if(piece_teams_team(stopPiece, startPiece)) continue;

		if(!correct_move_flag(&currentMove, board, info)) continue;
		if(!move_fully_legal(board, info, currentMove)) continue;

		if(pieceType == PIECE_TYPE_PAWN && MOVE_PROMOTE_FLAG(currentMove))
		{
			append_promote_moves(*moveArray, &moveAmount, currentMove);
		}
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

	*pointArray = create_point_array(32);
	short pointAmount = 0;

	Piece startPiece = board[piecePoint];

	for(unsigned short index = 0; index < pattAmount; index += 1)
	{
		Move currentMove = pattMoves[index];
		Piece stopPiece = move_stop_piece(currentMove, board);

		if(piece_teams_team(stopPiece, startPiece)) continue;

		if(!correct_move_flag(&currentMove, board, info)) continue;
		if(!move_fully_legal(board, info, currentMove)) continue;

		(*pointArray)[pointAmount++] = MOVE_STOP_MACRO(currentMove);
	}
	free(pattMoves); return true;
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
	if(!normal_team_exists(team)) return false;

	*moveArray = create_move_array(256);
	unsigned short moveAmount = 0;

	for(Point point = 0; point < BOARD_LENGTH; point += 1)
	{
		unsigned short currentTeam = PIECE_TEAM_MACRO(board[point]);
		if(!normal_teams_team(currentTeam, team)) continue;

		Move* addingMoves;
		if(!piece_legal_moves(&addingMoves, board, info, point)) continue;

		unsigned short addingAmount = move_array_amount(addingMoves);

		for(unsigned short index = 0; index < addingAmount; index += 1)
		{
			(*moveArray)[moveAmount++] = addingMoves[index];
		}
		free(addingMoves);
	}
	return true;
}
