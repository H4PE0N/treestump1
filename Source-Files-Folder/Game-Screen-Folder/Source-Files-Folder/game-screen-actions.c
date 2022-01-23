
#include "../Header-Files-Folder/game-screen-includer.h"

Point knightPoint = 18;
Point bishopPoint = 21;
Point rookPoint = 42;
Point queenPoint = 45;

bool input_promote_move(Move* promoMove, Screen screen, Piece pieceTeam)
{
	*promoMove = MOVE_BLANK;

	if(!render_board_squares(screen))
	{
		printf("if(!render_board_squares(screen))\n");
		return false;
	}

	if(!render_board_piece(screen, (PIECE_TYPE_KNIGHT | pieceTeam), knightPoint))
	{
		return false;
	}

	if(!render_board_piece(screen, (PIECE_TYPE_BISHOP | pieceTeam), bishopPoint))
	{
		return false;
	}

	if(!render_board_piece(screen, (PIECE_TYPE_ROOK | pieceTeam), rookPoint))
	{
		return false;
	}

	if(!render_board_piece(screen, (PIECE_TYPE_QUEEN | pieceTeam), queenPoint))
	{
		return false;
	}

	SDL_UpdateWindowSurface(screen.window);


	Event event;

	while(event.type != SDL_MOUSEBUTTONDOWN)
	{
		SDL_PollEvent(&event);
	}

	Point piecePoint = parse_mouse_point(event, screen);


	if(piecePoint == knightPoint)
	{
		*promoMove = ALLOC_MOVE_FLAG(*promoMove, MOVE_FLAG_KNIGHT);
	}
	else if(piecePoint == bishopPoint)
	{
		*promoMove = ALLOC_MOVE_FLAG(*promoMove, MOVE_FLAG_BISHOP);
	}
	else if(piecePoint == rookPoint)
	{
		*promoMove = ALLOC_MOVE_FLAG(*promoMove, MOVE_FLAG_ROOK);
	}
	else if(piecePoint == queenPoint)
	{
		*promoMove = ALLOC_MOVE_FLAG(*promoMove, MOVE_FLAG_QUEEN);
	}
	else return false;


	return true;
}
