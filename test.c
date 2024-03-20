#ifndef QUEUE_H
#define QUEUE_H
#include <stdio.h>
#include <stdlib.h>

typedef struct Queue {
    int front;
    int rear;
    FILE *file;
} Queue;

Queue * initQueue(FILE * file) {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->front = 0;
    queue->rear = 0;
    queue->file = file;
    return queue;
}

int main() {
    //Queue *queue = initQueue(temp);
    int n = 0; // Move to the 5th integer in the file
    int num;
    
    FILE *fp = fopen("temp.txt", "w+");
    
    if (fp == NULL) {
        perror("Error opening file");
        return 1;
    }

    fprintf(fp, "%7d\n", 40000);
    fprintf(fp, "%7d\n", 4000000);
    fprintf(fp, "%7d\n", 40000);
    fprintf(fp, "%7d\n", 40000);
    
    // Calculate the offset in bytes
    long int offset = (long int)n * sizeof(int);
    
    // jeśli minimalny rozmiar to 7 -> iteruję co 8
    fseek(fp, 16, SEEK_SET);
    
    // Read the integer at the current position
    fscanf(fp, "%d", &num);
    printf("Integer at position %d: %d\n", n, num);
    
    fclose(fp);
    return 0;
}

#endif /* QUEUE_H */