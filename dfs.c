#include "dfs.h"
#include "load_maze.h"
#include <stdio.h>
#include <stdlib.h>

#include "char_stack.h"
#include "int_stack.h"
#include "short_stack.h"
#include "manage.h"
#include "binary.h"

#define OUT_DIR "output/"
#define OUT OUT_DIR "kroki.txt"


//wybieram priorytet ruchów
void makePrio(char *directions, int rows, int cols, int end) {
    //transformacja współrzędnej liniowej na dwa wymiary
    int x = (end % cols) + 1;
    int y = (end / cols) + 1;

    //jeśli preferowany kierunek to VERTICAL, jako pierwszy wybieram kierunek pionowy
    if (DIR_PREF == 'V') {
        directions[0] = y >= rows / 2 ? 'S' : 'N';
        directions[1] = x >= cols / 2 ? 'E' : 'W';
    } else { // Zakładam że DIR_PREF == 'H'
        directions[0] = x >= cols / 2 ? 'E' : 'W';
        directions[1] = y >= rows / 2 ? 'S' : 'N';
    }

    // W drugim przypadku wyniki są poprostu zamieniane
    directions[2] = directions[0] == 'S' ? 'N' : (directions[0] == 'N' ? 'S' : (directions[0] == 'E' ? 'W' : 'E'));
    directions[3] = directions[1] == 'E' ? 'W' : (directions[1] == 'W' ? 'E' : (directions[1] == 'S' ? 'N' : 'S'));

    directions[4] = '\0';
}

//funkcja wykonująca pierwszy ruch
char firstMove(FILE *file, int *cell, int cols, int size) {
    if (*cell - cols < 0) {
        (*cell) += cols;
        return 'S';
    }

    if ((*cell) + cols >= size) {
        (*cell) -= cols;
        return 'N';
    }

    if (readCell(file, (*cell) - cols, cols) == ' ') {
        (*cell) -= cols;
        return 'N';
    }

    if (readCell(file, (*cell) + cols, cols) == ' ') {
        (*cell) += cols;
        return 'S';
    }

    if (readCell(file, (*cell) - 1, cols) == ' ') {
        (*cell) -= 1;
        return 'W';
    }

    if (readCell(file, (*cell) + 1, cols) == ' ') {
        (*cell) += 1;
        return 'E';
    }

    return 'X';
}


char move(FILE *file, char *directions, int *new_cell, int cell, int *count, int col) {
    // Ta zmienna informuje ile jest opcji ruchu w tej komórce
    int j = 0;
    // Kolejne przypadki N,S,E,W
    int opt[4] = {cell - col, cell + col, cell + 1, cell - 1};
    // Jeśli brak ruchu to zwraca X
    char move = 'X';

    for (int i = 3; i >= 0; i--) {
        switch (directions[i]) {
            case 'N':
                if (readCell(file, opt[0], col) == ' ') {
                    *new_cell = opt[0];
                    move = 'N';
                    j++;
                }
                break;
            case 'S':
                if (readCell(file, opt[1], col) == ' ') {
                    *new_cell = opt[1];
                    move = 'S';
                    j++;
                }
                break;
            case 'E':
                if (readCell(file, opt[2], col) == ' ') {
                    *new_cell = opt[2];
                    move = 'E';
                    j++;
                }
                break;
            case 'W':
                if (readCell(file, opt[3], col) == ' ') {
                    *new_cell = opt[3];
                    move = 'W';
                    j++;
                }
                break;
        }
    }

    // W "new_cell" zostanie zapisana ostatnia (najnowsza) komórka
    // Tak samo "move"
    // Jeśli komórka jest dostępna to j++

    // Count zawiera liczbę dostępnych komórek
    (*count) = j;

    // Zwracam jaki ruch wykona algorytm
    return move;
}

int runDFS(FILE* maze,MazeDim dims) {

        
    // przechowuje dlugosc drogi od węzła do węzła
    short int currPathLen = 0;
    //zawiera priorytet kierunków, np: ESWN - prawo-dół-lewo-góra
    char directions[5];

    FILE *stack = fopen("tempC.txt", "w+");
    FILE *stackInt = fopen("tempInt.txt", "w+");
    FILE *stackShort = fopen("tempShort.txt", "w+");

    //komórka którą algorytm wybierze jako następną
    int nextCell;
    //liczba możliwości ruchu
    int routesCount = 1;
    

    // inicjalizuje stosy
    CharStack *allMoves = createCharStack(stack);
    IntStack *nodes = initInt(stackInt);
    MiniIntStack *pathLens = initMiniInt(stackShort);
    

    int mazeSize = dims.rows*dims.columns;

    //obecna komórka
    int currCell = dims.start;
    //ustalam priorytet poruszania sie
    makePrio(directions, dims.rows, dims.columns, dims.end);
    printf("Priorytety kierunkow: %.4s\n", directions);
    
    char currMove = firstMove(maze, &currCell, dims.columns, mazeSize);
    
    //kiedy program odwiedzi komórkę to zmienia ją z ' ' na '-'
    writeCell(maze, currCell, dims.columns, '-');
    writeCell(maze, dims.start, dims.columns, '-');
    //Usuwam tymczasowo K z mapy aby algorytm traktował je jako przestrzeń
    writeCell(maze, dims.end, dims.columns, ' ');
    currPathLen++;

    //dodaje ruch na stos
    pushChar(allMoves, currMove);

    printf("Rozpoczynam algorytm DFS...\n");

    while(currCell != dims.end) {
        //zbieram dane tj.: możliwe ruchy, ich liczba, współrzędne każdego z nich
        currMove = move(maze, directions, &nextCell, currCell, &routesCount, dims.columns);
        switch(routesCount) {
            case 0:
                currCell = removeInt(nodes);
                popCharMultiple(allMoves, currPathLen);
                currPathLen = removeMiniInt(pathLens);
                break;
            case 1:
                pushChar(allMoves, currMove);
                currCell = nextCell;
                writeCell(maze, currCell, dims.columns, '-');
                currPathLen++;
                break;
            default:
                pushInt(nodes, currCell);
                pushMiniInt(pathLens, currPathLen);
                currPathLen = 1;
                currCell = nextCell;
                writeCell(maze, currCell, dims.columns, '-');
                pushChar(allMoves, currMove);
                break;
        }
    }

    //Zwalnianie pamięci
    freeMiniInt(pathLens);
    freeInt(nodes);
    
    int movesCount = printMoves(allMoves, OUT);
    movesCount++;
    printf("Znaleziono sciezke od dlugosci: %d\n", movesCount);

    // Usuwam z pliku ścieżkę
    restoreFile(maze);
    writeCell(maze, dims.start, dims.columns, 'P');
    writeCell(maze, dims.end, dims.columns, 'K');


    // Tworzenie pliku z labiryntem z odnalezioną ścieżką    

    deleteCharStack(allMoves);
    fclose(maze);
    fclose(stackInt);
    fclose(stackShort);

    remove("tempC.txt");
    remove("tempInt.txt");
    remove("tempShort.txt");
    
    return movesCount;

}