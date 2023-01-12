
#ifndef EXTRACT_ENGINE_FILES_H
#define EXTRACT_ENGINE_FILES_H

bool extract_score_matrix_t(int scoreMatrix[BOARD_RANKS][BOARD_FILES], FILE* filePointer);

bool extract_score_matrix(int scoreMatrix[BOARD_RANKS][BOARD_FILES], const char filePath[]);

bool type_matrix_filepath(char* filePath, uint8_t type);

bool extract_score_matrixs(int scoreMatrixs[PIECE_TYPE_SPAN][BOARD_RANKS][BOARD_FILES]);

#endif