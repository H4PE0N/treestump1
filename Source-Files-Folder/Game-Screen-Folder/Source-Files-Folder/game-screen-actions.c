
#include "../Header-Files-Folder/game-screen-includer.h"

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
		{ // The user did not click on any of the four promote types
			return input_screen_move(move, screen, board, info, kings, moveArray);
		}

		inputMove = ALLOC_MOVE_FLAG(inputMove, promoteFlag);
	}

	*move = inputMove;

	return true;
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

	*move = inputMove;

	return true;
}

bool input_promote_flag(Move* promoteFlag, Screen screen, unsigned short team)
{
	*promoteFlag = MOVE_FLAG_NONE;

	if(!display_promote_board(screen, team)) return false;

	Event event;

	while(!(event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT))
	{
		SDL_WaitEvent(&event);

		if(parse_quit_input(event)) return false;
	}

	Point piecePoint = parse_mouse_point(event, screen);

	parse_promote_point(promoteFlag, piecePoint);

	return true;
}

bool input_single_move(Move* move, Screen screen, const Piece board[], Info info, Kings kings, const Move moveArray[])
{
	Event event;

	Point* markPoints = create_point_array(BOARD_LENGTH);

	// The user gets to mark and draw arrows before they input their move
	while(!(event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT))
	{
		if(!SDL_WaitEvent(&event)) continue;


		if(!display_mark_board(screen, board, info, kings, moveArray, markPoints)) return false;


		if(parse_quit_input(event)) { free(markPoints); return false; }


		if(event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_RIGHT)
		{
			input_mark_parser(markPoints, screen, board, info, kings, moveArray, event);
		}
	}

	free(markPoints);

	// The user starts to input their move...
	input_move_parser(move, screen, board, info, kings, moveArray, event);

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

bool input_mark_parser(Point* markPoints, Screen screen, const Piece board[], Info info, Kings kings, const Move moveArray[], Event event)
{
	if(!(event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_RIGHT)) return false;

	Point startPoint = parse_mouse_point(event, screen);


	if(!display_mark_board(screen, board, info, kings, moveArray, markPoints)) return false;


	Event upEvent;

	while(!(upEvent.type == SDL_MOUSEBUTTONUP && upEvent.button.button == SDL_BUTTON_RIGHT))
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
	if(!(event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)) return false;

	Point startPoint = parse_mouse_point(event, screen);


	if(!display_move_board(screen, board, info, kings, moveArray, startPoint)) return false;


	Event upEvent;

	while(!(upEvent.type == SDL_MOUSEBUTTONUP && upEvent.button.button == SDL_BUTTON_LEFT))
	{
		SDL_WaitEvent(&upEvent);
	}


	Point stopPoint = parse_mouse_point(upEvent, screen);

	*move = (START_MOVE_MACRO(startPoint) | STOP_MOVE_MACRO(stopPoint));

	if(!display_chess_board(screen, board, info, kings, moveArray)) return false;

	return true;
}
