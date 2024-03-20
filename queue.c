#include "queue.h"
#include "load_maze.h"
#include <stdio.h>
#include <stdlib.h>

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

Queue* initializeQueue() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    if (queue == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    queue->front = NULL;
    queue->rear = NULL;
    return queue;
}

void push(Queue* queue, int data) {
    Node* newNode = createNode(data);
    if (queue->rear == NULL) {
        queue->front = newNode;
        queue->rear = newNode;
    } else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
}

int pop(Queue* queue) {
    if (queue->front == NULL) {
        printf("Queue is empty!\n");
        exit(1);
    }
    Node* temp = queue->front;
    int data = temp->data;
    queue->front = queue->front->next;
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    free(temp);
    return data;
}

void deleteQueue(Queue* queue) {
    while (queue->front != NULL) {
        Node* temp = queue->front;
        queue->front = queue->front->next;
        free(temp);
    }
    free(queue);
}

void printMoves(FILE *maze, const char* filename, int start, int end, int col) {
    FILE *out = fopen(filename, "w+");
    int cell = end;
    int i = 0, k = 1, counter = 0;
    int opt[4] = {-col, col, 1, -1};

    // Jeśli brak ruchu to zwraca X
    //NSEW
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
                writeCell(maze, cell, col, 'o');
                fprintf(out, "%c\n", 'S');
                cell -= col;
                writeCell(maze, cell, col, '0');
                counter+=2;
                k = 0;
                break;
            case 'S':
                fprintf(out, "%c\n", moves[i]);
                cell += opt[i];
                writeCell(maze, cell, col, 'o');
                fprintf(out, "%c\n", 'N');
                cell += col;
                writeCell(maze, cell, col, 'o');
                counter+=2;
                k = 0;
                break;
            case 'E':
                fprintf(out, "%c\n", moves[i]);
                cell += opt[i];
                writeCell(maze, cell, col, 'o');
                fprintf(out, "%c\n", 'W');
                cell += 1;
                writeCell(maze, cell, col, 'o');
                counter+=2;
                k = 0;
                break;
            case 'W':
                fprintf(out, "%c\n", moves[i]);
                cell += opt[i];
                writeCell(maze, cell, col, 'o');
                fprintf(out, "%c\n", 'E');
                cell -= 1;
                writeCell(maze, cell, col, 'o');
                counter+=2;
                k = 0;
                break;
            case '-':
                fprintf(out, "%c\n", moves[i]);
                cell += opt[i];
                writeCell(maze, cell, col, 'o');
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
}