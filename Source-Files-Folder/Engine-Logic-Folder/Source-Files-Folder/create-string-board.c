
#include "../Header-Files-Folder/englog-include-file.h"

bool create_fen_string(char* fenString, const Piece board[], Info info)
{
	char* stringArray[FEN_STRING_PARTS];
	alloc_array_strings(stringArray, FEN_STRING_PARTS, 72);

	bool result = create_fen_string_t(fenString, stringArray, board, info);

	free_array_strings(stringArray, FEN_STRING_PARTS);

	return result;
}

bool create_fen_string_t(char* fenString, char** stringArray, const Piece board[], Info info)
{
	if(!create_fenstr_parts(stringArray, board, info)) return false;

	merge_string_delim(fenString, stringArray, FEN_STRING_PARTS, FEN_STRING_DELIM);

	return true;
}

bool create_fenstr_parts(char* stringArray[], const Piece board[], Info info)
{
	if(!create_string_board(stringArray[0], board)) return false;

	if(!create_string_current(stringArray[1], info)) return false;

	if(!create_string_castles(stringArray[2], info)) return false;

	if(!create_string_passant(stringArray[3], info)) return false;

	if(!create_string_counter(stringArray[4], info)) return false;

	if(!create_string_turns(stringArray[5], info)) return false;

	return true;
}

bool create_string_counter(char* string, Info info)
{
	return sprintf(string, "%d", INFO_COUNTER_MACRO(info));
}

bool create_string_turns(char* string, Info info)
{
	return sprintf(string, "%d", INFO_TURNS_MACRO(info));
}

bool create_string_passant(char* string, Info info)
{
	Point pawnPoint = passant_pawn_point(info);

	if(pawnPoint != POINT_NONE)
	{
		char passantString[16];
		if(!create_point_string(passantString, pawnPoint)) return false;

		strcat(string, passantString);
	}
	else strcpy(string, FEN_PASSANT_NONE);

	return true;
}

bool create_string_castles(char* string, Info info)
{
	if(MASK_WHITE_KSIDE(info)) strncat(string, &(FEN_WKING_SYMBOL), 1);

	if(MASK_WHITE_QSIDE(info)) strncat(string, &(FEN_WQUEEN_SYMBOL), 1);

	if(MASK_BLACK_KSIDE(info)) strncat(string, &(FEN_BKING_SYMBOL), 1);

	if(MASK_BLACK_QSIDE(info)) strncat(string, &(FEN_BQUEEN_SYMBOL), 1);

	if(strlen(string) == 0) strcpy(string, FEN_CASTLES_NONE);

	return true;
}

bool create_string_current(char* string, Info info)
{
	if(INFO_TEAM_MACRO(info) == TEAM_WHITE) string[0] = WHITE_SYMBOL;

	else if(INFO_TEAM_MACRO(info) == TEAM_BLACK) string[0] = BLACK_SYMBOL;

	else return false;

	return true;
}

bool create_string_board(char* string, const Piece board[])
{
	char* stringArray[BOARD_RANKS];
	alloc_array_strings(stringArray, BOARD_RANKS, BOARD_FILES);

	bool result = create_string_board_t(string, stringArray, board);

	free_array_strings(stringArray, BOARD_RANKS); return result;
}

bool create_string_board_t(char* string, char** stringArray, const Piece board[])
{
	for(uint8_t rank = 0; rank < BOARD_RANKS; rank += 1)
		if(!create_board_files(stringArray[rank], board, rank)) return false;

	merge_string_delim(string, stringArray, BOARD_RANKS, FEN_RANK_DELIM);

	return true;
}

bool create_board_files(char* string, const Piece board[], uint8_t rank)
{
	for(uint8_t file = 0; file < BOARD_FILES; file += 1)
	{
		Point point = RANK_FILE_POINT(rank, file);

		if(BOARD_POINT_EXISTS(board, point))
		{
			if(!append_piece_symbol(string, board, point)) return false;
		}
		else if(!append_blank_symbol(string, board, rank, &file)) return false;
	}
	return true;
}

bool append_piece_symbol(char* string, const Piece board[], Point point)
{
	char symbol = chess_piece_symbol(board[point]);

	if(symbol == SYMBOL_NONE) return false;

	strncat(string, &symbol, 1); return true;
}

bool append_blank_symbol(char* string, const Piece board[], uint8_t rank, uint8_t* file)
{
	char symbol;
	if(!create_blank_symbol(&symbol, rank, file, board)) return false;

	strncat(string, &symbol, 1); return true;
}

bool create_blank_symbol(char* symbol, uint8_t rank, uint8_t* file, const Piece board[])
{
	uint8_t blanks = 0;

	for(; (*file + blanks) < BOARD_FILES; blanks += 1)
	{
		Point point = RANK_FILE_POINT(rank, (*file + blanks));

		if(BOARD_POINT_EXISTS(board, point)) break;
	}
	*file += (blanks - 1); *symbol = (blanks + '0');

	return true;
}

bool create_string_point(char* string, Point point)
{
	if(!POINT_INSIDE_BOARD(point)) return false;

	uint8_t rankIndex = POINT_RANK_MACRO(point);
	uint8_t fileIndex = POINT_FILE_MACRO(point);

	sprintf(string, "%c%c", FILE_SYMBOLS[fileIndex], RANK_SYMBOLS[rankIndex]);

	return true;
}

bool create_string_move(char* string, Move move)
{
	if(!MOVE_INSIDE_BOARD(move)) return false;

	Point startPoint = MOVE_START_MACRO(move);
	Point stopPoint = MOVE_STOP_MACRO(move);

	char startString[16], stopString[16];

	if(!create_string_point(startString, startPoint)) return false;
	if(!create_string_point(stopString, stopPoint)) return false;

	if(MOVE_PROMOTE_FLAG(move))
	{
		char pieceSymbol;
		if(!promote_piece_symbol(&pieceSymbol, move)) return false;

		sprintf(string, "%s%s%c", startString, stopString, pieceSymbol);
	}
	else sprintf(string, "%s%s", startString, stopString);

	return true;
}

bool promote_piece_symbol(char* symbol, Move move)
{
	if(MOVE_STORE_FLAG(move, MOVE_FLAG_KNIGHT)) *symbol = KNIGHT_PROM_SYMBOL;

	else if(MOVE_STORE_FLAG(move, MOVE_FLAG_BISHOP)) *symbol = BISHOP_PROM_SYMBOL;

	else if(MOVE_STORE_FLAG(move, MOVE_FLAG_ROOK)) *symbol = ROOK_PROM_SYMBOL;

	else if(MOVE_STORE_FLAG(move, MOVE_FLAG_QUEEN)) *symbol = QUEEN_PROM_SYMBOL;

	else return false;

	return true;
}
