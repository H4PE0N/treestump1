
#include "../Header-Files-Folder/engine-include-file.h"

bool parse_game_string(Piece** board, Info* info, const char fenString[])
{
	unsigned short stringLength = strlen(fenString);

	char* stringArray[FEN_STRING_PARTS];

	if(!split_string_delim(stringArray, fenString, stringLength, FEN_STRING_DELIM, FEN_STRING_PARTS)) return false;

	bool parseResult = parse_string_array(board, info, stringArray);

	free_array_strings(stringArray, FEN_STRING_PARTS);

	return parseResult;
}

bool parse_string_array(Piece** board, Info* info, char* stringArray[])
{
	*info = INFO_BLANK;

	if(!parse_string_board(board, stringArray[0])) return false;

	if(!parse_string_info(info, stringArray))
	{ free(*board); return false; }

	return true;
}

bool parse_string_info(Info* info, char* stringArray[])
{
	if(!parse_string_current(info, stringArray[1])) return false;

	if(!parse_string_castles(info, stringArray[2])) return false;

	if(!parse_string_passant(info, stringArray[3])) return false;

	if(!parse_string_counter(info, stringArray[4])) return false;

	if(!parse_string_turns(info, stringArray[5])) return false;

	return true;
}

bool parse_string_current(Info* info, const char stringToken[])
{
	Info infoCurrentTeam = INFO_BLANK;

	unsigned short stringLength = strlen(stringToken);

	if(stringLength != 1) return false;


	if(stringToken[0] == WHITE_SYMBOL) infoCurrentTeam = INFO_TEAM_WHITE;

	else if(stringToken[0] == BLACK_SYMBOL) infoCurrentTeam = INFO_TEAM_BLACK;

	else return false;

	*info = ALLOC_INFO_TEAM(*info, infoCurrentTeam);

	return true;
}

bool parse_string_counter(Info* info, const char stringToken[])
{
	unsigned short counter = 0;

	if(!parse_string_short(&counter, stringToken)) return false;

	*info = ALLOC_COUNTER_INFO(*info, counter);

	return true;
}

bool parse_string_turns(Info* info, const char stringToken[])
{
	unsigned short turns = 0;

	if(!parse_string_short(&turns, stringToken)) return false;

	*info = ALLOC_TURNS_INFO(*info, turns);

	return true;
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

bool parse_string_passant(Info* info, const char stringToken[])
{
	if(!strcmp(stringToken, FEN_PASSANT_NONE)) return true;

	Point passantPoint = POINT_NONE;
	if(!parse_string_point(&passantPoint, stringToken)) return false;

	unsigned short passant = (POINT_FILE_MACRO(passantPoint) + 1);

	*info = ALLOC_PASSANT_INFO(*info, passant);

	return true;
}

bool parse_string_point(Point* point, const char string[])
{
	unsigned short stringLength = strlen(string);

	if(stringLength != 2) return false;

	short fileIndex = string_symbol_index(FILE_SYMBOLS, BOARD_FILES, string[0]);
	short rankIndex = string_symbol_index(RANK_SYMBOLS, BOARD_RANKS, string[1]);

	if(fileIndex == INDEX_NONE || rankIndex == INDEX_NONE) return false;

	*point = RANK_FILE_POINT(rankIndex, fileIndex);

	return true;
}

bool parse_string_move(Move* move, const char stringMove[])
{
  int stringLen = strlen(stringMove);
  if(stringLen != 4 && stringLen != 5) return false;

  char startString[3];
  memset(startString, '\0', sizeof(startString));

  char stopString[3];
  memset(stopString, '\0', sizeof(stopString));

  strncpy(startString, (stringMove + 0), 2);
  strncpy(stopString, (stringMove + 2), 2);

  Point startPoint, stopPoint;
  if(!parse_string_point(&startPoint, startString)) return false;
  if(!parse_string_point(&stopPoint, stopString)) return false;

  Move parseMove = START_STOP_MOVE(startPoint, stopPoint);

  if(stringLen == 5)
  {
    parseMove = ALLOC_MOVE_FLAG(parseMove, MOVE_FLAG_QUEEN);
  }

  *move = parseMove;

  return true;
}

bool parse_string_castles(Info* info, const char stringToken[])
{
	Info castles = INFO_NONE;

	if(!strcmp(stringToken, FEN_CASTLES_NONE)) return true;

	unsigned short stringLength = strlen(stringToken);
	if(stringLength > FEN_MAX_CASTLES) return false;

	for(unsigned short index = 0; index < stringLength; index += 1)
	{
		char symbol = stringToken[index];

		Info infoCastle = INFO_BLANK;

		if(!parse_castle_symbol(&infoCastle, symbol)) return false;

		castles |= infoCastle;
	}

	*info = ALLOC_INFO_CASTLES(*info, castles);

	return true;
}

bool parse_castle_symbol(Info* infoCastle, char symbol)
{
	if(symbol == chess_piece_symbol(PIECE_TEAM_WHITE | PIECE_TYPE_KING))
	{
		*infoCastle = INFO_WHITE_KSIDE;
	}
	else if(symbol == chess_piece_symbol(PIECE_TEAM_WHITE | PIECE_TYPE_QUEEN))
	{
		*infoCastle = INFO_WHITE_QSIDE;
	}
	else if(symbol == chess_piece_symbol(PIECE_TEAM_BLACK | PIECE_TYPE_KING))
	{
		*infoCastle = INFO_BLACK_KSIDE;
	}
	else if(symbol == chess_piece_symbol(PIECE_TEAM_BLACK | PIECE_TYPE_QUEEN))
	{
		*infoCastle = INFO_BLACK_QSIDE;
	}
	else return false;

	return true;
}

bool parse_string_board(Piece** board, const char stringToken[])
{
	unsigned short stringLength = strlen(stringToken);

	char* stringArray[BOARD_RANKS];

	if(!split_string_delim(stringArray, stringToken, stringLength, FEN_RANK_DELIM, BOARD_RANKS)) return false;

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
			free_array_strings(stringArray, BOARD_RANKS);

			free(*board); return false;
		}
	}
	free_array_strings(stringArray, BOARD_RANKS); return true;
}

bool parse_board_files(Piece** board, unsigned short rank, const char rankString[], short length)
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

	Point point = RANK_FILE_POINT(rank, *file);

	(*board)[point] = piece;

	*file += 1; return true;
}

bool parse_board_blanks(Piece** board, unsigned short rank, unsigned short* file, short blanks)
{
	unsigned short totalFiles = (*file + blanks);

	if(totalFiles > BOARD_FILES) return false;

	for(; *file < totalFiles; *file += 1)
	{
		(*board)[RANK_FILE_POINT(rank, *file)] = PIECE_NONE;
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



char chess_piece_symbol(Piece piece)
{
	Piece pieceTeam = (piece & PIECE_TEAM_MASK);
	unsigned short typeIndex = PIECE_TYPE_MACRO(piece);

	if(pieceTeam == PIECE_TEAM_WHITE) return WHITE_TYPE_SYMBOLS[typeIndex];

	if(pieceTeam == PIECE_TEAM_BLACK) return BLACK_TYPE_SYMBOLS[typeIndex];

	return SYMBOL_NONE;
}
