#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

#ifndef MANAGE_H
#define MANAGE_H


typedef struct {
    char* fileName;
    char* algorithm;
    bool save_way;
    bool save_binary;
} Arguments;

// Funkcja sprawdzająca czy plik istnieje
bool fileExists(const char *filename);
int checkFileType(const char *filePath);


Arguments parseArguments(int argc, char* argv[]);

#endif
