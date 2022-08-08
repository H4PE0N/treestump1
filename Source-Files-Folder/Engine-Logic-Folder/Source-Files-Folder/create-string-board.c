
#include "../Header-Files-Folder/englog-include-file.h"

bool create_game_string(char** string, const Piece board[], Info info)
{
	*string = create_char_string(128);

	char* stringArray[FEN_STRING_PARTS];
	alloc_array_strings(stringArray, FEN_STRING_PARTS, 72);

	if(!create_string_board(stringArray[0], board))
	{
		free_array_strings(stringArray, FEN_STRING_PARTS);

		free(*string);

		return false;
	}

	if(!create_string_info(stringArray, info))
	{
		free_array_strings(stringArray, FEN_STRING_PARTS);

		free(*string);

		return false;
	}

	merge_string_delim(*string, stringArray, FEN_STRING_PARTS, FEN_STRING_DELIM);

	free_array_strings(stringArray, FEN_STRING_PARTS);

	return true;
}

bool create_string_info(char* stringArray[], Info info)
{
	if(!create_string_current(stringArray[1], info)) return false;

	if(!create_string_castles(stringArray[2], info)) return false;

	if(!create_string_passant(stringArray[3], info)) return false;

	if(!create_string_counter(stringArray[4], info)) return false;

	if(!create_string_turns(stringArray[5], info)) return false;

	return true;
}

bool create_string_counter(char* string, Info info)
{
	sprintf(string, "%d", INFO_COUNTER_MACRO(info));

	return true;
}

bool create_string_turns(char* string, Info info)
{
	sprintf(string, "%d", INFO_TURNS_MACRO(info));

	return true;
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
	if(MASK_WHITE_KSIDE(info))
	{
		char symbol = chess_piece_symbol(PIECE_TEAM_WHITE | PIECE_TYPE_KING);
		strncat(string, &symbol, 1);
	}
	if(MASK_WHITE_QSIDE(info))
	{
		char symbol = chess_piece_symbol(PIECE_TEAM_WHITE | PIECE_TYPE_QUEEN);
		strncat(string, &symbol, 1);
	}
	if(MASK_BLACK_KSIDE(info))
	{
		char symbol = chess_piece_symbol(PIECE_TEAM_BLACK | PIECE_TYPE_KING);
		strncat(string, &symbol, 1);
	}
	if(MASK_BLACK_QSIDE(info))
	{
		char symbol = chess_piece_symbol(PIECE_TEAM_BLACK | PIECE_TYPE_QUEEN);
		strncat(string, &symbol, 1);
	}
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

	for(unsigned short rank = 0; rank < BOARD_RANKS; rank += 1)
	{
		if(!create_board_files(stringArray[rank], board, rank))
		{
			free_array_strings(stringArray, BOARD_RANKS);

			return false;
		}
	}

	merge_string_delim(string, stringArray, BOARD_RANKS, FEN_RANK_DELIM);

	free_array_strings(stringArray, BOARD_RANKS);

	return true;
}

bool create_board_files(char* string, const Piece board[], unsigned short rank)
{
	for(unsigned short file = 0; file < BOARD_FILES; file += 1)
	{
		Point point = RANK_FILE_POINT(rank, file);

		if(chess_piece_exists(board[point]))
		{
			char symbol = chess_piece_symbol(board[point]);

			if(symbol == SYMBOL_NONE) return false;

			strncat(string, &symbol, 1);
		}
		else
		{
			char symbol;

			if(!create_blank_symbol(&symbol, rank, &file, board)) return false;

			strncat(string, &symbol, 1);
		}
	}
	return true;
}

bool create_blank_symbol(char* symbol, unsigned short rank, unsigned short* file, const Piece board[])
{
	short blanks = 0;

	for(; (*file + blanks) < BOARD_FILES; blanks += 1)
	{
		Point point = RANK_FILE_POINT(rank, (*file + blanks));

		if(chess_piece_exists(board[point])) break;
	}
	*file += (blanks - 1); *symbol = (blanks + '0');

	return true;
}

bool create_string_point(char* string, Point point)
{
	if(!POINT_INSIDE_BOARD(point)) return false;

	unsigned short rankIndex = POINT_RANK_MACRO(point);
	unsigned short fileIndex = POINT_FILE_MACRO(point);

	sprintf(string, "%c%c", FILE_SYMBOLS[fileIndex], RANK_SYMBOLS[rankIndex]);

	return true;
}

bool create_string_move(char* string, Move move)
{
	if(!move_inside_board(move)) return false;

	Point startPoint = MOVE_START_MACRO(move);
	Point stopPoint = MOVE_STOP_MACRO(move);

	char startString[16], stopString[16];

	if(!create_string_point(startString, startPoint)) return false;
	if(!create_string_point(stopString, stopPoint)) return false;

	if(MOVE_PROMOTE_FLAG(move))
	{
		char typeSymbol = 'q'; // THIS MUST BE CHANGED TO THE SPECIFIC TYPE!
		sprintf(string, "%s%s%c", startString, stopString, typeSymbol);
	}
	else sprintf(string, "%s%s", startString, stopString);

	return true;
}
