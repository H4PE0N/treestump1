
#include "../Header-Files-Folder/game-screen-includer.h"

bool create_surface_texture(Texture** texture, Render* render, Surface* surface)
{
  *texture = SDL_CreateTextureFromSurface(render, surface);

	return (texture != NULL);
}

bool extract_path_image(Surface** image, const char filePath[])
{
	*image = IMG_Load(filePath);

	return (*image != NULL);
}

bool extract_file_image(Image** image, const char filename[])
{
	char filePath[256];

	sprintf(filePath, "%s/%s", PIECE_FOLDER, filename);

	return extract_path_image(image, filePath);
}

const char* teamWords[] = {"none", "white", "black"};
const char* typeWords[] = {"none", "pawn", "knight", "bishop", "rook", "queen", "king"};

bool extract_piece_image(Surface** image, Piece piece)
{
	char* filename;

	if(!extract_piece_path(&filename, piece))
	{
		return false;
	}

	if(!extract_path_image(image, filename))
	{
		free(filename);

		return false;
	}

	free(filename);

	return true;
}

bool extract_piece_path(char** filePath, Piece piece)
{
	*filePath = malloc(sizeof(char) * 256);

	unsigned short team = PIECE_TEAM_MACRO(piece);
	unsigned short type = PIECE_TYPE_MACRO(piece);

	const char* teamWord = teamWords[team];
	const char* typeWord = typeWords[type];

	sprintf(*filePath, "%s/%s-%s.png", PIECE_FOLDER, teamWord, typeWord);

	return true;
}

bool extract_team_square(Surface** squareImage, unsigned short team)
{
	if(team == TEAM_WHITE)
	{
		if(!extract_file_image(squareImage, WHITE_SQUARE)) return false;
	}
	else if(team == TEAM_BLACK)
	{
		if(!extract_file_image(squareImage, BLACK_SQUARE)) return false;
	}
	else return false;

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
