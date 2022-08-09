
#include "../Header-Files-Folder/screen-include-file.h"

bool render_chess_board(Screen screen, const Piece board[], Info info, const Move moveArray[], bool inverted)
{
	if(!render_board_squares(screen, inverted)) return false;

	if(!render_latest_move(screen, moveArray, inverted)) return false;

	if(!render_check_squares(screen, board, info, inverted)) return false;

	if(!render_board_pieces(screen, board, inverted)) return false;

	return true;
}

bool render_move_board(Screen screen, const Piece board[], Info info, const Move moveArray[], Point point, bool inverted)
{
	if(!render_board_squares(screen, inverted)) return false;

	if(!render_latest_move(screen, moveArray, inverted)) return false;

	if(!render_check_squares(screen, board, info, inverted)) return false;


	if(!render_move_squares(screen, board, info, point, inverted)) return false;


	if(!render_board_pieces(screen, board, inverted)) return false;

	return true;
}

bool render_mark_board(Screen screen, const Piece board[], Info info, const Move moveArray[], const Point markPoints[], bool inverted)
{
	if(!render_board_squares(screen, inverted)) return false;

	if(!render_latest_move(screen, moveArray, inverted)) return false;

	if(!render_check_squares(screen, board, info, inverted)) return false;


	if(!render_board_pieces(screen, board, inverted)) return false;


	if(!render_input_marks(screen, markPoints, inverted)) return false;

	return true;
}

bool render_promote_board(Screen screen, unsigned short team)
{
	Piece pieceTeam = TEAM_PIECE_MACRO(team);

	if(!render_board_squares(screen, false)) return false;

	if(!render_board_piece(screen, (PIECE_TYPE_KNIGHT | pieceTeam), PROM_KNIGHT_POINT, false)) return false;

	if(!render_board_piece(screen, (PIECE_TYPE_BISHOP | pieceTeam), PROM_BISHOP_POINT, false)) return false;

	if(!render_board_piece(screen, (PIECE_TYPE_ROOK | pieceTeam), PROM_ROOK_POINT, false)) return false;

	if(!render_board_piece(screen, (PIECE_TYPE_QUEEN | pieceTeam), PROM_QUEEN_POINT, false)) return false;

	return true;
}

bool render_result_board(Screen screen, const Piece board[], Info info, bool inverted)
{
	unsigned short team = INFO_TEAM_MACRO(info);
	unsigned short winningTeam = normal_team_enemy(team);

	if(check_mate_ending(board, info, team))
	{
		if(!render_team_squares(screen, winningTeam, inverted)) return false;
	}
	else if(check_draw_ending(board, info, team))
	{
		if(!render_board_squares(screen, inverted)) return false;
	}
	else return false; // The game has not ended

	if(!render_check_squares(screen, board, info, inverted)) return false;

	if(!render_board_pieces(screen, board, inverted)) return false;

	return true;
}

// ############################################################################################

bool render_input_marks(Screen screen, const Point markPoints[], bool inverted)
{
	Surface* image;

	if(!extract_file_image(&image, MARK_SQUARE_FILE)) return false;

	unsigned short amount = point_array_amount(markPoints);

	for(int index = 0; index < amount; index += 1)
	{
		Point point = markPoints[index];

		if(!render_point_image(screen, image, point, 255, inverted)) return false;
	}
	return true;
}

bool render_team_squares(Screen screen, unsigned short team, bool inverted)
{
	Surface* squareImage;

	if(!extract_team_square(&squareImage, team)) return false;

	for(Point point = 0; point < BOARD_LENGTH; point += 1)
	{
		if(!render_point_image(screen, squareImage, point, 255, inverted)) return false;
	}
  return true;
}

bool render_board_pieces(Screen screen, const Piece board[], bool inverted)
{
	for(Point point = 0; point < BOARD_LENGTH; point += 1)
	{
		if(!chess_piece_exists(board[point])) continue;

		if(!render_board_piece(screen, board[point], point, inverted)) return false;
	}
	return true;
}

bool render_board_piece(Screen screen, Piece piece, Point point, bool inverted)
{
	if(!chess_piece_exists(piece)) return false;

	Surface* pieceImage;

	if(!extract_piece_image(&pieceImage, piece)) return false;

	if(!render_point_image(screen, pieceImage, point, 255, inverted)) return false;

	return true;
}

bool render_check_square(Screen screen, const Piece board[], Info info, Point kingPoint, bool inverted)
{
	if(!king_inside_check(board, info, kingPoint)) return true;

	Surface* checkSquare;

	if(!extract_file_image(&checkSquare, CHECK_SQUARE_FILE)) return false;

	if(!render_point_image(screen, checkSquare, kingPoint, 255, inverted)) return false;

	return true;
}

bool render_check_squares(Screen screen, const Piece board[], Info info, bool inverted)
{
	Point whiteKing = board_king_point(board, TEAM_WHITE);
	Point blackKing = board_king_point(board, TEAM_BLACK);

	if(!render_check_square(screen, board, info, whiteKing, inverted)) return false;

	if(!render_check_square(screen, board, info, blackKing, inverted)) return false;

	return true;
}

bool render_move_squares(Screen screen, const Piece board[], Info info, Point point, bool inverted)
{
	if(!POINT_INSIDE_BOARD(point)) return true;

	unsigned short team = PIECE_TEAM_MACRO(board[point]);

	if(!current_team_move(info, team)) return false;


	Point* pointArray;
	if(!piece_legal_points(&pointArray, board, info, point)) return true;

  unsigned short pointAmount = point_array_amount(pointArray);


	if(pointAmount <= 0) { free(pointArray); return false; }


  Surface* moveSquare;

	if(!extract_file_image(&moveSquare, MOVE_SQUARE_FILE))
	{
		free(pointArray); return false;
	}


	for(unsigned short index = 0; index < pointAmount; index += 1)
	{
		Point stopPoint = pointArray[index];

		if(!render_point_image(screen, moveSquare, stopPoint, 255, inverted))
		{
      free(pointArray); return false;
		}
	}
	free(pointArray); return true;
}

bool render_latest_move(Screen screen, const Move moveArray[], bool inverted)
{
	unsigned short moveAmount = move_array_amount(moveArray);

	if(moveAmount <= 0) return true;


	Surface* movedSquare;

	if(!extract_file_image(&movedSquare, MOVED_SQUARE_FILE)) return false;


  if(!render_board_move(screen, movedSquare, moveArray[moveAmount - 1], 255, inverted)) return false;

  return true;
}

bool render_engine_moves(Screen screen, const Move engineMoves[], bool inverted)
{
	unsigned short moveAmount = move_array_amount(engineMoves);

	Surface* movedSquare;

	if(!extract_file_image(&movedSquare, MOVED_SQUARE_FILE)) return false;

	for(unsigned short index = 0; index < moveAmount; index += 1)
	{
		if(!render_board_move(screen, movedSquare, engineMoves[index], 255, inverted)) return false;
	}
	return true;
}

bool render_board_squares(Screen screen, bool inverted)
{
	Surface* whiteSquare, *blackSquare;

	if(!extract_file_image(&whiteSquare, WHITE_SQUARE_FILE)) return false;

  if(!extract_file_image(&blackSquare, BLACK_SQUARE_FILE)) return false;

	for(Point point = 0; point < BOARD_LENGTH; point += 1)
	{
		unsigned short rank = POINT_RANK_MACRO(point);
		unsigned short file = POINT_FILE_MACRO(point);

		Surface* image = (rank + file) % 2 == 0 ? whiteSquare : blackSquare;

		if(!render_point_image(screen, image, point, 255, inverted)) return false;
	}

  return true;
}

bool render_board_move(Screen screen, Surface* moveImage, Move move, Uint8 opacity, bool inverted)
{
	Point stopPoint = MOVE_STOP_MACRO(move);
	Point startPoint = MOVE_START_MACRO(move);

	if(!render_point_image(screen, moveImage, stopPoint, opacity, inverted)) return false;

	if(!render_point_image(screen, moveImage, startPoint, opacity, inverted)) return false;

	return true;
}

bool render_point_image(Screen screen, Surface* image, Point point, Uint8 opacity, bool inverted)
{
	Rect position;

	if(!board_point_position(&position, screen, point, inverted)) return false;

	if(!render_screen_image(screen.render, image, position, opacity)) return false;

	return true;
}

bool render_screen_image(Render* render, Surface* surface, Rect position, Uint8 opacity)
{
	Texture* texture = NULL;

	if(!create_surface_texture(&texture, render, surface)) return false;

	SDL_SetTextureAlphaMod(texture, opacity);


	SDL_RenderCopy(render, texture, NULL, &position);


	SDL_DestroyTexture(texture);

	return true;
}
