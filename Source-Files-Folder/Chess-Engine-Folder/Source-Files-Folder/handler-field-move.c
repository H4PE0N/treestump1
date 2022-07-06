
#include "../Header-Files-Folder/engine-include-file.h"

Piece start_piece_type(Move move, const Piece board[])
{
	if(!move_inside_board(move)) return PIECE_TYPE_NONE;

	return point_piece_type(MOVE_START_MACRO(move), board);
}

Piece move_start_piece(Move move, const Piece board[])
{
	if(!move_inside_board(move)) return PIECE_NONE;

	return board[MOVE_START_MACRO(move)];
}

Piece move_stop_piece(Move move, const Piece board[])
{
	if(!move_inside_board(move)) return PIECE_NONE;

	return board[MOVE_STOP_MACRO(move)];
}

Move start_stop_move(Point start, Point stop)
{
	return (START_MOVE_MACRO(start) | STOP_MOVE_MACRO(stop));
}

unsigned short move_array_amount(const Move moveArray[])
{
	unsigned short movesAmount = 0;

	while(moveArray[movesAmount] != MOVE_NONE && moveArray[movesAmount] >= 0)
	{
		movesAmount += 1;
	}

	return movesAmount;
}

void append_moves_array(Move* moves, const Move adding[])
{
	int movesAmount = move_array_amount(moves);
	int addingAmount = move_array_amount(adding);

	for(unsigned short index = 0; index < addingAmount; index += 1)
	{
		moves[movesAmount + index] = adding[index];
	}
}

Move* create_move_array(unsigned short arrayLength)
{
	Move* moveArray = malloc(sizeof(Move) * (arrayLength + 1));

	for(unsigned short index = 0; index < (arrayLength + 1); index += 1)
	{
		moveArray[index] = MOVE_NONE;
	}
	return moveArray;
}

bool move_inside_board(Move move)
{
	if(move == MOVE_NONE || move < 0) return false;

	Point startPoint = MOVE_START_MACRO(move);
	Point stopPoint = MOVE_STOP_MACRO(move);

	bool startPointInside = point_inside_board(startPoint);
	bool stopPointInside = point_inside_board(stopPoint);

	return (startPointInside && stopPointInside);
}

bool move_points_team(const Piece board[], Move move)
{
	Point startPoint = MOVE_START_MACRO(move);
	Point stopPoint = MOVE_STOP_MACRO(move);

	return board_points_team(board, startPoint, stopPoint);
}

bool move_points_enemy(const Piece board[], Move move)
{
	Point startPoint = MOVE_START_MACRO(move);
	Point stopPoint = MOVE_STOP_MACRO(move);

	return board_points_enemy(board, startPoint, stopPoint);
}

short move_file_offset(Move move, unsigned short team)
{
	Point startPoint = MOVE_START_MACRO(move);
	Point stopPoint = MOVE_STOP_MACRO(move);

	unsigned short startFile = POINT_FILE_MACRO(startPoint);
	unsigned short stopFile = POINT_FILE_MACRO(stopPoint);

	signed short fileOffset = (stopFile - startFile);

	if(team == TEAM_WHITE) return fileOffset;// * WHITE_MOVE_VALUE;

	if(team == TEAM_BLACK) return fileOffset;// * BLACK_MOVE_VALUE;

	return SHORT_NONE;
}

short move_rank_offset(Move move, unsigned short team)
{
	Point startPoint = MOVE_START_MACRO(move);
	Point stopPoint = MOVE_STOP_MACRO(move);

	unsigned short startRank = POINT_RANK_MACRO(startPoint);
	unsigned short stopRank = POINT_RANK_MACRO(stopPoint);

	signed short rankOffset = (stopRank - startRank);

	if(team == TEAM_WHITE) return rankOffset * WHITE_MOVE_VALUE;

	if(team == TEAM_BLACK) return rankOffset * BLACK_MOVE_VALUE;

	return SHORT_NONE;
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

signed short board_move_pattern(Move move)
{
	Point startPoint = MOVE_START_MACRO(move);
	Point stopPoint = MOVE_STOP_MACRO(move);

	return (stopPoint - startPoint);
}

bool create_move_string(char* moveString, const Piece board[], Info info, Kings kings, Move move)
{
	if(move == MOVE_NONE || move < 0)
	{
		*moveString = '\0';

		return true;
	}

	Point startPoint = MOVE_START_MACRO(move);
	Point stopPoint = MOVE_STOP_MACRO(move);

	unsigned short type = PIECE_TYPE_MACRO(board[startPoint]);

	Piece pieceTeam = (board[startPoint] & PIECE_TEAM_MASK);

	unsigned short stopFile = POINT_FILE_MACRO(stopPoint);


	char pieceSymbol = '\0';
	char stopPointString[10];
	char checkSymbol = '\0';
	char mateSymbol = '\0';
	char captureSymbol = '\0';


	if(pieceTeam == PIECE_TEAM_WHITE) pieceSymbol = WHITE_MOVE_SYMBOLS[type];
	else if(pieceTeam == PIECE_TEAM_BLACK) pieceSymbol = BLACK_MOVE_SYMBOLS[type];

	if(!create_point_string(stopPointString, stopPoint))
	{
		printf("if(!create_point_string(stopPointString, stopPoint))\n");
	}

	if(move_deliver_mate(board, info, kings, move))
	{
		mateSymbol = '#';
	}
	else if(move_deliver_check(board, info, kings, move))
	{
		checkSymbol = '+';
	}

	if(board_points_enemy(board, startPoint, stopPoint) || (INFO_PASSANT_MACRO(info) == (stopFile + 1) ))
	{
		captureSymbol = 'x';
	}



	sprintf(moveString, "%s%s%s%s%s",
		(char[]) {pieceSymbol, '\0'},
		(char[]) {captureSymbol, '\0'},
		stopPointString,
		(char[]) {checkSymbol, '\0'},
		(char[]) {mateSymbol, '\0'}
	);

	//sprintf(moveString, "%c%c%s%c", pieceSymbol, speciallChar1, stopPointString, speciallChar2);

	return true;
}

bool create_point_string(char* pointString, Point point)
{
	unsigned short file = POINT_FILE_MACRO(point);
	unsigned short rank = POINT_RANK_MACRO(point);

	sprintf(pointString, "%c%c", FILE_SYMBOLS[file], RANK_SYMBOLS[rank]);

	return true;
}

signed short move_offset_factor(signed short moveOffset)
{
	return (moveOffset == 0 ? 0 : (moveOffset > 0 ? 1 : -1) );
}
