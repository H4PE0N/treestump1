
#include "../Header-Files-Folder/englog-include-file.h"

const char WHITE_TYPE_SYMBOLS[] = {'\0', 'P', 'N', 'B', 'R', 'Q', 'K'};
const char BLACK_TYPE_SYMBOLS[] = {'\0', 'p', 'n', 'b', 'r', 'q', 'k'};

const char WHITE_MOVE_SYMBOLS[] = {'\0', '\0', 'N', 'B', 'R', 'Q', 'K'};
const char BLACK_MOVE_SYMBOLS[] = {'\0', '\0', 'n', 'b', 'r', 'q', 'k'};

const char RANK_SYMBOLS[] = {'8', '7', '6', '5', '4', '3', '2', '1'};
const char FILE_SYMBOLS[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};

const char WHITE_SYMBOL = 'w';
const char BLACK_SYMBOL = 'b';

const char SYMBOL_NONE = '\0';

const char FEN_STRING_DELIM[] = " ";
const char FEN_RANK_DELIM[] = "/";

const unsigned short FEN_STRING_PARTS = 6;
const unsigned short FEN_MAX_CASTLES = 4;

const char FEN_PASSANT_NONE[] = "-";
const char FEN_CASTLES_NONE[] = "-";

const char* TEAM_WORDS[] = {"none", "white", "black"};
const char* TYPE_WORDS[] = {"none", "pawn", "knight", "bishop", "rook", "queen", "king"};

const char FEN_START_STRING[] = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 1 0";
