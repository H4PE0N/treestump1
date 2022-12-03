
#include "../Header-Files-Folder/screen-include-file.h"

bool parse_quit_input(Event event)
{
  bool keypress = key_event_check(event, SDLK_q, SDL_KEYDOWN);

  return (keypress || (event.type == SDL_QUIT));
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

bool mouse_event_check(Event event, Uint8 buttonSide, Uint32 eventType)
{
	return ((event.type == eventType) && (event.button.button == buttonSide));
}

bool key_event_check(Event event, int keyCode, Uint32 eventType)
{
  return ((event.type == eventType) && (event.key.keysym.sym == keyCode));
}

bool screen_event_check(Event event, int windowEvent, Uint32 eventType)
{
  return ((event.type == eventType) && (event.window.event == windowEvent));
}

bool board_point_position(Rect* position, Screen screen, Point point)
{
	if(!POINT_INSIDE_BOARD(point)) return false;

  Point renderPoint = check_inverted_point(point, screen.inverted);

	unsigned short rank = POINT_RANK_MACRO(renderPoint);
	unsigned short file = POINT_FILE_MACRO(renderPoint);

  Rect boardRect = board_screen_position(screen.width, screen.height);

  float squareWidth = (boardRect.w / BOARD_FILES);
  float squareHeight = (boardRect.h / BOARD_RANKS);

	float realHeight = (boardRect.y + squareHeight * rank);
	float realWidth = (boardRect.x + squareWidth * file);

	*position = (Rect) {realWidth, realHeight, squareWidth, squareHeight};

	return true;
}

Rect board_screen_position(int screenWidth, int screenHeight)
{
  float boardLength = MIN_NUMBER_VALUE(screenWidth, screenHeight);

  float blankWidth = ((screenWidth - boardLength) / 2);
  float blankHeight = ((screenHeight - boardLength) / 2);

  return (Rect) {blankWidth, blankHeight, boardLength, boardLength};
}

Point parse_mouse_point(Event event, Screen screen)
{
  Rect boardRect = board_screen_position(screen.width, screen.height);

  float squareWidth = (boardRect.w / BOARD_FILES);
  float squareHeight = (boardRect.h / BOARD_RANKS);

  int file = floor((event.motion.x - boardRect.x) / squareWidth);
  int rank = floor((event.motion.y - boardRect.y) / squareHeight);

  if(!FILE_INSIDE_BOARD(file)) return POINT_NONE;
  if(!RANK_INSIDE_BOARD(rank)) return POINT_NONE;

  Point point = RANK_FILE_POINT(rank, file);

  return check_inverted_point(point, screen.inverted);
}

Point check_inverted_point(Point point, bool inverted)
{
  return (inverted ? (BOARD_LENGTH - 1 - point) : point);
}
