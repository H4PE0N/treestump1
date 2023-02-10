
#include "../Header-Files-Folder/console-include-file.h"

char console_piece_symbol(Piece piece)
{
	Piece pieceTeam = (piece & PIECE_TEAM_MASK);
	unsigned short typeIndex = PIECE_TYPE_MACRO(piece);

	if(pieceTeam == PIECE_TEAM_WHITE) return WHITE_CON_SYMBOLS[typeIndex];
	if(pieceTeam == PIECE_TEAM_BLACK) return BLACK_CON_SYMBOLS[typeIndex];

	return CON_SYMBOL_NONE;
}

bool print_console_board(const Piece board[])
{
	for(Point point = 0; point < BOARD_POINTS; point += 1)
	{
    unsigned short rank = POINT_RANK_MACRO(point);
    unsigned short file = POINT_FILE_MACRO(point);

    char symbol = console_piece_symbol(board[point]);

    if(file == 0) printf("%d ", BOARD_RANKS - rank);

    if(file == 7) printf("%c\n", symbol);
    else printf("%c ", symbol);
	}
  printf("  A B C D E F G H\n"); return true;
}

bool print_console_state(State state)
{
	unsigned short team = STATE_CURRENT_MACRO(state);
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
