
#include "../Header-Files-Folder/engine-include-file.h"

const char ENGINE_FILES_FOLDER[] = "../Source-Files-Folder/Chess-Engine-Folder/Engine-Files-Folder";

int TYPE_SCORE_MATRIX[7][8][8];

const int PIECE_TYPE_SCORES[7] = {0, 10, 30, 30, 50, 90, 900};

const int MATE_SCORE = -10000;
const int DRAW_SCORE = -0;

const float MATRIX_FACTOR = 1.0;
const float TYPE_FACTOR = 5.0;

const int MIN_STATE_SCORE = -20000;
const int MAX_STATE_SCORE = +20000;
