#include "load_maze.h"
#include "char_stack.h"
#include "int_stack.h"
#include "short_stack.h"
#include "algorytm.h"
#include "binary.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h> 



#define IN "mm.bin"
#define OUT_DIR "output/"
#define OUT OUT_DIR "kroki.txt"


#define DEFAULT_FILE "maze.txt"

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

int main(int argc, char *argv[]) {
    int rows = 0, cols = 0, start = 0, end = 0;
    
    // przechowuje dlugosc drogi od węzła do węzła
    short int currPathLen = 0;
    //zawiera priorytet kierunków, np: ESWN - prawo-dół-lewo-góra
    char directions[5];

    const char* textFilePath = "tempik.txt";


    char filePath[256];

    if (argc < 2) {
        // Nie podano pliku, użyj domyślnego labiryntu
        printf("Nie podano pliku, używanie domyślnego pliku: %s\n", DEFAULT_FILE);
        strncpy(filePath, DEFAULT_FILE, sizeof(filePath));
    } else {
        snprintf(filePath, sizeof(filePath), "source/%s", argv[1]); // Dodaj ścieżkę do pliku
        if (!fileExists(filePath)) {
            // jeśli plik nie istnieje, użyj domyślnego labiryntu
            strncpy(filePath, DEFAULT_FILE, sizeof(filePath));
            printf("Podany plik nie istnieje. Używanie domyślnego pliku: %s\n", filePath);
        } else {
            printf("Używamy plik: %s\n", filePath);
        }
    }


    // Sprawdzanie typ pliku
    int fileType = checkFileType(filePath);
    if (fileType == 1) {
        printf("Podany plik is binarny.\n");
        // Konwertowanie pliku binarnego na tekstowy
        convertBinaryToText(filePath, textFilePath);
        
    } else if (fileType == 0) {
        printf("Podany plik jest tekstowy.\n");
        textFilePath = filePath;
    } else {
        printf("Nieobsługiwany format pliku.\n");
        return -1;
    }


    FILE *maze = fopen(textFilePath, "r+");
    FILE *stack = fopen("temp.txt", "w+");

    //komórka którą algorytm wybierze jako następną
    int nextCell;
    //liczba możliwości ruchu
    int routesCount = 1;

    //inicjalizuje stosy
    CharStack *allMoves = createCharStack(stack);
    IntStack *nodes = initInt();
    MiniIntStack *pathLens = initMiniInt();

    //pobieram z pliku rozmiar labiryntu
    checkSizeAndGetData(maze, &rows, &cols, &start, &end);

    int mazeSize = rows*cols;

    //ta zmienna przechowuje sciany oraz przestrzen labiryntu

    
    //jesli nie zostanie wczytany początek lub koniec to nie ma roz.
    if(start == 0 || end == 0) {
        printf("Nie znaleziono poczatku lub konca labiryntu\n");
        return -1;
    }

    //obecna komórka
    int currCell = start;
    //ustalam priorytet poruszania sie
    makePrio(directions, rows, cols, end);
    printf("Priorytety kierunkow: %.4s\n", directions);
    
    char currMove = firstMove(maze, &currCell, cols, mazeSize);

    printf("Pierwszy ruch: %c\n", currMove);
    
    //kiedy program odwiedzi komórkę to zmienia ją z ' ' na '-'
    writeCell(maze, currCell, cols, '-');
    writeCell(maze, start, cols, '-');
    //Usuwam tymczasowo K z mapy aby algorytm traktował je jako przestrzeń
    writeCell(maze, end, cols, ' ');
    currPathLen++;

    //dodaje ruch na stos
    pushChar(allMoves, currMove);

    printf("Rozpoczynam algorytm...\n");

    while(currCell != end) {
        //zbieram dane tj.: możliwe ruchy, ich liczba, współrzędne każdego z nich
        currMove = move(maze, directions, &nextCell, currCell, &routesCount, cols);
        switch(routesCount) {
            case 0:
                currCell = removeInt(nodes);
                popCharMultiple(allMoves, currPathLen);
                currPathLen = removeMiniInt(pathLens);
                break;
            case 1:
                pushChar(allMoves, currMove);
                currCell = nextCell;
                writeCell(maze, currCell, cols, '-');
                currPathLen++;
                break;
            default:
                pushInt(nodes, currCell);
                pushMiniInt(pathLens, currPathLen);
                currPathLen = 1;
                currCell = nextCell;
                writeCell(maze, currCell, cols, '-');
                pushChar(allMoves, currMove);
                break;
        }
    }
    
    //Po włączeniu plik będzie zawierał ścieżkę wyjściową
    /*
        restoreFile(maze);
        dodajSciezke(maze, allMoves, start, cols);
    */

    //Zwalniam pamięć
    freeMiniInt(pathLens);
    freeInt(nodes);

    
    int movesCount = printMoves(allMoves, OUT);
    printf("Rozwiazanie sklada sie z %d ruchow\n", movesCount);
    // updateBinaryFileWithSolution(binaryFilePath, movesCount);
   
    deleteCharStack(allMoves);
    
    //Wypełniam P i K aby można było wyczyścić dawną ścieżkę
    writeCell(maze, start, cols, 'P');
    writeCell(maze, end, cols, 'K');
    // Usuwam z pliku ścieżkę
    restoreFile(maze);
    fclose(maze);
    fclose(stack);
    remove("temp.txt");
    remove("tempik.txt");

    return 0;
}