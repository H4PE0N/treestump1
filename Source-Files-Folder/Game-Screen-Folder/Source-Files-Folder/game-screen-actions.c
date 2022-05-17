
#include "../Header-Files-Folder/game-screen-includer.h"

Point knightPoint = 18;
Point bishopPoint = 21;
Point rookPoint = 42;
Point queenPoint = 45;

bool render_promote_board(Screen screen, unsigned short team)
{
	Piece pieceTeam = TEAM_PIECE_MACRO(team);

	if(!render_board_squares(screen)) return false;

	if(!render_board_piece(screen, (PIECE_TYPE_KNIGHT | pieceTeam), knightPoint)) return false;

	if(!render_board_piece(screen, (PIECE_TYPE_BISHOP | pieceTeam), bishopPoint)) return false;

	if(!render_board_piece(screen, (PIECE_TYPE_ROOK | pieceTeam), rookPoint)) return false;

	if(!render_board_piece(screen, (PIECE_TYPE_QUEEN | pieceTeam), queenPoint)) return false;

	return true;
}

bool display_promote_board(Screen screen, unsigned short team)
{
	SDL_RenderClear(screen.render);

	if(!render_promote_board(screen, team)) return false;

	SDL_RenderPresent(screen.render);

	return true;
}

bool input_promote_move(Move* promoMove, Screen screen, unsigned short team)
{
	if(!display_promote_board(screen, team))
	{
		printf("Could not display_promote_board\n");

		return false;
	}

	*promoMove = MOVE_BLANK;


	Event event;

	while(event.type != SDL_MOUSEBUTTONDOWN)
	{
		SDL_WaitEvent(&event);
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
