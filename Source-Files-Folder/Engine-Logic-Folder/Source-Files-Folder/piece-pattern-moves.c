
#include "../Header-Files-Folder/englog-include-file.h"

bool piece_pattern_moves(Move** moveArray, int* moveAmount, const Piece board[], Point piecePoint)
{
  if(!POINT_INSIDE_BOARD(piecePoint)) return false;

  if(PIECE_STORE_TYPE(board[piecePoint], PIECE_TYPE_PAWN))
    return pawn_pattern_moves(moveArray, moveAmount, board, piecePoint);

	if(PIECE_STORE_TYPE(board[piecePoint], PIECE_TYPE_KNIGHT))
    return knight_pattern_moves(moveArray, moveAmount, board, piecePoint);

	if(PIECE_STORE_TYPE(board[piecePoint], PIECE_TYPE_BISHOP))
    return bishop_pattern_moves(moveArray, moveAmount, board, piecePoint);

	if(PIECE_STORE_TYPE(board[piecePoint], PIECE_TYPE_ROOK))
    return rook_pattern_moves(moveArray, moveAmount, board, piecePoint);

	if(PIECE_STORE_TYPE(board[piecePoint], PIECE_TYPE_QUEEN))
    return queen_pattern_moves(moveArray, moveAmount, board, piecePoint);

	if(PIECE_STORE_TYPE(board[piecePoint], PIECE_TYPE_KING))
    return king_pattern_moves(moveArray, moveAmount, board, piecePoint);

	return false;
}

bool pawn_pattern_moves(Move** moveArray, int* moveAmount, const Piece board[], Point piecePoint)
{
  if(!POINT_INSIDE_BOARD(piecePoint)) return false;

	*moveArray = create_move_array(4); *moveAmount = 0;

  uint8_t pieceRank = POINT_RANK_MACRO(piecePoint);
  uint8_t pieceFile = POINT_FILE_MACRO(piecePoint);

  uint8_t team = BOARD_POINT_TEAM(board, piecePoint);

  append_pawn_pmoves(*moveArray, moveAmount, team, piecePoint, pieceRank, pieceFile);

	return true;
}

void append_pawn_pmoves(Move* moveArray, int* moveAmount, uint8_t team, Point piecePoint, uint8_t pieceRank, uint8_t pieceFile)
{
  for(uint8_t rank = 0; rank < 2; rank += 1)
	{
		for(uint8_t file = 0; file < 3; file += 1)
		{
      append_pawn_pmove(moveArray, moveAmount, team, piecePoint, pieceRank, pieceFile, rank, file);
		}
	}
}

bool append_pawn_pmove(Move* moveArray, int* moveAmount, uint8_t team, Point piecePoint, uint8_t pieceRank, uint8_t pieceFile, uint8_t rank, uint8_t file)
{
  if(rank == 1 && (file == 0 || file == 2) ) return false;

  int8_t realRank = pieceRank + (rank + 1) * ((team == TEAM_WHITE) ? WHITE_MOVE_VALUE : BLACK_MOVE_VALUE);
  int8_t realFile = (pieceFile - 1) + file;

  if(!RANK_FILE_INSIDE(realRank, realFile)) return false;

  Point point = RANK_FILE_POINT(realRank, realFile);
  Move move = START_STOP_MOVE(piecePoint, point);

  moveArray[(*moveAmount)++] = move; return true;
}

bool knight_pattern_moves(Move** moveArray, int* moveAmount, const Piece board[], Point piecePoint)
{
  if(!POINT_INSIDE_BOARD(piecePoint)) return false;

  *moveArray = create_move_array(8); *moveAmount = 0;

  uint8_t pieceRank = POINT_RANK_MACRO(piecePoint);
  uint8_t pieceFile = POINT_FILE_MACRO(piecePoint);

  append_knight_pmoves(*moveArray, moveAmount, piecePoint, pieceRank, pieceFile);

  return true;
}

void append_knight_pmoves(Move* moveArray, int* moveAmount, Point piecePoint, uint8_t pieceRank, uint8_t pieceFile)
{
  for(uint8_t rank = 0; rank < 5; rank += 1)
	{
		for(uint8_t file = 0; file < 5; file += 1)
		{
      append_knight_pmove(moveArray, moveAmount, piecePoint, pieceRank, pieceFile, rank, file);
		}
	}
}

bool append_knight_pmove(Move* moveArray, int* moveAmount, Point piecePoint, uint8_t pieceRank, uint8_t pieceFile, uint8_t rank, uint8_t file)
{
  if(rank == file || (rank + file) == 4) return false;
  if(rank == 2 || file == 2) return false;

  int8_t realRank = (pieceRank - 2) + rank;
  int8_t realFile = (pieceFile - 2) + file;

  if(!RANK_FILE_INSIDE(realRank, realFile)) return false;

  Point point = RANK_FILE_POINT(realRank, realFile);
  Move move = START_STOP_MOVE(piecePoint, point);

  moveArray[(*moveAmount)++] = move; return true;
}

bool straight_pattern_moves(Move** moveArray, int* moveAmount, const Piece board[], Point piecePoint)
{
  if(!POINT_INSIDE_BOARD(piecePoint)) return false;

  *moveArray = create_move_array(14); *moveAmount = 0;

  uint8_t pieceRank = POINT_RANK_MACRO(piecePoint);
  uint8_t pieceFile = POINT_FILE_MACRO(piecePoint);

  append_s1type_pmoves(*moveArray, moveAmount, piecePoint, pieceFile);

  append_s2type_pmoves(*moveArray, moveAmount, piecePoint, pieceRank);

  return true;
}

void append_s1type_pmoves(Move* moveArray, int* moveAmount, Point piecePoint, uint8_t pieceFile)
{
  for(uint8_t rank = 0; rank < BOARD_RANKS; rank += 1)
	{
    Point point = RANK_FILE_POINT(rank, pieceFile);
    if(piecePoint == point) continue;

		Move move = START_STOP_MOVE(piecePoint, point);

    moveArray[(*moveAmount)++] = move;
	}
}

void append_s2type_pmoves(Move* moveArray, int* moveAmount, Point piecePoint, uint8_t pieceRank)
{
  for(uint8_t file = 0; file < BOARD_FILES; file += 1)
	{
		Point point = RANK_FILE_POINT(pieceRank, file);
    if(piecePoint == point) continue;

		Move move = START_STOP_MOVE(piecePoint, point);

    moveArray[(*moveAmount)++] = move;
	}
}

bool diagonal_pattern_moves(Move** moveArray, int* moveAmount, const Piece board[], Point piecePoint)
{
  if(!POINT_INSIDE_BOARD(piecePoint)) return false;

  *moveArray = create_move_array(14); *moveAmount = 0;

  uint8_t pieceRank = POINT_RANK_MACRO(piecePoint);
  uint8_t pieceFile = POINT_FILE_MACRO(piecePoint);

  append_d1type_pmoves(*moveArray, moveAmount, piecePoint, pieceRank, pieceFile);

  append_d2type_pmoves(*moveArray, moveAmount, piecePoint, pieceRank, pieceFile);

  return true;
}

void append_d2type_pmoves(Move* moveArray, int* moveAmount, Point piecePoint, uint8_t pieceRank, uint8_t pieceFile)
{
  for(int8_t index = -8; index <= 16; index += 1)
	{
    int8_t realRank = (pieceRank + index);
    int8_t realFile = (pieceFile - index);

    append_diagonal_pmove(moveArray, moveAmount, piecePoint, realRank, realFile);
	}
}

void append_d1type_pmoves(Move* moveArray, int* moveAmount, Point piecePoint, uint8_t pieceRank, uint8_t pieceFile)
{
  for(int8_t index = -8; index <= 16; index += 1)
	{
    int8_t realRank = (pieceRank + index);
    int8_t realFile = (pieceFile + index);

    append_diagonal_pmove(moveArray, moveAmount, piecePoint, realRank, realFile);
	}
}

bool append_diagonal_pmove(Move* moveArray, int* moveAmount, Point piecePoint, uint8_t realRank, uint8_t realFile)
{
  if(!RANK_FILE_INSIDE(realRank, realFile)) return false;

  Point point = RANK_FILE_POINT(realRank, realFile);
  if(piecePoint == point) return false;

  Move move = START_STOP_MOVE(piecePoint, point);

  moveArray[(*moveAmount)++] = move; return true;
}

bool rook_pattern_moves(Move** moveArray, int* moveAmount, const Piece board[], Point piecePoint)
{
  if(!POINT_INSIDE_BOARD(piecePoint)) return false;

  *moveArray = create_move_array(14); *moveAmount = 0;

  Move* straightMoves; int addingAmount;
  if(straight_pattern_moves(&straightMoves, &addingAmount, board, piecePoint))
  {
    append_move_array(*moveArray, moveAmount, straightMoves, addingAmount);

    free(straightMoves);
  }
  return true;
}

bool bishop_pattern_moves(Move** moveArray, int* moveAmount, const Piece board[], Point piecePoint)
{
  if(!POINT_INSIDE_BOARD(piecePoint)) return false;

  *moveArray = create_move_array(14); *moveAmount = 0;

  Move* diagonalMoves; int addingAmount;
  if(diagonal_pattern_moves(&diagonalMoves, &addingAmount, board, piecePoint))
  {
  	append_move_array(*moveArray, moveAmount, diagonalMoves, addingAmount);

    free(diagonalMoves);
  }
  return true;
}

bool queen_pattern_moves(Move** moveArray, int* moveAmount, const Piece board[], Point piecePoint)
{
  if(!POINT_INSIDE_BOARD(piecePoint)) return false;

  *moveArray = create_move_array(28); *moveAmount = 0;

  Move* diagonalMoves; int addingAmount;
  if(diagonal_pattern_moves(&diagonalMoves, &addingAmount, board, piecePoint))
  {
  	append_move_array(*moveArray, moveAmount, diagonalMoves, addingAmount);

    free(diagonalMoves);
  }

  Move* straightMoves;
  if(straight_pattern_moves(&straightMoves, &addingAmount, board, piecePoint))
  {
    append_move_array(*moveArray, moveAmount, straightMoves, addingAmount);

    free(straightMoves);
  }
  return true;
}

bool king_pattern_moves(Move** moveArray, int* moveAmount, const Piece board[], Point piecePoint)
{
  if(!POINT_INSIDE_BOARD(piecePoint)) return false;

  *moveArray = create_move_array(10); *moveAmount = 0;

  uint8_t pieceRank = POINT_RANK_MACRO(piecePoint);
  uint8_t pieceFile = POINT_FILE_MACRO(piecePoint);

  append_king_pmoves(*moveArray, moveAmount, piecePoint, pieceRank, pieceFile);

	return true;
}

void append_king_pmoves(Move* moveArray, int* moveAmount, Point piecePoint, uint8_t pieceRank, uint8_t pieceFile)
{
  for(uint8_t rank = 0; rank < 3; rank += 1)
	{
		for(uint8_t file = 0; file < 5; file += 1)
		{
      append_king_pmove(moveArray, moveAmount, piecePoint, pieceRank, pieceFile, rank, file);
		}
	}
}

bool append_king_pmove(Move* moveArray, int* moveAmount, Point piecePoint, uint8_t pieceRank, uint8_t pieceFile, uint8_t rank, uint8_t file)
{
  if((file == 0 || file == 4) && rank != 1) return false;

  int8_t realRank = (pieceRank - 1) + rank;
  int8_t realFile = (pieceFile - 2) + file;

  if(!RANK_FILE_INSIDE(realRank, realFile)) return false;

  Point point = RANK_FILE_POINT(realRank, realFile);
  if(piecePoint == point) return false;

  Move move = START_STOP_MOVE(piecePoint, point);

  moveArray[(*moveAmount)++] = move; return true;
}
