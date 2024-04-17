#include "manage.h"



#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>



// Funkcja sprawdzająca czy plik istnieje
bool fileExists(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file) {
        fclose(file);
        return true;
    }
    return false;
}

// Funkcja sprawdzająca typ pliku
int checkFileType(const char *filePath) {
    const char *dot = strrchr(filePath, '.'); // usuwa wszystko przed ostatnim wystąpieniem '.'
    if (!dot || dot == filePath) {
        return -1; // No extension found
    }
    if (strcmp(dot, ".bin") == 0) {
        return 1; // Plik binarny
    } else if (strcmp(dot, ".txt") == 0) {
        return 0; // Plik tekstowy
    }
    return -1; // Format nieobsługiwany
}


// Funkcja parsująca argumenty
Arguments parseArguments(int argc, char* argv[]) {
    Arguments args = { .fileName = "maze.txt", .algorithm = "dfs" }; // Domyślne wartości

    int opt;
    while ((opt = getopt(argc, argv, "n:a:p")) != -1) {
        switch (opt) {
            case 'n':
                {
                char prefix[] = "source/";
                args.fileName = malloc(strlen(prefix) + strlen(optarg) + 1);  // Allocate memory for the full path
                if (args.fileName == NULL) {
                    fprintf(stderr, "Błąd alokacji pamieci\n");
                    exit(EXIT_FAILURE);
                }
                strcpy(args.fileName, prefix);
                strcat(args.fileName, optarg);
                printf("Nazwa pliku: %s\n", args.fileName);
                break;
                }
            case 'a':
                if (strcmp(optarg, "dfs") == 0 || strcmp(optarg, "bfs") == 0) {
                    args.algorithm = strdup(optarg);
                } else {
                    fprintf(stderr, "Uwaga źle podany dany algrotytm: '%s'. Przełączam na dfs.\n", optarg);
                    args.algorithm = strdup("dfs");
                }
                if (args.algorithm == NULL) {
                    fprintf(stderr, "Błąd alokacji pamięci.\n");
                    exit(EXIT_FAILURE);
                }
                break;
            case 'p':
                printf("\n#POMOC#\n");
                printf("  -n <nazwa_pliku>    Określ nazwę pliku z labiryntem, musi być w folderze 'source' (domyślnie: maze.txt)\n");
                printf("  -a <algorytm>       Wybierz algorytm do rozwiązania labiryntu (dfs lub bfs, domyślnie: dfs)\n");
                exit(EXIT_SUCCESS);
            
            default:
                printf("\nWpisz -p żeby otrzymać pomoc.\n\n");
                exit(-1);
                exit(EXIT_FAILURE);
        }
    }

    return args;
}