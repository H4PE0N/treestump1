
#include "../Header-Files-Folder/screen-include-file.h"

bool input_screen_move(Move* move, Screen* screen, const Piece board[], State state, const Move moveArray[])
{
	Move inputMove = MOVE_NONE;
	if(!input_legal_move(&inputMove, screen, board, state, moveArray)) return false;

	if(MOVE_PROMOTE_FLAG(inputMove))
	{
		uint8_t startTeam = MOVE_START_TEAM(board, inputMove);

		Move promoteFlag = MOVE_FLAG_NONE;
		if(!input_promote_flag(&promoteFlag, screen, startTeam)) return false;

		if(promoteFlag == MOVE_FLAG_NONE)
			return input_screen_move(move, screen, board, state, moveArray);

		inputMove = ALLOC_MOVE_FLAG(inputMove, promoteFlag);
	}
	*move = inputMove; return true;
}

bool print_console_state(State state)
{
	uint8_t team = STATE_CURRENT_MACRO(state);
	if(!NORMAL_TEAM_EXISTS(team)) return false;

	printf("current team:(%s)\n", TEAM_WORDS[team]);

	printf("turns:(%d)\n", STATE_TURNS_MACRO(state));

	printf("clock:(%d)\n", STATE_CLOCK_MACRO(state));

	char passantString[16];
	memset(passantString, '\0', sizeof(passantString));

	Point passantPoint = passant_pawn_point(state);
	if(!create_string_point(passantString, passantPoint))
	{
		strcpy(passantString, "none");
	}
	printf("passant:(%s)\n", passantString);

	return true;
}

bool input_legal_move(Move* move, Screen* screen, const Piece board[], State state, const Move moveArray[])
{
	Move inputMove = MOVE_NONE;

	while(!move_fully_legal(board, state, inputMove))
	{
		print_console_state(state);

		if(!input_single_move(&inputMove, screen, board, state, moveArray)) return false;

		if(!MOVE_INSIDE_BOARD(inputMove)) continue;

		uint8_t startTeam = MOVE_START_TEAM(board, inputMove);
		if(!current_team_move(state, startTeam)) continue;

		if(!correct_move_flag(&inputMove, board, state)) continue;
	}
	*move = inputMove; return true;
}

bool input_promote_flag(Move* promoteFlag, Screen* screen, uint8_t team)
{
	*promoteFlag = MOVE_FLAG_NONE;

	bool inverted = screen->inverted; screen->inverted = false;

	bool result = input_promote_flagX(promoteFlag, screen, team);

	screen->inverted = inverted; return result;
}

bool input_promote_flagX(Move* promoteFlag, Screen* screen, uint8_t team)
{
	if(!display_promote_board(*screen, team)) return false;

	Event event;
	while(!mouse_event_check(event, LEFT_BUTTON, BUTTON_DOWN))
	{
		SDL_WaitEvent(&event);

		if(parse_quit_input(event)) return false;
	}
	Point piecePoint = parse_mouse_point(event, *screen);

	parse_promote_point(promoteFlag, piecePoint); return true;
}

bool input_single_move(Move* move, Screen* screen, const Piece board[], State state, const Move moveArray[])
{
	Point markPoints[BOARD_POINTS];
	memset(markPoints, POINT_NONE, sizeof(Point) * BOARD_POINTS);

	Event event;
	do {
		if(!SDL_WaitEvent(&event)) continue;

		if(!display_mark_board(*screen, board, state, moveArray, markPoints)) return false;

		if(parse_quit_input(event)) return false;


		if(mouse_event_check(event, RIGHT_BUTTON, BUTTON_DOWN))
			input_mark_parser(markPoints, *screen, board, state, moveArray, event);

		if(key_event_check(event, SDLK_SPACE, SDL_KEYDOWN))
			invert_screen_parser(screen, event);

		else if(screen_event_check(event, SDL_WINDOWEVENT_RESIZED, SDL_WINDOWEVENT))
  		resize_window_parser(screen, event);
	}
	while(!mouse_event_check(event, LEFT_BUTTON, BUTTON_DOWN));

	input_move_parser(move, *screen, board, state, moveArray, event);

	return true;
}

bool invert_screen_parser(Screen* screen, Event event)
{
	if(!key_event_check(event, SDLK_SPACE, SDL_KEYDOWN)) return false;

	screen->inverted = !(screen->inverted); return true;
}

bool resize_window_parser(Screen* screen, Event event)
{
	if(!screen_event_check(event, SDL_WINDOWEVENT_RESIZED, SDL_WINDOWEVENT)) return false;

	SDL_SetWindowSize(screen->window, event.window.data1, event.window.data2);

	screen->width = event.window.data1; screen->height = event.window.data2;
	return true;
}

bool input_mark_parser(Point* markPoints, Screen screen, const Piece board[], State state, const Move moveArray[], Event event)
{
	if(!mouse_event_check(event, RIGHT_BUTTON, BUTTON_DOWN)) return false;

	if(!display_mark_board(screen, board, state, moveArray, markPoints)) return false;

	Event upEvent;
	while(!mouse_event_check(upEvent, RIGHT_BUTTON, BUTTON_UP))
		SDL_WaitEvent(&upEvent);

	// If the square you pressed down on, are not the one you released on:
	// This means that you have tried to create an arrow, instead of marking
	Point startPoint = parse_mouse_point(event, screen);

	if(startPoint != parse_mouse_point(upEvent, screen)) return false;

	// ====== THIS IS WHERE THE MARKING IS HANDLED ===============================

	int amount = point_array_amount(markPoints);

	int pointIndex = array_point_index(markPoints, amount, startPoint);

	// If the point you marked is not already marked -> add it to the list
	if(pointIndex == INDEX_NONE) markPoints[amount] = startPoint;

	// If the point is already marked -> delete it from the list
	else delete_array_point(markPoints, amount, pointIndex);


	if(!display_mark_board(screen, board, state, moveArray, markPoints)) return false;

	return true;
}

bool input_move_parser(Move* move, Screen screen, const Piece board[], State state, const Move moveArray[], Event event)
{
	if(!mouse_event_check(event, LEFT_BUTTON, BUTTON_DOWN)) return false;

	Point startPoint = parse_mouse_point(event, screen);

	if(!display_move_board(screen, board, state, moveArray, startPoint)) return false;

	Event upEvent;
	while(!mouse_event_check(upEvent, LEFT_BUTTON, BUTTON_UP))
		SDL_WaitEvent(&upEvent);

	Point stopPoint = parse_mouse_point(upEvent, screen);

	*move = START_STOP_MOVE(startPoint, stopPoint);

	if(!display_chess_board(screen, board, state, moveArray)) return false;

	return true;
}
