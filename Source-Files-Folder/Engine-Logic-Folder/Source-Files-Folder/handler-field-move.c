
#include "../Header-Files-Folder/englog-include-file.h"

int move_array_amount(const Move moveArray[])
{
	int moveAmount = 0;

	while(MOVE_INSIDE_BOARD(moveArray[moveAmount])) moveAmount += 1;

	return moveAmount;
}

void paste_capped_moves(Move* moves1, int amount1, const Move moves2[], int amount2)
{
	int pasteAmount = MIN_NUMBER_VALUE(amount1, amount2);
	paste_move_array(moves1, moves2, pasteAmount);
}

void paste_move_array(Move* moves1, const Move moves2[], int moveAmount)
{
	for(int index = 0; index < moveAmount; index += 1)
	{
		moves1[index] = moves2[index];
	}
}

Move* copy_move_array(const Move moveArray[], int moveAmount)
{
	Move* movesCopy = malloc(sizeof(Move) * moveAmount);
	memcpy(movesCopy, moveArray, sizeof(Move) * moveAmount);

	return movesCopy;
}

void append_move_array(Move* moves1, int* amount1, const Move moves2[], int amount2)
{
	for(int index = 0; index < amount2; index += 1)
	{
		moves1[(*amount1)++] = moves2[index];
	}
}

Move* create_move_array(int amount)
{
	Move* moveArray = malloc(sizeof(Move) * (amount + 1));
	memset(moveArray, MOVE_NONE, sizeof(Move) * (amount + 1));

	return moveArray;
}

int8_t move_file_offset(Move move, uint8_t team)
{
	return (MOVE_STOP_FILE(move) - MOVE_START_FILE(move));
}

int8_t move_rank_offset(Move move, uint8_t team)
{
	int8_t rankOffset = (MOVE_STOP_RANK(move) - MOVE_START_RANK(move));

	if(team == TEAM_WHITE) return (rankOffset * WHITE_MOVE_VALUE);

	return (rankOffset * BLACK_MOVE_VALUE);
}

int8_t normal_rank_offset(Move move)
{
	Point startPoint = MOVE_START_MACRO(move);
	Point stopPoint = MOVE_STOP_MACRO(move);

	return (POINT_RANK_MACRO(stopPoint) - POINT_RANK_MACRO(startPoint));
}

int8_t normal_file_offset(Move move)
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
	int8_t movePattern = BOARD_MOVE_PATTERN(move);

	if(movePattern == KSIDE_FILE_OFFSET) strcpy(moveString, KSIDE_MOVE_STRING);

	else if(movePattern == QSIDE_FILE_OFFSET) strcpy(moveString, QSIDE_MOVE_STRING);

	else return false;

	return true;
}

bool chess_move_capture(Move move, const Piece board[], Info info)
{
	uint8_t stopFile = MOVE_STOP_FILE(move);

	if(MOVE_POINTS_ENEMY(board, move)) return true;

	else if(INFO_PASSANT_MACRO(info) == (stopFile + 1)) return true;

	return false;
}

bool equal_piece_rank(const Piece board[], Point point)
{
	uint8_t pieceFile = POINT_FILE_MACRO(point);
	uint8_t pieceRank = POINT_RANK_MACRO(point);

	for(uint8_t file = 0; file < BOARD_FILES; file += 1)
	{
		if(pieceFile == file) continue;

		Point currPoint = RANK_FILE_POINT(pieceRank, file);
		if(board[currPoint] == board[point]) return true;
	}
	return false;
}

bool equal_piece_file(const Piece board[], Point point)
{
	uint8_t pieceFile = POINT_FILE_MACRO(point);
	uint8_t pieceRank = POINT_RANK_MACRO(point);

	for(uint8_t rank = 0; rank < BOARD_RANKS; rank += 1)
	{
		if(pieceRank == rank) continue;

		Point currPoint = RANK_FILE_POINT(rank, pieceFile);
		if(board[currPoint] == board[point]) return true;
	}
	return false;
}

bool piece_place_string(char* placeString, const Piece board[], Point point)
{
	uint8_t pieceFile = POINT_FILE_MACRO(point);
	uint8_t pieceRank = POINT_RANK_MACRO(point);

	if(!equal_piece_file(board, point))
		strncpy(placeString, &FILE_SYMBOLS[pieceFile], 1);

	else if(!equal_piece_rank(board, point))
		strncpy(placeString, &RANK_SYMBOLS[pieceRank], 1);

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
	Move* equalMoves; int moveAmount;
	if(!equal_pattern_moves(&equalMoves, &moveAmount, board, move)) return false;

	for(int index = 0; index < moveAmount; index += 1)
	{
		Move currentMove = equalMoves[index];

		if(!start_pieces_equal(board, currentMove, move)) continue;

		if(pattern_moves_equal(currentMove, move)) continue;

		if(!pattern_move_legal(&currentMove, board, info)) continue;

		free(equalMoves); return true;
	}
	free(equalMoves); return false;
}

bool equal_pattern_moves(Move** moves, int* moveAmount, const Piece board[], Move move)
{
	if(!target_pattern_moves(moves, moveAmount, board, move)) return false;

	for(int index = 0; index < *moveAmount; index += 1)
	{
		(*moves)[index] = INVERT_CHESS_MOVE((*moves)[index]);
	}
	return true;
}

bool target_pattern_moves(Move** moves, int* moveAmount, const Piece board[], Move move)
{
	if(!MOVE_INSIDE_BOARD(move)) return false;

	Point startPoint = MOVE_START_MACRO(move);
	Point stopPoint = MOVE_STOP_MACRO(move);

	if(PIECE_STORE_TYPE(board[startPoint], PIECE_TYPE_PAWN))
		return pawn_pattern_moves(moves, moveAmount, board, stopPoint);

	if(PIECE_STORE_TYPE(board[startPoint], PIECE_TYPE_KNIGHT))
		return knight_pattern_moves(moves, moveAmount, board, stopPoint);

	if(PIECE_STORE_TYPE(board[startPoint], PIECE_TYPE_BISHOP))
		return bishop_pattern_moves(moves, moveAmount, board, stopPoint);

	if(PIECE_STORE_TYPE(board[startPoint], PIECE_TYPE_ROOK))
		return rook_pattern_moves(moves, moveAmount, board, stopPoint);

	if(PIECE_STORE_TYPE(board[startPoint], PIECE_TYPE_QUEEN))
		return queen_pattern_moves(moves, moveAmount, board, stopPoint);

	if(PIECE_STORE_TYPE(board[startPoint], PIECE_TYPE_KING))
		return king_pattern_moves(moves, moveAmount, board, stopPoint);

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
