#ifndef BINARY_H
#define BINARY_H
#include "char_stack.h"
#include <stdio.h>
#include "load_maze.h"

void convertBinaryToText(const char* binaryFilePath, const char* textFilePath);
void updateBinaryFileWithSolution(const char* binaryFilePath, int move_count);
void writeMazeToBinary(const char* textFilePath, const char* binaryFilePath, int move_count, MazeDim dims);


#endif // BINARY_H
