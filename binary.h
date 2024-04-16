#ifndef BINARY_H
#define BINARY_H
#include "char_stack.h"
#include <stdio.h>

void convertBinaryToText(const char* binaryFilePath, const char* textFilePath);
void updateBinaryFileWithSolution(const char* binaryFilePath, int move_count);
void writeMazeToBinary(const char* textFilePath, const char* binaryFilePath, int move_count);


typedef struct {
    int columns;      
    int lines;        
    int entryX;       
    int entryY;       
    int exitX;        
    int exitY;       
} MazeDimensions; // Struktura przechowująca wymiary labiryntu

#endif // BINARY_H
