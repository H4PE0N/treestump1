
#include "../Header-Files-Folder/screen-include-file.h"

bool input_screen_move(Move* move, Screen screen, const Piece board[], Info info, Kings kings, const Move moveArray[])
{
	Move inputMove = MOVE_NONE;

	if(!input_legal_move(&inputMove, screen, board, info, kings, moveArray)) return false;

	unsigned short startTeam = PIECE_TEAM_MACRO(board[MOVE_START_MACRO(inputMove)]);
	Piece startPieceType = (board[MOVE_START_MACRO(inputMove)] & PIECE_TYPE_MASK);

	if(startPieceType == PIECE_TYPE_PAWN && promote_pattern_valid(inputMove, startTeam))
	{
		Move promoteFlag = MOVE_FLAG_NONE;

		if(!input_promote_flag(&promoteFlag, screen, startTeam)) return false;

		if(promoteFlag == MOVE_FLAG_NONE)
			return input_screen_move(move, screen, board, info, kings, moveArray);

		inputMove = ALLOC_MOVE_FLAG(inputMove, promoteFlag);
	}
	*move = inputMove; return true;
}

bool input_legal_move(Move* move, Screen screen, const Piece board[], Info info, Kings kings, const Move moveArray[])
{
	Move inputMove = MOVE_NONE;

	while(!move_fully_legal(board, info, kings, inputMove))
	{
		if(!input_single_move(&inputMove, screen, board, info, kings, moveArray)) return false;

		if(!move_inside_board(inputMove)) continue;

		Piece startPiece = board[MOVE_START_MACRO(inputMove)];
		unsigned short startTeam = PIECE_TEAM_MACRO(startPiece);

		if(!current_team_move(info, startTeam)) continue;

		if(!correct_move_flag(&inputMove, startPiece, info)) continue;
	}
	*move = inputMove; return true;
}

bool input_promote_flag(Move* promoteFlag, Screen screen, unsigned short team)
{
	*promoteFlag = MOVE_FLAG_NONE;

	if(!display_promote_board(screen, team)) return false;

	Event event;
	while(!mouse_event_check(event, LEFT_BUTTON, BUTTON_DOWN))
	{
		SDL_WaitEvent(&event);

		if(parse_quit_input(event)) return false;
	}
	Point piecePoint = parse_mouse_point(event, screen);

	parse_promote_point(promoteFlag, piecePoint); return true;
}

bool input_single_move(Move* move, Screen screen, const Piece board[], Info info, Kings kings, const Move moveArray[])
{
	Point* markPoints = create_point_array(BOARD_LENGTH);

	Event event;
	while(!mouse_event_check(event, LEFT_BUTTON, BUTTON_DOWN))
	{
		if(!SDL_WaitEvent(&event)) continue;

		if(!display_mark_board(screen, board, info, kings, moveArray, markPoints)) return false;

		if(parse_quit_input(event)) { free(markPoints); return false; }

		if(mouse_event_check(event, RIGHT_BUTTON, BUTTON_DOWN))
		{
			input_mark_parser(markPoints, screen, board, info, kings, moveArray, event);
		}
	}
	free(markPoints);

	input_move_parser(move, screen, board, info, kings, moveArray, event);

	return true;
}

bool input_mark_parser(Point* markPoints, Screen screen, const Piece board[], Info info, Kings kings, const Move moveArray[], Event event)
{
	if(!mouse_event_check(event, RIGHT_BUTTON, BUTTON_DOWN)) return false;

	Point startPoint = parse_mouse_point(event, screen);

	if(!display_mark_board(screen, board, info, kings, moveArray, markPoints)) return false;

	Event upEvent;
	while(!mouse_event_check(upEvent, RIGHT_BUTTON, BUTTON_UP))
	{
		SDL_WaitEvent(&upEvent);
	}

	// If the square you pressed down on, are not the one you released on:
	// This means that you have tried to create an arrow, instead of marking
	if(startPoint != parse_mouse_point(upEvent, screen)) return false;


	// ====== THIS IS WHERE THE MARKING IS HANDLED ===============================

	unsigned short amount = point_array_amount(markPoints);

	signed short pointIndex = array_point_index(markPoints, amount, startPoint);

	// If the point you marked is not already marked -> add it to the list
	if(pointIndex == -1) markPoints[amount] = startPoint;

	// If the point is already marked -> delete it from the list
	else delete_array_point(markPoints, amount, pointIndex);


	if(!display_mark_board(screen, board, info, kings, moveArray, markPoints)) return false;

	return true;
}

bool input_move_parser(Move* move, Screen screen, const Piece board[], Info info, Kings kings, const Move moveArray[], Event event)
{
	if(!mouse_event_check(event, LEFT_BUTTON, BUTTON_DOWN)) return false;

	Point startPoint = parse_mouse_point(event, screen);

	if(!display_move_board(screen, board, info, kings, moveArray, startPoint)) return false;

	Event upEvent;
	while(!mouse_event_check(upEvent, LEFT_BUTTON, BUTTON_UP))
	{
		SDL_WaitEvent(&upEvent);
	}
	Point stopPoint = parse_mouse_point(upEvent, screen);

	*move = (START_MOVE_MACRO(startPoint) | STOP_MOVE_MACRO(stopPoint));

	if(!display_chess_board(screen, board, info, kings, moveArray)) return false;

	return true;
}
