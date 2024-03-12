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

//funkcja testująca
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

//funkcja testująca cd.
void dodajSciezke(char *maze, CharStack *moves, int start, int col) {
    int cell = start;
    char move = popChar(moves);

    while(move != '\0') {
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
    //zmienne testowe
    int nodesSize = 0, pathLensSize = 0, allMovesSize = 0;

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
    allMovesSize++;

    while(currCell != end) {
        //zbieram dane tj.: możliwe ruchy, ich liczba, współrzędne każdego z nich
        currMove = move(maze, directions, &nextCell, currCell, &routesCount, cols);
        switch(routesCount) {
            case 0:
                currCell = pop(nodes);
                nodesSize--;
                popCharMultiple(allMoves, currPathLen);
                allMovesSize -= currPathLen;
                currPathLen = popShort(pathLens);
                pathLensSize--;
                break;
            case 1:
                pushChar(allMoves, currMove);
                allMovesSize++;
                currCell = nextCell;
                maze[currCell] = '-';
                currPathLen++;
                break;
            default:
                push(nodes, currCell);
                nodesSize++;
                pushShort(pathLens, currPathLen);
                pathLensSize++;
                currPathLen = 1;
                currCell = nextCell;
                maze[currCell] = '-';
                pushChar(allMoves, currMove);
                allMovesSize++;
                break;
        }
    }

    free(maze);
    //Tworzę nowe, niezapełnione maze
    maze = calloc(mazeSize, sizeof(char));
    getData(IN, maze, cols, &start, &end);

    //Odwracam stos
    reverseCharStack(allMoves);
    
    //Wypisuję do pliku mazeOut planszę ze wszystkimi ruchami
    dodajSciezke(maze, allMoves, start, cols);
    wypiszLab(maze, rows, cols, "mazeOut.txt");
    printf("\nLabirynt ze sciezka zapisany w mazeOut,txt\n");

    //Wypisuję raport
    nodesSize *= 4; //int
    pathLensSize *= 2; //short int
    int sumaA = nodesSize + pathLensSize + allMovesSize;
    int suma = sumaA + mazeSize;
    printf("\n");
    printf("Maze %f KB \nNodes %f KB \nPathLens %f KB \nAllMoves %f KB \n", (double)mazeSize/1000, (double)nodesSize/1000, (double)pathLensSize/1000, (double)allMovesSize/1000);
    printf("Sam algorytm zajmuje: %f KB\n", (double)sumaA/1000);
    printf("Caly program razem z planszą: %f KB\n", (double)suma/1000);
    printf("\n");

    //Zwalniam pamięć
    free(maze);
    deleteStack(nodes);
    deleteShortStack(pathLens);
    deleteCharStack(allMoves);

    return 0;
}