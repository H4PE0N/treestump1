
#include "../Header-Files-Folder/screen-include-file.h"

const Point PROM_KNIGHT_POINT = 0b010010;
const Point PROM_BISHOP_POINT = 0b010101;
const Point PROM_ROOK_POINT = 0b101010;
const Point PROM_QUEEN_POINT = 0b101101;

const char IMAGES_FOLDER[] = "../Source-Files-Folder/Game-Screen-Folder/Screen-Images-Folder";

const char WHITE_SQUARE_FILE[] = "white-square.png";
const char BLACK_SQUARE_FILE[] = "black-square.png";

const char MOVE_SQUARE_FILE[] = "move-square.png";
const char MOVED_SQUARE_FILE[] = "moved-square.png";
const char CHECK_SQUARE_FILE[] = "check-square.png";
const char MARK_SQUARE_FILE[] = "mark-square.png";

const char* TEAM_WORDS[] = {"none", "white", "black"};
const char* TYPE_WORDS[] = {"none", "pawn", "knight", "bishop", "rook", "queen", "king"};
