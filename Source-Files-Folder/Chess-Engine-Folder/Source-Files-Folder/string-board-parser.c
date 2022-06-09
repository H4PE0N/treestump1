
#include "../Header-Files-Folder/engine-include-file.h"

/*
Instead of every "parse_string_..." function having an specific info variable,
the functions may should have "info" as an argument and parse the specific variable
it self. The allocation of the specific variable should be done in the functions.
*/
bool parse_game_string(Piece** board, Info* info, Kings* kings, const char fenString[])
{
	unsigned short stringLength = strlen(fenString);

	char* stringArray[FEN_STRING_PARTS];

	if(!split_string_delim(stringArray, fenString, stringLength, FEN_STRING_DELIM, FEN_STRING_PARTS))
	{
		printf("split_string_delim\n");

		return false;
	}

	*info = INFO_BLANK;

	if(!parse_string_board(board, stringArray[0]))
	{
		printf("parse_string_board\n");

		free_array_strings(stringArray, FEN_STRING_PARTS);

		return false;
	}

	Info infoCurrentTeam = INFO_BLANK;

	if(!parse_string_current(&infoCurrentTeam, stringArray[1]))
	{
		printf("parse_string_current\n");

		free_array_strings(stringArray, FEN_STRING_PARTS);

		free(*board);

		return false;
	}


	*info = ALLOC_INFO_TEAM(*info, infoCurrentTeam);


	Info castles = INFO_BLANK;

	if(!parse_string_castles(&castles, stringArray[2]))
	{
		printf("parse_string_castles\n");

		free_array_strings(stringArray, FEN_STRING_PARTS);

		free(*board);

		return false;
	}


	*info = ALLOC_INFO_CASTLES(*info, castles);


	unsigned short passant = 0;

	if(!parse_string_passant(&passant, stringArray[3]))
	{
		printf("parse_string_passant\n");

		free_array_strings(stringArray, FEN_STRING_PARTS);

		free(*board);

		return false;
	}


	*info = ALLOC_INFO_PASSANT(*info, PASSANT_INFO_MACRO(passant));


	unsigned short turns = 0;

	if(!parse_string_turns(&turns, stringArray[4]))
	{
		printf("parse_string_turns\n");

		free_array_strings(stringArray, FEN_STRING_PARTS);

		free(*board);

		return false;
	}


	*info = ALLOC_INFO_TURNS(*info, TURNS_INFO_MACRO(turns));


	unsigned short counter = 0;

	if(!parse_string_counter(&counter, stringArray[5]))
	{
		printf("parse_string_counter\n");

		free_array_strings(stringArray, FEN_STRING_PARTS);

		free(*board);

		return false;
	}


	*info = ALLOC_INFO_COUNTER(*info, COUNTER_INFO_MACRO(counter));


	free_array_strings(stringArray, FEN_STRING_PARTS);


	if(!parse_king_points(kings, *board))
	{
		printf("if(!parse_king_points(kings, board))\n");

		free(*board);

		return false;
	}

	return true;
}

bool parse_king_points(Kings* kings, const Piece board[])
{
	Point whitePoint = board_piece_point(board, PIECE_TEAM_WHITE | PIECE_TYPE_KING);
	Point blackPoint = board_piece_point(board, PIECE_TEAM_BLACK | PIECE_TYPE_KING);

	if(whitePoint == POINT_NONE || blackPoint == POINT_NONE) return false;

	*kings = ALLOC_KINGS_WHITE(*kings, WHITE_KINGS_MACRO(whitePoint));
	*kings = ALLOC_KINGS_BLACK(*kings, BLACK_KINGS_MACRO(blackPoint));

	return true;
}

bool parse_string_current(Info* infoCurrentTeam, const char stringToken[])
{
	unsigned short stringLength = strlen(stringToken);

	if(stringLength != 1) return false;

	if(stringToken[0] == WHITE_SYMBOL) *infoCurrentTeam = INFO_TEAM_WHITE;

	else if(stringToken[0] == BLACK_SYMBOL) *infoCurrentTeam = INFO_TEAM_BLACK;

	else return false;

	return true;
}

bool parse_string_counter(unsigned short* counter, const char stringToken[])
{
	return parse_string_short(counter, stringToken);
}

bool parse_string_turns(unsigned short* turns, const char stringToken[])
{
	return parse_string_short(turns, stringToken);
}

bool parse_string_short(unsigned short* number, const char string[])
{
	unsigned short stringLength = strlen(string);

	if(stringLength < 1) return false;

	unsigned short dummyNumber = 0;

	for(unsigned short index = 0; index < stringLength; index += 1)
	{
		unsigned short value = pow(10, (stringLength - index - 1));

		signed short potentNumber = (string[index] - '0');

		if(!NUMBER_IN_BOUNDS(potentNumber, 0, 9)) return false;

		dummyNumber += (value * potentNumber);
	}
	*number = dummyNumber; return true;
}

bool parse_string_passant(unsigned short* passant, const char stringToken[])
{
	*passant = INFO_NONE;

	if(!strcmp(stringToken, FEN_PASSANT_NONE)) return true;

	Point passantPoint = POINT_NONE;
	if(!parse_string_point(&passantPoint, stringToken)) return false;

	*passant = (POINT_FILE_MACRO(passantPoint) + 1);

	return true;
}

bool parse_string_point(Point* point, const char string[])
{
	unsigned short stringLength = strlen(string);

	if(stringLength != 2) return false;

	short fileIndex = string_symbol_index(FILE_SYMBOLS, BOARD_FILES, string[0]);
	short rankIndex = string_symbol_index(RANK_SYMBOLS, BOARD_RANKS, string[1]);

	if(fileIndex == INDEX_NONE || rankIndex == INDEX_NONE) return false;

	*point = rank_file_point(rankIndex, fileIndex);

	return true;
}

bool parse_string_castles(Info* castles, const char stringToken[])
{
	*castles = INFO_NONE;

	if(!strcmp(stringToken, FEN_CASTLES_NONE)) return true;

	unsigned short stringLength = strlen(stringToken);
	if(stringLength > FEN_MAX_CASTLES) return false;

	for(unsigned short index = 0; index < stringLength; index += 1)
	{
		char symbol = stringToken[index];

		if(symbol == chess_piece_symbol(PIECE_TEAM_WHITE | PIECE_TYPE_KING))
		{
			*castles |= INFO_WHITE_KING;
		}
		else if(symbol == chess_piece_symbol(PIECE_TEAM_WHITE | PIECE_TYPE_QUEEN))
		{
			*castles |= INFO_WHITE_QUEEN;
		}
		else if(symbol == chess_piece_symbol(PIECE_TEAM_BLACK | PIECE_TYPE_KING))
		{
			*castles |= INFO_BLACK_KING;
		}
		else if(symbol == chess_piece_symbol(PIECE_TEAM_BLACK | PIECE_TYPE_QUEEN))
		{
			*castles |= INFO_BLACK_QUEEN;
		}
		else return false;
	}
	return true;
}

char chess_piece_symbol(Piece piece)
{
	Piece pieceTeam = (piece & PIECE_TEAM_MASK);
	unsigned short typeIndex = PIECE_TYPE_MACRO(piece);

	if(pieceTeam == PIECE_TEAM_WHITE) return WHITE_TYPE_SYMBOLS[typeIndex];

	else if(pieceTeam == PIECE_TEAM_BLACK) return BLACK_TYPE_SYMBOLS[typeIndex];

	return SYMBOL_NONE;
}

bool parse_string_board(Piece** board, const char stringToken[])
{
	unsigned short stringLength = strlen(stringToken);

	char* stringArray[BOARD_RANKS];

	if(!split_string_delim(stringArray, stringToken, stringLength, FEN_RANK_DELIM, BOARD_RANKS))
	{
		printf("split_string_delim\n");

		return false;
	}

	/*
	Just now: split_string_delim can return an array with less than BOARD_RANKS (8) ranks of strings.
	This must be fixed. Either the function must return exactly "amount" of strings, or it must be
	checked that there is "amount" rank strings at this exact location.
	*/

	*board = malloc(sizeof(Piece) * BOARD_LENGTH);

	for(unsigned short rank = 0; rank < BOARD_RANKS; rank += 1)
	{
		unsigned short rankLength = strlen(stringArray[rank]);

		if(!parse_board_files(board, rank, stringArray[rank], rankLength))
		{
			free(*board); free_array_strings(stringArray, BOARD_RANKS);

			return false;
		}
	}
	free_array_strings(stringArray, BOARD_RANKS); return true;
}

bool parse_board_files(Piece** board, unsigned short rank, const char rankString[], unsigned short length)
{
	unsigned short file = 0;

	for(unsigned short index = 0; index < length; index += 1)
	{
		if(file >= BOARD_FILES) return false;

		char symbol = rankString[index];

		if(!parse_board_symbol(board, rank, &file, symbol)) return false;
	}
	return true;
}

bool parse_board_symbol(Piece** board, unsigned short rank, unsigned short* file, char symbol)
{
	short potentBlanks = (symbol - '0');

	if(NUMBER_IN_BOUNDS(potentBlanks, 0, BOARD_FILES))
	{
		return parse_board_blanks(board, rank, file, potentBlanks);
	}

	Piece piece;

	if(!parse_board_piece(&piece, symbol)) return false;

	Point point = rank_file_point(rank, *file);

	(*board)[point] = piece;

	*file += 1;

	return true;
}

bool parse_board_blanks(Piece** board, unsigned short rank, unsigned short* file, unsigned short blanks)
{
	unsigned short totalFiles = (*file + blanks);

	if(totalFiles > BOARD_FILES) return false;

	for(; *file < totalFiles; *file += 1)
	{
		Point point = rank_file_point(rank, *file);

		(*board)[point] = PIECE_NONE;
	}
	return true;
}

bool parse_board_piece(Piece* piece, char symbol)
{
	for(unsigned short typeIndex = 0; typeIndex < PIECE_TYPE_SPAN; typeIndex += 1)
	{
		Piece pieceType = TYPE_PIECE_MACRO(typeIndex);

		if(symbol == WHITE_TYPE_SYMBOLS[typeIndex])
		{
			*piece = (PIECE_TEAM_WHITE | pieceType); return true;
		}
		if(symbol == BLACK_TYPE_SYMBOLS[typeIndex])
		{
			*piece = (PIECE_TEAM_BLACK | pieceType); return true;
		}
	}
	return false;
}
