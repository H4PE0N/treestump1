
#include "../Header-Files-Folder/screen-include-file.h"

bool extract_path_image(Surface** image, const char filePath[])
{
	*image = IMG_Load(filePath); return (*image != NULL);
}

bool extract_file_image(Image** image, const char filename[])
{
	char filePath[256];

	sprintf(filePath, "%s/%s", PIECE_FOLDER, filename);

	return extract_path_image(image, filePath);
}

bool extract_piece_image(Surface** image, Piece piece)
{
	char* filename;

	if(!extract_piece_path(&filename, piece))
	{
		return false;
	}

	if(!extract_path_image(image, filename))
	{
		free(filename); return false;
	}
	free(filename); return true;
}

bool extract_piece_path(char** filePath, Piece piece)
{
	*filePath = malloc(sizeof(char) * 256);

	unsigned short team = PIECE_TEAM_MACRO(piece);
	unsigned short type = PIECE_TYPE_MACRO(piece);

	sprintf(*filePath, "%s/%s-%s.png", PIECE_FOLDER, TEAM_WORDS[team], TYPE_WORDS[type]);

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
