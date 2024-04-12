#include "load_maze.h"
#include "char_stack.h"
#include "int_stack.h"
#include "short_stack.h"
#include "dfs.h"
#include "binary.h"
#include "bfs.h"
#include "manage.h"


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h> 
#include <unistd.h>



#define IN "mm.bin"
#define OUT_DIR "output/"
#define OUT OUT_DIR "kroki.txt"


#define DEFAULT_FILE "maze.txt"
#define DEFAULT_ALGORITHM "dfs"




int main(int argc, char *argv[]) {


    const char* textFilePath = "tempik.txt";


    // Parsowanie argumentów
    Arguments args = parseArguments(argc, argv);


    // Sprawdzanie typ pliku
    int fileType = checkFileType(args.fileName);
    if (fileType == 1) {
        printf("Podany plik is binarny.\n");
        // Konwertowanie pliku binarnego na tekstowy
        convertBinaryToText(args.fileName, textFilePath);
        
    } else if (fileType == 0) {
        printf("Podany plik jest tekstowy.\n");
        textFilePath = args.fileName;
    } else {
        printf("Nieobsługiwany format pliku.\n");
        return -1;
    }


    FILE *maze = fopen(textFilePath, "r+");


    if (maze == NULL) {
        perror("Błąd przy otwieraniu pliku");
        return -1;
    }

    // Sprawdzanie jaki algorytm ma być użyty
    if (strcmp(args.algorithm, "dfs") == 0) {
        runDFS(maze);
    } else if (strcmp(args.algorithm, "bfs") == 0) {
        runBFS(maze);
    } 

    return 0;
}