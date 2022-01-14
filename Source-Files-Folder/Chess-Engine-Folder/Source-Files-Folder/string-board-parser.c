
#include "../Header-Files-Folder/engine-include-file.h"

// rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR KQkq - 1 0

bool parse_game_string(Piece** board, Info* info, char gameString[])
{
	unsigned short stringLength = strlen(gameString);

	unsigned short amount = 6;

	char* stringArray[amount];

	if(!split_string_delim(stringArray, gameString, stringLength, (char*) STRING_DELIM, amount))
	{
		printf("split_string_delim\n");

		return false;
	}

	for(unsigned short index = 0; index < amount; index += 1)
	{
		printf("stringArray[%d]: (%s)\n", index, stringArray[index]);
	}

	*info = INFO_NONE;

	if(!parse_string_board(board, stringArray[0]))
	{
		printf("parse_string_board\n");

		free_array_strings(stringArray, amount);

		return false;
	}

	Info currentTeam;

	if(!parse_string_current(&currentTeam, stringArray[1]))
	{
		printf("parse_string_current\n");

		free_array_strings(stringArray, amount);

		free(*board);

		return false;
	}

	*info |= currentTeam & INFO_TEAM_MASK;

	Info castles;

	if(!parse_string_castles(&castles, stringArray[2]))
	{
		printf("parse_string_castles\n");

		free_array_strings(stringArray, amount);

		free(*board);

		return false;
	}

	*info |= castles & INFO_CASTLES_MASK;

	Passant passant;

	if(!parse_string_passant(&passant, stringArray[3]))
	{
		printf("parse_string_passant\n");

		free_array_strings(stringArray, amount);

		free(*board);

		return false;
	}

	*info |= (passant << INFO_PASSANT_SHIFT) & INFO_PASSANT_MASK;

	Turns turns;

	if(!parse_string_turns(&turns, stringArray[4]))
	{
		printf("parse_string_turns\n");

		free_array_strings(stringArray, amount);

		free(*board);

		return false;
	}

	*info |= (turns << INFO_TURNS_SHIFT) & INFO_TURNS_MASK;

	Counter counter;

	if(!parse_string_counter(&counter, stringArray[5]))
	{
		printf("parse_string_counter\n");

		free_array_strings(stringArray, amount);

		free(*board);

		return false;
	}

	*info |= (counter << INFO_COUNTER_SHIFT) & INFO_COUNTER_MASK;

	free_array_strings(stringArray, amount);

	return true;
}

bool parse_string_current(Info* currentTeam, char stringToken[])
{
	unsigned short stringLength = strlen(stringToken);

	char stringCopy[stringLength];

	strcpy(stringCopy, stringToken);

	printf("Current: %s\n", stringCopy);

	if(stringLength != 1) return false;

	if(stringCopy[0] == WHITE_SYMBOL)
	{
		*currentTeam = INFO_TEAM_WHITE;
	}
	else if(stringCopy[0] == BLACK_SYMBOL)
	{
		*currentTeam = INFO_TEAM_BLACK;
	}
	else
	{
		return false;
	}

	return true;
}

bool parse_string_counter(Counter* counter, char stringToken[])
{
	unsigned short stringLength = strlen(stringToken);

	char stringCopy[stringLength];

	strcpy(stringCopy, stringToken);

	if(!parse_string_short(counter, stringCopy))
	{
		return false;
	}

	return true;
}

bool parse_string_turns(Turns* turns, char stringToken[])
{
	unsigned short stringLength = strlen(stringToken);

	char stringCopy[stringLength];

	strcpy(stringCopy, stringToken);
	
	if(!parse_string_short(turns, stringCopy))
	{
		return false;
	}
	
	return true;
}

bool parse_string_short(unsigned short* number, char string[])
{
	unsigned short stringLength = strlen(string);

	if(stringLength < 1) return false;

	char stringCopy[stringLength];

	strcpy(stringCopy, string);


	unsigned int dummyNumber = 0;


	for(unsigned int index = 0; index < stringLength; index += 1)
	{
		unsigned short value = pow(10, (stringLength - index - 1));

		// potential number
		short potentNumber = stringCopy[index] - '0';

		if(NUMBER_IN_BOUNDS(potentNumber, 0, 9)) // if 'potentNumber' is a number, not a letter
		{
			dummyNumber += value * potentNumber;
		}
		else
		{
			// A letter is in the string

			return false;
		}
	}

	*number = dummyNumber;

	return true;
}

bool parse_string_passant(Passant* passant, char stringToken[])
{
	return true;
}

bool parse_string_point(Point* point, char string[])
{
	/*
	unsigned short stringLength = strlen(string);

	if(stringLength != 2)
	{
		return false;
	}

	unsigned short file = string_symbol_index((char*) fileSymbols, boardFiles, string[0]);

	if(!number_inside_bounds(file, 0, boardFiles - 1)) return false;

	unsigned int rank = string_symbol_index((char*) rankSymbols, boardRanks, string[1]);

	if(!number_inside_bounds(rank, 0, boardRanks - 1)) return false;

	*point = (rank * boardFiles) + file;
	*/
	return true;
}

bool parse_string_move(Move* move, char string[])
{
	return true;
}

bool parse_string_castles(Info* castles, char stringToken[])
{
	unsigned short stringLength = strlen(stringToken);

	char stringCopy[stringLength];

	strcpy(stringCopy, stringToken);


	if(stringLength > 4) return false;


	*castles = MOVE_NONE; // Setting all castle abilities to false;


	if(strcmp(stringCopy, CASTLES_NONE) == 0)
	{
		// This means that there is no castle ability
		return true;
	}

	for(unsigned short index = 0; index < stringLength; index += 1)
	{
		char symbol = stringCopy[index];


		if(symbol == WHITE_SYMBOLS[(PIECE_TYPE_KING >> PIECE_TYPE_SHIFT)])
		{
			*castles |= INFO_WHITE_KING;
		}
		else if(symbol == WHITE_SYMBOLS[(PIECE_TYPE_QUEEN >> PIECE_TYPE_SHIFT)])
		{
			*castles |= INFO_WHITE_QUEEN;
		}
		else if(symbol == BLACK_SYMBOLS[(PIECE_TYPE_KING >> PIECE_TYPE_SHIFT)])
		{
			*castles |= INFO_BLACK_KING;
		}
		else if(symbol == BLACK_SYMBOLS[(PIECE_TYPE_QUEEN >> PIECE_TYPE_SHIFT)])
		{
			*castles |= INFO_BLACK_QUEEN;
		}
		else
		{
			// FEN is wrong!

			return false;
		}
	}

	return true;
}

bool parse_string_board(Piece** board, char stringToken[])
{
	unsigned short stringLength = strlen(stringToken);

	char stringCopy[stringLength];

	strcpy(stringCopy, stringToken);

	
	*board = malloc(sizeof(Piece) * BOARD_LENGTH);


	char* stringArray[BOARD_RANKS];

	if(!split_string_delim(stringArray, stringCopy, stringLength, (char*) RANK_DELIM, BOARD_RANKS))
	{
		printf("split_string_delim\n");

		return false;
	}


	for(unsigned short rank = 0; rank < BOARD_RANKS; rank += 1)
	{
		unsigned short stringLength = strlen(stringArray[rank]);


		unsigned short file = 0;

		for(unsigned short index = 0; index < stringLength; index += 1) // length of string ex. 2 (7p)
		{
			if(file >= BOARD_FILES)
			{
				// One rank of symbols cant be more than 'boardFiles' chars long (8 chars)
				free(*board);

				free_array_strings(stringArray, BOARD_RANKS);

				return false;
			}

			char symbol = stringArray[rank][index];

			short blanks = symbol - '0';

			if(NUMBER_IN_BOUNDS(blanks, 0, BOARD_FILES)) // If symbol is 0 - 8
			{
				unsigned short blankFiles = file + blanks;

				if(blankFiles > BOARD_FILES)
				{
					// The FEN string is set wrong.
					free(*board);

					free_array_strings(stringArray, BOARD_RANKS);

					return false;
				}

				for(; file < blankFiles; file += 1)
				{
					Point point = (rank * BOARD_FILES) + file;

					(*board)[point] = PIECE_TEAM_NONE | PIECE_TYPE_NONE;
				}
			}
			else
			{
				Piece piece;

				if(!parse_board_piece(&piece, symbol))
				{
					// The FEN string is set wrong.
					free(*board);

					free_array_strings(stringArray, BOARD_RANKS);

					return false;
				}

				Point point = (rank * BOARD_FILES) + file;

				(*board)[point] = piece;

				file += 1;				
			}
		}
	}

	free_array_strings(stringArray, BOARD_RANKS);

	return true;
}

bool parse_board_piece(Piece* piece, char symbol)
{
	// 65 - 90  uppercase = white
	// 97 - 122	lowercase = black

	for(unsigned short index = 0; index < SYMBOL_AMOUNT; index += 1)
	{
		if(symbol == WHITE_SYMBOLS[index])
		{
			*piece = PIECE_TEAM_WHITE | (index << PIECE_TYPE_SHIFT); // (index = type)

			return true;
		}
		if(symbol == BLACK_SYMBOLS[index])
		{
			*piece = PIECE_TEAM_BLACK | (index << PIECE_TYPE_SHIFT); // (index = type)

			return true;
		}
	}

	return false;
}