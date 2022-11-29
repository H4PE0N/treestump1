
#include "../Header-Files-Folder/englog-include-file.h"

bool piece_pattern_moves(Move** moves, short* moveAmount, const Piece board[], Point piecePoint)
{
  if(!POINT_INSIDE_BOARD(piecePoint)) return false;

  if(PIECE_STORE_TYPE(board[piecePoint], PIECE_TYPE_PAWN))
    return pawn_pattern_moves(moves, moveAmount, board, piecePoint);

	if(PIECE_STORE_TYPE(board[piecePoint], PIECE_TYPE_KNIGHT))
    return knight_pattern_moves(moves, moveAmount, board, piecePoint);

	if(PIECE_STORE_TYPE(board[piecePoint], PIECE_TYPE_BISHOP))
    return bishop_pattern_moves(moves, moveAmount, board, piecePoint);

	if(PIECE_STORE_TYPE(board[piecePoint], PIECE_TYPE_ROOK))
    return rook_pattern_moves(moves, moveAmount, board, piecePoint);

	if(PIECE_STORE_TYPE(board[piecePoint], PIECE_TYPE_QUEEN))
    return queen_pattern_moves(moves, moveAmount, board, piecePoint);

	if(PIECE_STORE_TYPE(board[piecePoint], PIECE_TYPE_KING))
    return king_pattern_moves(moves, moveAmount, board, piecePoint);

	return false;
}

bool pawn_pattern_moves(Move** moves, short* moveAmount, const Piece board[], Point piecePoint)
{
  if(!POINT_INSIDE_BOARD(piecePoint)) return false;

	*moves = create_move_array(4); *moveAmount = 0;

  unsigned short pieceRank = POINT_RANK_MACRO(piecePoint);
  unsigned short pieceFile = POINT_FILE_MACRO(piecePoint);

  unsigned short team = BOARD_POINT_TEAM(board, piecePoint);

	for(unsigned short rank = 0; rank < 2; rank += 1)
	{
		for(unsigned short file = 0; file < 3; file += 1)
		{
			if(rank == 1 && (file == 0 || file == 2) ) continue;

      // This here should be a seperate function:
      short realRank = pieceRank + (rank + 1) * ((team == TEAM_WHITE) ? WHITE_MOVE_VALUE : BLACK_MOVE_VALUE);
			short realFile = (pieceFile - 1) + file;

      if(!RANK_FILE_INSIDE(realRank, realFile)) continue;

			Point point = RANK_FILE_POINT(realRank, realFile);

			(*moves)[(*moveAmount)++] = START_STOP_MOVE(piecePoint, point);
		}
	}
	return true;
}

bool knight_pattern_moves(Move** moves, short* moveAmount, const Piece board[], Point piecePoint)
{
  if(!POINT_INSIDE_BOARD(piecePoint)) return false;

  *moves = create_move_array(8); *moveAmount = 0;

  unsigned short pieceRank = POINT_RANK_MACRO(piecePoint);
  unsigned short pieceFile = POINT_FILE_MACRO(piecePoint);

	for(unsigned short rank = 0; rank < 5; rank += 1)
	{
		for(unsigned short file = 0; file < 5; file += 1)
		{
			if(rank == file || (rank + file) == 4) continue;
			if(rank == 2 || file == 2) continue;

			short realRank = (pieceRank - 2) + rank;
			short realFile = (pieceFile - 2) + file;

			if(!RANK_FILE_INSIDE(realRank, realFile)) continue;

			Point point = RANK_FILE_POINT(realRank, realFile);

      (*moves)[(*moveAmount)++] = START_STOP_MOVE(piecePoint, point);
		}
	}
  return true;
}

bool straight_pattern_moves(Move** moves, short* moveAmount, const Piece board[], Point piecePoint)
{
  if(!POINT_INSIDE_BOARD(piecePoint)) return false;

  *moves = create_move_array(14); *moveAmount = 0;

  unsigned short pieceRank = POINT_RANK_MACRO(piecePoint);
  unsigned short pieceFile = POINT_FILE_MACRO(piecePoint);

  for(unsigned short rank = 0; rank < BOARD_RANKS; rank += 1)
	{
    Point point = RANK_FILE_POINT(rank, pieceFile);
    if(piecePoint == point) continue;

		(*moves)[(*moveAmount)++] = START_STOP_MOVE(piecePoint, point);
	}

	for(unsigned short file = 0; file < BOARD_FILES; file += 1)
	{
		Point point = RANK_FILE_POINT(pieceRank, file);
    if(piecePoint == point) continue;

		(*moves)[(*moveAmount)++] = START_STOP_MOVE(piecePoint, point);
	}
  return true;
}

bool diagonal_pattern_moves(Move** moves, short* moveAmount, const Piece board[], Point piecePoint)
{
  if(!POINT_INSIDE_BOARD(piecePoint)) return false;

  *moves = create_move_array(14); *moveAmount = 0;

  unsigned short pieceRank = POINT_RANK_MACRO(piecePoint);
  unsigned short pieceFile = POINT_FILE_MACRO(piecePoint);

  for(short index = -8; index <= 16; index += 1)
	{
		short realRank = (pieceRank + index);
		short realFile = (pieceFile + index);

    if(!RANK_FILE_INSIDE(realRank, realFile)) continue;

		Point point = RANK_FILE_POINT(realRank, realFile);
    if(piecePoint == point) continue;

    (*moves)[(*moveAmount)++] = START_STOP_MOVE(piecePoint, point);
	}

	for(short index = -8; index <= 16; index += 1)
	{
		short realRank = (pieceRank + index);
		short realFile = (pieceFile - index);

    if(!RANK_FILE_INSIDE(realRank, realFile)) continue;

		Point point = RANK_FILE_POINT(realRank, realFile);
    if(piecePoint == point) continue;

    (*moves)[(*moveAmount)++] = START_STOP_MOVE(piecePoint, point);
	}
  return true;
}

bool rook_pattern_moves(Move** moves, short* moveAmount, const Piece board[], Point piecePoint)
{
  if(!POINT_INSIDE_BOARD(piecePoint)) return false;

  *moves = create_move_array(14); *moveAmount = 0;

  Move* straightMoves; short addingAmount;
  if(straight_pattern_moves(&straightMoves, &addingAmount, board, piecePoint))
  {
    append_move_array(*moves, moveAmount, straightMoves, addingAmount);

    free(straightMoves);
  }
  return true;
}

bool bishop_pattern_moves(Move** moves, short* moveAmount, const Piece board[], Point piecePoint)
{
  if(!POINT_INSIDE_BOARD(piecePoint)) return false;

  *moves = create_move_array(14); *moveAmount = 0;

  Move* diagonalMoves; short addingAmount;
  if(diagonal_pattern_moves(&diagonalMoves, &addingAmount, board, piecePoint))
  {
  	append_move_array(*moves, moveAmount, diagonalMoves, addingAmount);

    free(diagonalMoves);
  }
  return true;
}

bool queen_pattern_moves(Move** moves, short* moveAmount, const Piece board[], Point piecePoint)
{
  if(!POINT_INSIDE_BOARD(piecePoint)) return false;

  *moves = create_move_array(28); *moveAmount = 0;

  Move* diagonalMoves; short addingAmount;
  if(diagonal_pattern_moves(&diagonalMoves, &addingAmount, board, piecePoint))
  {
  	append_move_array(*moves, moveAmount, diagonalMoves, addingAmount);

    free(diagonalMoves);
  }

  Move* straightMoves;
  if(straight_pattern_moves(&straightMoves, &addingAmount, board, piecePoint))
  {
    append_move_array(*moves, moveAmount, straightMoves, addingAmount);

    free(straightMoves);
  }
  return true;
}

bool king_pattern_moves(Move** moves, short* moveAmount, const Piece board[], Point piecePoint)
{
  if(!POINT_INSIDE_BOARD(piecePoint)) return false;

  *moves = create_move_array(10); *moveAmount = 0;

  unsigned short pieceRank = POINT_RANK_MACRO(piecePoint);
  unsigned short pieceFile = POINT_FILE_MACRO(piecePoint);

  for(unsigned short rank = 0; rank < 3; rank += 1)
	{
		for(unsigned short file = 0; file < 5; file += 1)
		{
      if((file == 0 || file == 4) && rank != 1) continue;

			short realRank = (pieceRank - 1) + rank;
			short realFile = (pieceFile - 2) + file;

      if(!RANK_FILE_INSIDE(realRank, realFile)) continue;

      Point point = RANK_FILE_POINT(realRank, realFile);
      if(piecePoint == point) continue;

			(*moves)[(*moveAmount)++] = START_STOP_MOVE(piecePoint, point);
		}
	}
	return true;
}
