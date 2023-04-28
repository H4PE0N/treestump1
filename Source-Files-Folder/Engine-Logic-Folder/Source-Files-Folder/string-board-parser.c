
#include "../Header-Files-Folder/englog-include-file.h"

bool parse_create_board(Piece** board, State* state, const char fenString[])
{
	*board = malloc(sizeof(Piece) * BOARD_POINTS);

	if(parse_fen_string(*board, state, fenString)) return true;

	free(*board); return false;
}

bool parse_fen_string(Piece* board, State* state, const char fenString[])
{
	int stringLength = strlen(fenString);

	char* stringArray[FEN_STRING_PARTS];

	if(!split_string_delim(stringArray, fenString, stringLength, FEN_STRING_DELIM, FEN_STRING_PARTS)) return false;

	bool parseResult = parse_string_array(board, state, stringArray);

	free_array_strings(stringArray, FEN_STRING_PARTS);

	return parseResult;
}

bool parse_string_array(Piece* board, State* state, char* stringArray[])
{
	*state = STATE_BLANK;

	if(!parse_string_board(board, stringArray[0])) return false;

	if(!parse_string_state(state, stringArray)) return false;

	return true;
}

bool parse_string_state(State* state, char* stringArray[])
{
	if(!parse_string_current(state, stringArray[1])) return false;

	if(!parse_string_castles(state, stringArray[2])) return false;

	if(!parse_string_passant(state, stringArray[3])) return false;

	if(!parse_string_clock(state, stringArray[4])) return false;

	if(!parse_string_turns(state, stringArray[5])) return false;

	return true;
}

bool parse_string_current(State* state, const char stringToken[])
{
	State stateCurrentTeam = STATE_BLANK;

	int stringLength = strlen(stringToken);

	if(stringLength != 1) return false;


	if(stringToken[0] == WHITE_SYMBOL) stateCurrentTeam = STATE_TEAM_WHITE;

	else if(stringToken[0] == BLACK_SYMBOL) stateCurrentTeam = STATE_TEAM_BLACK;

	else return false;

	*state = ALLOC_STATE_CURRENT(*state, stateCurrentTeam);

	return true;
}

bool parse_string_clock(State* state, const char stringToken[])
{
	int clock = atoi(stringToken);

	if((clock == 0) && (stringToken[0] != '0')) return false;

	*state = ALLOC_CLOCK_STATE(*state, clock); return true;
}

bool parse_string_turns(State* state, const char stringToken[])
{
	int turns = atoi(stringToken);

	if((turns == 0) && (stringToken[0] != '0')) return false;

	*state = ALLOC_TURNS_STATE(*state, turns); return true;
}

bool parse_string_passant(State* state, const char stringToken[])
{
	if(!strcmp(stringToken, FEN_PASSANT_NONE)) return true;

	Point passantPoint = POINT_NONE;
	if(!parse_string_point(&passantPoint, stringToken)) return false;

	unsigned short passant = (POINT_FILE_MACRO(passantPoint) + 1);

	*state = ALLOC_PASSANT_STATE(*state, passant);

	return true;
}

bool parse_string_point(Point* point, const char string[])
{
	int stringLength = strlen(string);

	if(stringLength != 2) return false;

	int fileIndex = string_symbol_index(FILE_SYMBOLS, BOARD_FILES, string[0]);
	int rankIndex = string_symbol_index(RANK_SYMBOLS, BOARD_RANKS, string[1]);

	if(fileIndex == INDEX_NONE || rankIndex == INDEX_NONE) return false;

	*point = RANK_FILE_POINT(rankIndex, fileIndex);

	return true;
}

bool string_basic_move(Move* move, const char stringMove[])
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

  if(stringLen == 5)   parseMove = ALLOC_MOVE_FLAG(parseMove, MOVE_FLAG_QUEEN);

  *move = parseMove;

  return true;
}

bool parse_string_castles(State* state, const char stringToken[])
{
	State castles = STATE_NONE;

	if(!strcmp(stringToken, FEN_CASTLES_NONE)) return true;

	int stringLength = strlen(stringToken);
	if(stringLength > FEN_MAX_CASTLES) return false;

	for(int index = 0; index < stringLength; index += 1)
	{
		char symbol = stringToken[index];

		State stateCastle = STATE_BLANK;

		if(!parse_castle_symbol(&stateCastle, symbol)) return false;

		castles |= stateCastle;
	}
	*state = ALLOC_STATE_CASTLES(*state, castles); return true;
}

bool parse_castle_symbol(State* stateCastle, char symbol)
{
	if(symbol == chess_piece_symbol(PIECE_TEAM_WHITE | PIECE_TYPE_KING))
	{
		*stateCastle = STATE_WHITE_KSIDE;
	}
	else if(symbol == chess_piece_symbol(PIECE_TEAM_WHITE | PIECE_TYPE_QUEEN))
	{
		*stateCastle = STATE_WHITE_QSIDE;
	}
	else if(symbol == chess_piece_symbol(PIECE_TEAM_BLACK | PIECE_TYPE_KING))
	{
		*stateCastle = STATE_BLACK_KSIDE;
	}
	else if(symbol == chess_piece_symbol(PIECE_TEAM_BLACK | PIECE_TYPE_QUEEN))
	{
		*stateCastle = STATE_BLACK_QSIDE;
	}
	else return false;

	return true;
}

bool parse_string_board(Piece* board, const char stringToken[])
{
	int stringLength = strlen(stringToken);

	char* stringArray[BOARD_RANKS];

	if(!split_string_delim(stringArray, stringToken, stringLength, FEN_RANK_DELIM, BOARD_RANKS)) return false;

	for(uint8_t rank = 0; rank < BOARD_RANKS; rank += 1)
	{
		int rankLength = strlen(stringArray[rank]);

		if(!parse_board_files(board, rank, stringArray[rank], rankLength))
		{
			free_array_strings(stringArray, BOARD_RANKS);

			return false;
		}
	}
	free_array_strings(stringArray, BOARD_RANKS); return true;
}

bool parse_board_files(Piece* board, uint8_t rank, const char rankString[], int length)
{
	uint8_t file = 0;

	for(int index = 0; index < length; index += 1)
	{
		if(file >= BOARD_FILES) return false;

		char symbol = rankString[index];

		if(!parse_board_symbol(board, rank, &file, symbol)) return false;
	}
	return true;
}

bool parse_board_symbol(Piece* board, uint8_t rank, uint8_t* file, char symbol)
{
	short potentBlanks = (symbol - '0');

	if(NUMBER_IN_BOUNDS(potentBlanks, 0, BOARD_FILES))
	{
		return parse_board_blanks(board, rank, file, potentBlanks);
	}

	Piece piece;
	if(!parse_board_piece(&piece, symbol)) return false;

	Point point = RANK_FILE_POINT(rank, *file);

	board[point] = piece;

	*file += 1; return true;
}

bool parse_board_blanks(Piece* board, uint8_t rank, uint8_t* file, short blanks)
{
	short totalFiles = (*file + blanks);

	if(totalFiles > BOARD_FILES) return false;

	for(; *file < totalFiles; *file += 1)
	{
		board[RANK_FILE_POINT(rank, *file)] = PIECE_NONE;
	}
	return true;
}

bool parse_board_piece(Piece* piece, char symbol)
{
	for(uint8_t typeIndex = 0; typeIndex < PIECE_TYPE_SPAN; typeIndex += 1)
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
	uint8_t team = PIECE_TEAM_MACRO(piece);
	uint8_t typeIndex = PIECE_TYPE_MACRO(piece);

	if(team == TEAM_WHITE) return WHITE_TYPE_SYMBOLS[typeIndex];
	if(team == TEAM_BLACK) return BLACK_TYPE_SYMBOLS[typeIndex];

	return SYMBOL_NONE;
}
