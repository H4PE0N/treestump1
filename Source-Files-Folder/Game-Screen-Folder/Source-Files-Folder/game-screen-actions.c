
#include "../Header-Files-Folder/game-screen-includer.h"

bool input_promote_flag(Move* promoteFlag, Screen screen, unsigned short team)
{
	*promoteFlag = MOVE_FLAG_NONE;

	if(!display_promote_board(screen, team))
	{
		printf("Could not display_promote_board\n");

		return false;
	}

	Event event;

	while(event.type != SDL_MOUSEBUTTONDOWN)
	{
		SDL_WaitEvent(&event);

		if(parse_quit_input(event)) return false;
	}

	Point piecePoint = parse_mouse_point(event, screen);

	return parse_promote_point(promoteFlag, piecePoint);
}

bool input_screen_move(Move* move, Screen screen, const Piece board[], Info info, Kings kings, const Move moves[])
{
	Move inputMove = MOVE_NONE;
	Event event;

	Point markPoints[BOARD_LENGTH + 1];

	for(int index = 0; index < (BOARD_LENGTH + 1); index += 1)
	{
		markPoints[index] = POINT_NONE;
	}

	while(!move_inside_board(inputMove))
	{
		if(!display_input_board(screen, board, info, kings, moves, markPoints, -1)) return false;


		if(!SDL_WaitEvent(&event)) continue;

		if(parse_quit_input(event)) return false;


		screen_input_parser(&inputMove, markPoints, screen, board, info, kings, moves, event);
	}

	*move = inputMove;

	return true;
}

bool screen_input_parser(Move* move, Point* markPoints, Screen screen, const Piece board[], Info info, Kings kings, const Move moves[], Event event)
{
	if(event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
	{
		return input_move_parser(move, screen, board, info, kings, moves, event);
	}
	else if(event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_RIGHT)
	{
		input_mark_parser(markPoints, screen, event);
	}
	return false;
}

bool input_mark_parser(Point* markPoints, Screen screen, Event event)
{
	if(!(event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_RIGHT)) return false;

	Point point = parse_mouse_point(event, screen);

	unsigned short amount = point_array_amount(markPoints);

	signed short pointIndex = array_point_index(markPoints, amount, point);

	if(pointIndex == -1) markPoints[amount] = point;

	else delete_array_point(markPoints, amount, pointIndex);

	return true;
}

bool parse_promote_point(Move* promoteFlag, Point point)
{
	if(point == PROM_KNIGHT_POINT) *promoteFlag = MOVE_FLAG_KNIGHT;

	else if(point == PROM_BISHOP_POINT) *promoteFlag = MOVE_FLAG_BISHOP;

	else if(point == PROM_ROOK_POINT) *promoteFlag = MOVE_FLAG_ROOK;

	else if(point == PROM_QUEEN_POINT) *promoteFlag = MOVE_FLAG_QUEEN;

	else return false;

	return true;
}

bool input_move_parser(Move* move, Screen screen, const Piece board[], Info info, Kings kings, const Move moves[], Event event)
{
	if(!(event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)) return false;

	Point startPoint = parse_mouse_point(event, screen);


	if(!display_chess_board(screen, board, info, kings, moves, startPoint)) return false;


	Event upEvent;

	while(!(upEvent.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT))
	{
		SDL_WaitEvent(&upEvent);
	}


	Point stopPoint = parse_mouse_point(upEvent, screen);

	*move = (START_MOVE_MACRO(startPoint) | STOP_MOVE_MACRO(stopPoint));

	return true;
}
