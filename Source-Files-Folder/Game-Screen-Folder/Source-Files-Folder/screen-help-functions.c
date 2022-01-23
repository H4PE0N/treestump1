
#include "../Header-Files-Folder/game-screen-includer.h"

bool render_board_image(Renderer* renderer, Surface* surface, Rect position, Uint8 opacity)
{
	Texture* texture = NULL;

	if(!create_surface_texture(&texture, renderer, surface))
	{
		return false;
	}

	SDL_SetTextureAlphaMod(texture, opacity);


	SDL_RenderCopy(renderer, texture, NULL, &position);


	SDL_DestroyTexture(texture);

	return true;
}

bool load_filename_image(Surface** image, char filename[])
{
	*image = IMG_Load(filename);

	return (*image != NULL);
}

const char* teamWords[] = {"none", "white", "black"};
const char* typeWords[] = {"none", "pawn", "knight", "bishop", "rook", "queen", "king"};

bool extract_piece_image(Surface** image, Piece piece)
{
	char* filename;

	if(!extract_piece_file(&filename, piece))
	{
		return false;
	}

	if(!load_filename_image(image, filename))
	{
		free(filename);

		return false;
	}

	free(filename);

	return true;
}

bool extract_piece_file(char** filename, Piece piece)
{
	*filename = malloc(sizeof(char) * 128);

	unsigned short team = PIECE_TEAM_MACRO(piece);
	unsigned short type = PIECE_TYPE_MACRO(piece);

	const char* teamWord = teamWords[team];
	const char* typeWord = typeWords[type];

	sprintf(*filename, "%s/%s-%s.png", PIECE_FOLDER, teamWord, typeWord);

	return true;
}

bool render_board_move(Screen screen, Surface* moveImage, Move move, Uint8 opacity)
{
	Point stopPoint = MOVE_STOP_MACRO(move);
	Point startPoint = MOVE_START_MACRO(move);

	if(!render_point_image(screen, moveImage, stopPoint, opacity))
	{
		return false;
	}

	if(!render_point_image(screen, moveImage, startPoint, opacity))
	{
		return false;
	}

	return true;
}

bool render_point_image(Screen screen, Surface* image, Point point, Uint8 opacity)
{
	Rect position;

	if(!board_point_position(&position, screen, point))
	{
		return false;
	}

	if(!render_board_image(screen.renderer, image, position, opacity))
	{
		return false;
	}

	return true;
}

bool board_point_position(Rect* position, Screen screen, Point point)
{
	if(!point_inside_board(point)) return false;

	unsigned short rank = POINT_RANK_MACRO(point);
	unsigned short file = POINT_FILE_MACRO(point);

	float squareWidth = (screen.width / BOARD_FILES);
	float squareHeight = (screen.height / BOARD_RANKS);

	float realHeight = squareHeight * rank;
	float realWidth = squareWidth * file;

	*position = (Rect) {realWidth, realHeight, squareWidth, squareHeight};

	return true;
}

Point parse_mouse_point(Event event, Screen screen)
{
	float squareWidth = (screen.width / BOARD_FILES);
	float squareHeight = (screen.height / BOARD_RANKS);

	unsigned short file = (unsigned short) floor( (float) event.motion.x / squareWidth);
	unsigned short rank = (unsigned short) floor( (float) event.motion.y / squareHeight);

	if(!NUMBER_IN_BOUNDS(file, 0, BOARD_FILES)) return POINT_NONE;

	if(!NUMBER_IN_BOUNDS(rank, 0, BOARD_RANKS)) return POINT_NONE;

	Point point = FILE_POINT_MACRO(file) | RANK_POINT_MACRO(rank);

	return point;
}
