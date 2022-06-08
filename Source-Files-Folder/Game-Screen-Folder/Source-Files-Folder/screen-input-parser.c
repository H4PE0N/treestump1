
#include "../Header-Files-Folder/screen-include-file.h"

bool parse_quit_input(Event event)
{
  bool keypress = (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_q);
  bool quitIcon = (event.type == SDL_QUIT);

  return keypress || quitIcon;
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

bool mouse_event_check(Event event, Uint8 buttonSide, Uint32 buttonMove)
{
	return (event.type == buttonMove && event.button.button == buttonSide);
}

bool board_point_position(Rect* position, Screen screen, Point point)
{
	if(!point_inside_board(point)) return false;

	unsigned short rank = POINT_RANK_MACRO(point);
	unsigned short file = POINT_FILE_MACRO(point);

	float squareWidth = (screen.width / BOARD_FILES);
	float squareHeight = (screen.height / BOARD_RANKS);

	float realHeight = squareHeight * rank;
	float realWidth = squareWidth * file;

	*position = (Rect) {realWidth, realHeight, squareWidth, squareHeight};

	return true;
}

Point parse_mouse_point(Event event, Screen screen)
{
	float squareWidth = (screen.width / BOARD_FILES);
	float squareHeight = (screen.height / BOARD_RANKS);

	unsigned short file = (unsigned short) floor( (float) event.motion.x / squareWidth);
	unsigned short rank = (unsigned short) floor( (float) event.motion.y / squareHeight);

	if(!NUMBER_IN_BOUNDS(file, 0, BOARD_FILES)) return POINT_NONE;

	if(!NUMBER_IN_BOUNDS(rank, 0, BOARD_RANKS)) return POINT_NONE;

	Point point = FILE_POINT_MACRO(file) | RANK_POINT_MACRO(rank);

	return point;
}
