
#include "../Header-Files-Folder/screen-include-file.h"

const Uint32 BUTTON_UP = SDL_MOUSEBUTTONUP;
const Uint32 BUTTON_DOWN = SDL_MOUSEBUTTONDOWN;
const Uint8 LEFT_BUTTON = SDL_BUTTON_LEFT;
const Uint8 RIGHT_BUTTON = SDL_BUTTON_RIGHT;

const int WINDOW_CENTER = SDL_WINDOWPOS_CENTERED;
const Uint32 WINDOW_RESIZE = SDL_WINDOW_RESIZABLE;
const Uint32 WINDOW_OPENGL = SDL_WINDOW_OPENGL;
const Uint32 WINDOW_SHOWN = SDL_WINDOW_SHOWN;

const Point PROM_KNIGHT_POINT = 18;
const Point PROM_BISHOP_POINT = 21;
const Point PROM_ROOK_POINT = 42;
const Point PROM_QUEEN_POINT = 45;

const char PIECE_FOLDER[] = "../Source-Files-Folder/Game-Screen-Folder/Screen-Images-Folder";

const char WHITE_SQUARE[] = "white-square.png";
const char BLACK_SQUARE[] = "black-square.png";

const char MOVE_SQUARE[] = "move-square.png";
const char MOVED_SQUARE[] = "moved-square.png";
const char CHECK_SQUARE[] = "check-square.png";
const char MARK_SQUARE[] = "mark-square.png";

const char* TEAM_WORDS[] = {"none", "white", "black"};
const char* TYPE_WORDS[] = {"none", "pawn", "knight", "bishop", "rook", "queen", "king"};
