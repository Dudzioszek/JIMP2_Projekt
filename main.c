#include "load_maze.h"
#include "char_stack.h"
#include "int_stack.h"
#include "short_stack.h"
#include "algorytm.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define IN "maze.txt"
#define OUT "kroki.txt"

void wypiszLab(char *maze, int row, int cols, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Błąd otwarcia pliku do zapisu.\n");
        return;
    }

    int mazeSize = row * cols;
    int i = 0;
    while (i < mazeSize) {
        fprintf(file, "%c", maze[i]);
        if ((i + 1) % cols == 0) fprintf(file, "\n");
        i++;
    }

    fclose(file);
}

void dodajSciezke(char *maze, CharStack *moves, int start, int col) {
    int cell = start;
    char move = popChar(moves);

    while(move != NULL) {
        maze[cell] = '-';
        switch(move) {
                case 'N':
                    cell -= col;
                    break;
                case 'S':
                    cell += col;
                    break;
                case 'E':
                    cell += 1;
                    break;
                case 'W':
                    cell -= 1;
                    break;
            }
            move = popChar(moves);
        }
}

int main() {
    int rows = 0, cols = 0, start = 0, end = 0;
    // przechowuje dlugosc drogi od węzła do węzła
    short int currPathLen = 0;
    //zawiera priorytet kierunków, np: ESWN - prawo-dół-lewo-góra
    char directions[5];
    
    //komórka którą algorytm wybierze jako następną
    int nextCell;
    //liczba możliwości ruchu
    int routesCount = 1;

    //inicjalizuje stosy
    CharStack *allMoves = createCharStack();
    Stack *nodes = createStack();
    ShortStack *pathLens = createShortStack();

    //pobieram z pliku rozmiar labiryntu
    checkSize(IN, &rows, &cols);
    int mazeSize = rows*cols;

    //ta zmienna przechowuje sciany oraz przestrzen labiryntu
    char *maze = calloc(mazeSize, sizeof(char));

    //zapelniam zmienna maze, start i end
    getData(IN, maze, cols, &start, &end);

    //jesli nie zostanie wczytany początek lub koniec to nie ma roz.
    if(start == 0 || end == 0) {
        printf("Labirynt nie ma rozwiązania!!\n");
        return -1;
    }

    //obecna komórka
    int currCell = start;
    
    //ustalam priorytet poruszania sie
    makePrio(directions, rows, cols, end);
    printf("Priorytety kierunkow: %.4s\n", directions);
    
    char currMove = firstMove(maze, &currCell, cols, mazeSize);
    
    //kiedy program odwiedzi komórkę to zmienia ją z ' ' na '-'
    maze[currCell] = '-';
    maze[start] = '-';
    currPathLen++;

    //dodaje ruch na stos
    pushChar(allMoves, currMove);

    while(currCell != end) {
        //zbieram dane tj.: możliwe ruchy, ich liczba, współrzędne każdego z nich
        currMove = move(maze, directions, &nextCell, currCell, &routesCount, cols);
        switch(routesCount) {
            case 0:
                currCell = pop(nodes);
                popCharMultiple(allMoves, currPathLen);
                currPathLen = popShort(pathLens);
                break;
            case 1:
                pushChar(allMoves, currMove);
                currCell = nextCell;
                maze[currCell] = '-';
                currPathLen++;
                break;
            default:
                push(nodes, currCell);
                pushShort(pathLens, currPathLen);
                currPathLen = 1;
                currCell = nextCell;
                maze[currCell] = '-';
                pushChar(allMoves, currMove);
                break;
        }
    }

    free(maze);
    //Dodatkowe testy:
    maze = calloc(mazeSize, sizeof(char));
    getData(IN, maze, cols, &start, &end);
    reverseCharStack(allMoves);
    dodajSciezke(maze, allMoves, start, cols);
    wypiszLab(maze, rows, cols, "mazeOut");
    //int k = printMoves(allMoves, OUT);
    //printf("Rozwiazanie sklada sie z %d ruchow\n", k);
    deleteStack(nodes);
    deleteShortStack(pathLens);
    deleteCharStack(allMoves);

    return 0;
}