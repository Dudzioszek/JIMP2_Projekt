#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>


typedef struct {
    char* fileName;
    char* algorithm;
} Arguments;

// Funkcja sprawdzająca czy plik istnieje
bool fileExists(const char *filename);
int checkFileType(const char *filePath);


Arguments parseArguments(int argc, char* argv[]);
