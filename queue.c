#include "queue.h"
#include "load_maze.h"
#include "char_stack.h"
#include <stdio.h>
#include <stdlib.h>

Queue *initializeQueue(FILE * file) {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->front = 0;
    queue->rear = 0;
    queue->file = file;
    return queue;
}


// Funkcja dodająca element do kolejki
void push(Queue* queue, int data) {
    fseek(queue->file, queue->rear, SEEK_SET);
    //zakładam że data nie będzie dłuższa niż 7 cyfr
    fprintf(queue->file, "%7d\n", data);
    //rear inkrementuję o 8 ponieważ biorę jeszcze pod uwagę znak nowej linii
    queue->rear += 8;
}


// Funkcja usuwająca element z kolejki
int pop(Queue* queue) {
    fseek(queue->file, queue->front, SEEK_SET);
    int data;
    fscanf(queue->file, "%d", &data);
    queue->front += 8;
    return data;
}


void deleteQueue(Queue* queue) {
    free(queue);
}


//  Zapisuje ruchy do pliku
int printMovesq(FILE *maze, const char* filename, int start, int end, int col) {
    FILE *out = fopen(filename, "w+");
    int cell = end;
    int i = 0, k = 1, counter = 0;
    int opt[4] = {-col, col, 1, -1};

    //NSEW - przeciwne kierunki
    char *moves = "SNWE";
    char move = 'X';

    while(cell != start) {
        i = 0;
        k = 1;
        while(i < 4 && k == 1) {
            move = readCell(maze, cell + opt[i], col);
            switch(move)
            {
            case 'N':
                fprintf(out, "%c\n", moves[i]);
                cell += opt[i];
                writeCell(maze, cell, col, '*');
                fprintf(out, "%c\n", 'S');
                cell -= col;
                writeCell(maze, cell, col, '*');
                counter+=2;
                k = 0;
                break;
            case 'S':
                fprintf(out, "%c\n", moves[i]);
                cell += opt[i];
                writeCell(maze, cell, col, '*');
                fprintf(out, "%c\n", 'N');
                cell += col;
                writeCell(maze, cell, col, '*');
                counter+=2;
                k = 0;
                break;
            case 'E':
                fprintf(out, "%c\n", moves[i]);
                cell += opt[i];
                writeCell(maze, cell, col, '*');
                fprintf(out, "%c\n", 'W');
                cell += 1;
                writeCell(maze, cell, col, '*');
                counter+=2;
                k = 0;
                break;
            case 'W':
                fprintf(out, "%c\n", moves[i]);
                cell += opt[i];
                writeCell(maze, cell, col, '*');
                fprintf(out, "%c\n", 'E');
                cell -= 1;
                writeCell(maze, cell, col, '*');
                counter+=2;
                k = 0;
                break;
            case '-':
                fprintf(out, "%c\n", moves[i]);
                cell += opt[i];
                writeCell(maze, cell, col, '*');
                counter++;
                move = moves[i];
                k = 0;
                break;
            default:
                break;
            }
            i++;
        }
    }

    // odwracam ruchy
    int j1 = 0, j2 = (counter - 1) * 2;
    char moveTop, moveBot;
    while(j1 <= j2) {
        fseek(out, j1, SEEK_SET);
        moveTop = fgetc(out);
        fseek(out, j2, SEEK_SET);
        moveBot = fgetc(out);
        fseek(out, j1, SEEK_SET);
        fputc(moveBot, out);
        fseek(out, j2, SEEK_SET);
        fputc(moveTop, out);
        j1+=2; j2-=2;
    }
    fclose(out);
    return counter;
}


// Funckcja tłumacząca ruchy na kierunki
void translateSteps(const char * inPath, const char * outPath, int movesAmount) {
    FILE * inFile = fopen(inPath, "r+");
    FILE * outFile = fopen(outPath, "w+");
    fprintf(outFile, "START\n");
    fseek(inFile, 0, SEEK_SET);

    int streak = 1;
    char currentDirection = fgetc(inFile);
    char previousDirection = currentDirection; // Zakładamy, że tablica nie jest pusta
    char c;

    for (int i = 1; i < movesAmount; i++) {
        
        fseek(inFile, 2*i, SEEK_SET);
        if ((c = fgetc(inFile)) == previousDirection) {
            streak++;
        } else {
            fprintf(outFile, "FORWARD %d\n", streak); // Wypisz poprzednią sekwencję ruchu
            fprintf(outFile, "%s\n", getTurnDirection(previousDirection, c)); // Wypisz skręt

            previousDirection = c;
            streak = 1; // Resetuj licznik ruchów w nowym kierunku
        }
    }

    // Wypisz ostatnią sekwencję ruchów
    fprintf(outFile, "FORWARD %d\n", streak);
    fprintf(outFile, "STOP\n"); // Zakończ sekwencję
    fclose(outFile);
    fclose(inFile);
}