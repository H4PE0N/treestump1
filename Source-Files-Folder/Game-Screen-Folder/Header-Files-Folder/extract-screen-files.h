
#ifndef EXTRACT_SCREEN_FILES_H
#define EXTRACT_SCREEN_FILES_H

bool extract_path_image(Surface**, const char[]);

bool extract_file_image(Surface**, const char[]);

bool extract_piece_image(Surface**, Piece);

bool extract_piece_path(char**, Piece);

bool extract_team_square(Surface**, uint8_t team);

#endif
