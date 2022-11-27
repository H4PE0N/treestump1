
#include "../Header-Files-Folder/englog-include-file.h"

unsigned short move_array_amount(const Move moveArray[])
{
	unsigned short movesAmount = 0;

	while(moveArray[movesAmount] != MOVE_NONE && moveArray[movesAmount] >= 0) movesAmount += 1;

	return movesAmount;
}

void append_moves_array(Move* moveArray, const Move addingArray[])
{
	int moveAmount = move_array_amount(moveArray);
	int addingAmount = move_array_amount(addingArray);

	for(unsigned short index = 0; index < addingAmount; index += 1)
		moveArray[moveAmount + index] = addingArray[index];
}

Move* create_move_array(short arrayLength)
{
	Move* moveArray = malloc(sizeof(Move) * (arrayLength + 1));

	for(unsigned short index = 0; index < (arrayLength + 1); index += 1)
		moveArray[index] = MOVE_NONE;

	return moveArray;
}

short move_file_offset(Move move, unsigned short team)
{
	unsigned short startFile = MOVE_START_FILE(move);
	unsigned short stopFile = MOVE_STOP_FILE(move);

	signed short fileOffset = (stopFile - startFile);

	if(team == TEAM_WHITE) return fileOffset;
	if(team == TEAM_BLACK) return fileOffset;

	return SHORT_NONE;
}

short move_rank_offset(Move move, unsigned short team)
{
	unsigned short startRank = MOVE_START_RANK(move);
	unsigned short stopRank = MOVE_STOP_RANK(move);

	signed short rankOffset = (stopRank - startRank);

	if(team == TEAM_WHITE) return (rankOffset * WHITE_MOVE_VALUE);
	if(team == TEAM_BLACK) return (rankOffset * BLACK_MOVE_VALUE);

	return SHORT_NONE;
}

unsigned short abs_move_roffset(Move move, unsigned short team)
{
	return ABS_SHORT_NUMBER(move_rank_offset(move, team));
}

unsigned short abs_move_foffset(Move move, unsigned short team)
{
	return ABS_SHORT_NUMBER(move_file_offset(move, team));
}

short normal_rank_offset(Move move)
{
	Point startPoint = MOVE_START_MACRO(move);
	Point stopPoint = MOVE_STOP_MACRO(move);

	return (POINT_RANK_MACRO(stopPoint) - POINT_RANK_MACRO(startPoint));
}

short normal_file_offset(Move move)
{
	Point startPoint = MOVE_START_MACRO(move);
	Point stopPoint = MOVE_STOP_MACRO(move);

	return (POINT_FILE_MACRO(stopPoint) - POINT_FILE_MACRO(startPoint));
}

char piece_move_symbol(Piece piece)
{
	if(!CHESS_PIECE_EXISTS(piece)) return SYMBOL_NONE;

	return MOVE_TYPE_SYMBOLS[PIECE_TYPE_MACRO(piece)];
}

bool castle_move_string(char* moveString, Move move)
{
	signed short movePattern = BOARD_MOVE_PATTERN(move);

	if(movePattern == KSIDE_FILE_OFFSET) strcpy(moveString, KSIDE_MOVE_STRING);

	else if(movePattern == QSIDE_FILE_OFFSET) strcpy(moveString, QSIDE_MOVE_STRING);

	else return false;

	return true;
}

bool chess_move_capture(Move move, const Piece board[], Info info)
{
	unsigned short stopFile = MOVE_STOP_FILE(move);

	if(MOVE_POINTS_ENEMY(board, move)) return true;

	else if(INFO_PASSANT_MACRO(info) == (stopFile + 1)) return true;

	return false;
}

bool equal_piece_rank(const Piece board[], Point point)
{
	unsigned short pieceFile = POINT_FILE_MACRO(point);
	unsigned short pieceRank = POINT_RANK_MACRO(point);

	for(unsigned short file = 0; file < BOARD_FILES; file += 1)
	{
		if(pieceFile == file) continue;

		Point currPoint = RANK_FILE_POINT(pieceRank, file);
		if(board[currPoint] == board[point]) return true;
	}
	return false;
}

bool equal_piece_file(const Piece board[], Point point)
{
	unsigned short pieceFile = POINT_FILE_MACRO(point);
	unsigned short pieceRank = POINT_RANK_MACRO(point);

	for(unsigned short rank = 0; rank < BOARD_RANKS; rank += 1)
	{
		if(pieceRank == rank) continue;

		Point currPoint = RANK_FILE_POINT(rank, pieceFile);
		if(board[currPoint] == board[point]) return true;
	}
	return false;
}

bool piece_place_string(char* placeString, const Piece board[], Point point)
{
	unsigned short pieceFile = POINT_FILE_MACRO(point);
	unsigned short pieceRank = POINT_RANK_MACRO(point);

	if(!equal_piece_file(board, point)) strncpy(placeString, &FILE_SYMBOLS[pieceFile], 1);

	else if(!equal_piece_rank(board, point)) strncpy(placeString, &RANK_SYMBOLS[pieceRank], 1);

	else
	{
		char pointString[8];
		if(!create_point_string(pointString, point)) return false;

		strcpy(placeString, pointString);
	}
	return true;
}

bool pattern_moves_equal(Move move1, Move move2)
{
	if(MOVE_START_MACRO(move1) != MOVE_START_MACRO(move2)) return false;
	if(MOVE_STOP_MACRO(move1) != MOVE_STOP_MACRO(move2)) return false;

	return true;
}

bool start_pieces_equal(const Piece board[], Move move1, Move move2)
{
	if(!MOVE_INSIDE_BOARD(move1) || !MOVE_INSIDE_BOARD(move2)) return false;

	return (MOVE_START_PIECE(board, move1) == MOVE_START_PIECE(board, move2));
}

bool equal_piece_attack(const Piece board[], Info info, Move move)
{
	Move* equalMoves;
	if(!equal_pattern_moves(&equalMoves, board, move)) return false;
	
	unsigned short moveAmount = move_array_amount(equalMoves);

	for(short index = 0; index < moveAmount; index += 1)
	{
		Move currentMove = equalMoves[index];

		if(!start_pieces_equal(board, currentMove, move)) continue;

		if(pattern_moves_equal(currentMove, move)) continue;

		if(!pattern_move_legal(&currentMove, board, info)) continue;

		free(equalMoves); return true;
	}
	free(equalMoves); return false;
}

bool equal_pattern_moves(Move** moves, const Piece board[], Move move)
{
	if(!target_pattern_moves(moves, board, move)) return false;
	
	unsigned short moveAmount = move_array_amount(*moves);

	for(short index = 0; index < moveAmount; index += 1)
		(*moves)[index] = INVERT_CHESS_MOVE((*moves)[index]);
	
	return true;
}

bool target_pattern_moves(Move** moves, const Piece board[], Move move)
{
	if(!MOVE_INSIDE_BOARD(move)) return false;

	Point startPoint = MOVE_START_MACRO(move);
	Point stopPoint = MOVE_STOP_MACRO(move);

	if(PIECE_STORE_TYPE(board[startPoint], PIECE_TYPE_PAWN))
		return pawn_pattern_moves(moves, board, stopPoint);

	if(PIECE_STORE_TYPE(board[startPoint], PIECE_TYPE_KNIGHT))
		return knight_pattern_moves(moves, board, stopPoint);

	if(PIECE_STORE_TYPE(board[startPoint], PIECE_TYPE_BISHOP))
		return bishop_pattern_moves(moves, board, stopPoint);

	if(PIECE_STORE_TYPE(board[startPoint], PIECE_TYPE_ROOK))
		return rook_pattern_moves(moves, board, stopPoint);

	if(PIECE_STORE_TYPE(board[startPoint], PIECE_TYPE_QUEEN))
		return queen_pattern_moves(moves, board, stopPoint);

	if(PIECE_STORE_TYPE(board[startPoint], PIECE_TYPE_KING))
		return king_pattern_moves(moves, board, stopPoint);

	return false;
}

bool create_move_string(char* moveString, const Piece board[], Info info, Move move)
{
	if(!MOVE_INSIDE_BOARD(move)) return false;

	memset(moveString, '\0', sizeof(char) * 16);

	if(MOVE_STORE_FLAG(move, MOVE_FLAG_CASTLE))
		return castle_move_string(moveString, move);

	Point startPoint = MOVE_START_MACRO(move);

	if(!PIECE_STORE_TYPE(board[startPoint], PIECE_TYPE_PAWN))
	{
		char pieceSymbol = piece_move_symbol(board[startPoint]);

		if(pieceSymbol == SYMBOL_NONE) return false;

		strncat(moveString, &pieceSymbol, 1);
	}

	char placeString[8];
	if(equal_piece_attack(board, info, move))
	{
		if(!piece_place_string(placeString, board, startPoint)) return false;

		strcat(moveString, placeString);
	}

	if(chess_move_capture(move, board, info))
	{
		if(PIECE_STORE_TYPE(board[startPoint], PIECE_TYPE_PAWN))
		{
			if(!strlen(placeString))
			{
				if(!piece_place_string(placeString, board, startPoint)) return false;

				strcat(moveString, placeString);
			}
		}
		strcat(moveString, "x");
	}

	Point stopPoint = MOVE_STOP_MACRO(move);
	

	char stopString[8];
	if(!create_point_string(stopString, stopPoint)) return false;

	strcat(moveString, stopString);


	if(MOVE_PROMOTE_FLAG(move))
	{
		Piece pieceType = promote_piece_type(move);

		if(pieceType == PIECE_TYPE_NONE) return false;

		unsigned short typeIndex = PIECE_TYPE_MACRO(pieceType);

		strcat(moveString, "=");
		strncat(moveString, &MOVE_TYPE_SYMBOLS[typeIndex], 1);
	}


	if(move_deliver_mate(board, info, move)) strcat(moveString, "#");
	
	else if(move_deliver_check(board, info, move)) strcat(moveString, "+");

	return true;
}

bool create_point_string(char* pointString, Point point)
{
	char fileSymbol = FILE_SYMBOLS[POINT_FILE_MACRO(point)];
	char rankSymbol = RANK_SYMBOLS[POINT_RANK_MACRO(point)];

	sprintf(pointString, "%c%c", fileSymbol, rankSymbol);

	return true;
}