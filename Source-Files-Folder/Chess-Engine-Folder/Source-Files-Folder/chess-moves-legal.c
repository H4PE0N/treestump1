
#include "../Header-Files-Folder/engine-include-file.h"

// This function should check:
// - the move is pseudo legal
// - the own king is not set in check
bool move_fully_legal(const Piece board[], Info info, Kings kings, Move move)
{
	if(!move_inside_board(move)) return false;

	if(!move_pseudo_legal(board, info, move)) return false;

	if(!move_check_handler(board, info, kings, move)) return false;

	return true;
}

// This function should check:
// - the piece has the ability to move that way
// - the piece theoretically can move that way
// - there is not anyting that can block the piece when moving
bool move_pseudo_legal(const Piece board[], Info info, Move move)
{
	if(!move_inside_board(move)) return false;

	Piece startPiece = board[MOVE_START_MACRO(move)];


	if(!move_ability_valid(move, startPiece, info)) return false;

	if(!move_pattern_valid(move, startPiece)) return false;

	if(!move_pattern_fits(board, move)) return false;

	return true;
}

bool piece_legal_moves(Move** moveArray, const Piece board[], Info info, Kings kings, Point piecePoint)
{
	if(!point_inside_board(piecePoint)) return false;

	Move* pattMoves;
	if(!piece_pattern_moves(&pattMoves, board, piecePoint)) return false;

	unsigned short pattAmount = move_array_amount(pattMoves);

	*moveArray = create_move_array(32);
	unsigned short moveAmount = 0;

	Piece startPiece = board[piecePoint];

	for(unsigned short index = 0; index < pattAmount; index += 1)
	{
		Move currentMove = pattMoves[index];
		Piece stopPiece = board[MOVE_STOP_MACRO(currentMove)];

		if(piece_teams_team(stopPiece, startPiece)) continue;

		if(!correct_move_flag(&currentMove, startPiece, info)) continue;
		if(!move_fully_legal(board, info, kings, currentMove)) continue;

		(*moveArray)[moveAmount++] = currentMove;
	}
	free(pattMoves); return true;
}

bool team_legal_moves(Move** moveArray, const Piece board[], Info info, Kings kings, unsigned short team)
{
	if(!normal_team_exists(team)) return false;

	*moveArray = create_move_array(376);
	unsigned short moveAmount = 0;

	for(Point point = 0; point < BOARD_LENGTH; point += 1)
	{
		unsigned short currentTeam = PIECE_TEAM_MACRO(board[point]);
		if(!normal_teams_team(currentTeam, team)) continue;

		Move* addingMoves;
		if(!piece_legal_moves(&addingMoves, board, info, kings, point)) continue;

		unsigned short addingAmount = move_array_amount(addingMoves);
		//printf("Point: %d Type: %d Team: %d Amount: %d\n", point, PIECE_TYPE_MACRO(board[point]), PIECE_TEAM_MACRO(board[point]), addingAmount);

		for(unsigned short index = 0; index < addingAmount; index += 1)
		{
			(*moveArray)[moveAmount++] = addingMoves[index];
		}
		free(addingMoves);
	}
	return true;
}
