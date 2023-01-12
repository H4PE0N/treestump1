
#include "../Header-Files-Folder/screen-include-file.h"

bool extract_path_image(Surface** image, const char filePath[])
{
	*image = IMG_Load(filePath); return (*image != NULL);
}

bool extract_file_image(Image** image, const char filename[])
{
	char filePath[256];

	sprintf(filePath, "%s/%s", IMAGES_FOLDER, filename);

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

	const char* teamWord = TEAM_WORDS[PIECE_TEAM_MACRO(piece)];
	const char* typeWord = TYPE_WORDS[PIECE_TYPE_MACRO(piece)];

	sprintf(*filePath, "%s/%s-%s.png", IMAGES_FOLDER, teamWord, typeWord);

	return true;
}

bool extract_team_square(Surface** squareImage, uint8_t team)
{
	if(team == TEAM_WHITE)
		return extract_file_image(squareImage, WHITE_SQUARE_FILE);

	else if(team == TEAM_BLACK)
		return extract_file_image(squareImage, BLACK_SQUARE_FILE);

	return false;
}
