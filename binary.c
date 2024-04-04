#include "binary.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "char_stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h> // Potrzebne dla offsetof

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

uint8_t directionToBin(char direction) {
    switch (direction) {
        case 'N': return 0x00;
        case 'E': return 0x01;
        case 'S': return 0x02;
        case 'W': return 0x03;
        default: return 0xFF; // Nieznany kierunek
    }
}

void generateMazeFromEncoding(FILE *binaryFile, FILE *textFile, uint32_t wordCount, uint8_t separator, uint8_t wall, uint8_t path, uint16_t cols, uint16_t rows, uint16_t entryX, uint16_t entryY, uint16_t exitX, uint16_t exitY) {
    uint8_t byte, value, countByte;
    int32_t cellsProcessed = 0;
    int32_t currentRow = 1, currentCol = 1;

    while (wordCount-- && cellsProcessed < cols * rows) { 
        fread(&byte, sizeof(byte), 1, binaryFile); // Odczytaj separator
        if (byte != separator) {
            fprintf(stderr, "Expected separator, received: %02x\n", byte);
            exit(EXIT_FAILURE);
        }

        fread(&value, sizeof(value), 1, binaryFile); // Odczytaj wartość
        fread(&countByte, sizeof(countByte), 1, binaryFile); // Odczytaj liczbę wystąpień

        for (int i = 0; i < countByte + 1 && cellsProcessed < cols * rows; i++) {
            // Sprawdź, czy jesteśmy na pozycji wejścia lub wyjścia
            if (currentRow == entryY && currentCol == entryX) {
                fputc('P', textFile);
            } else if (currentRow == exitY && currentCol == exitX) {
                fputc('K', textFile);
            } else {
                fputc(value == wall ? 'X' : ' ', textFile);
            }

            cellsProcessed++;
            currentCol++;
            if (currentCol > cols) {
                fputc('\n', textFile);
                currentCol = 1;
                currentRow++;
            }
        }
    }
}

void convertBinaryToText(const char* binaryFilePath, const char* textFilePath) {
    FILE *binaryFile = fopen(binaryFilePath, "rb");
    if (!binaryFile) {
        perror("Nie można otworzyć pliku binarnego");
        exit(EXIT_FAILURE);
    }

    FILE *textFile = fopen(textFilePath, "w");
    if (!textFile) {
        perror("Nie można utworzyć pliku tekstowego");
        fclose(binaryFile);
        exit(EXIT_FAILURE);
    }

    // Odczyt nagłówka pliku
    uint32_t fileId, counter, solutionOffset;
    uint16_t columns, lines, entryX, entryY, exitX, exitY;
    uint8_t escape, separator, wall, path;

    fread(&fileId, sizeof(fileId), 1, binaryFile);
    fread(&escape, sizeof(escape), 1, binaryFile);
    fread(&columns, sizeof(columns), 1, binaryFile);
    fread(&lines, sizeof(lines), 1, binaryFile);
    fread(&entryX, sizeof(entryX), 1, binaryFile);
    fread(&entryY, sizeof(entryY), 1, binaryFile);
    fread(&exitX, sizeof(exitX), 1, binaryFile);
    fread(&exitY, sizeof(exitY), 1, binaryFile);
    fseek(binaryFile, 12, SEEK_CUR); // Pomiń zarezerwowane bajty
    fread(&counter, sizeof(counter), 1, binaryFile);
    fread(&solutionOffset, sizeof(solutionOffset), 1, binaryFile);
    printf("%d",solutionOffset);
    fread(&separator, sizeof(separator), 1, binaryFile);
    fread(&wall, sizeof(wall), 1, binaryFile);
    fread(&path, sizeof(path), 1, binaryFile);

    // Sprawdź, czy solutionOffset jest ustawiony i różny od 0
    if (solutionOffset > 0) {
        // Ustaw wskaźnik pliku na początek danych labiryntu, pomijając sekcję rozwiązania
        fseek(binaryFile, solutionOffset, SEEK_SET);
    }

    generateMazeFromEncoding(binaryFile, textFile, counter, separator, wall, path, columns, lines, entryX, entryY, exitX, exitY);

    fclose(binaryFile);
    fclose(textFile);
    printf("Konwersja zakończona pomyślnie. Wynik zapisano w: %s\n", textFilePath);
}








void updateBinaryFileWithSolution(const char* binaryFilePath, int move_count) {
     FILE *binaryFile = fopen(binaryFilePath, "r+b");
    if (binaryFile == NULL) {
        perror("Nie można otworzyć pliku binarnego");
        exit(EXIT_FAILURE);
    }

    // Przejście na koniec pliku, aby znaleźć pozycję, gdzie zacznie się sekcja rozwiązania
    fseek(binaryFile, 0, SEEK_END);
    uint32_t solutionOffset = (uint32_t)ftell(binaryFile);

    // Bezpośrednie przesunięcie do miejsca w nagłówku, gdzie jest zapisany Solution Offset, i jego aktualizacja
    fseek(binaryFile, 36, SEEK_SET); // 36 bajtów od początku pliku do Solution Offset
    fwrite(&solutionOffset, sizeof(solutionOffset), 1, binaryFile);

    // Powrót na koniec pliku, aby dodać sekcję rozwiązania
    fseek(binaryFile, 0, SEEK_END);

    // Zapis nagłówka sekcji rozwiązania
    uint32_t directionIdentifier = 0x52524243; // Identfikator sekcji rozwiązania
    fwrite(&directionIdentifier, sizeof(directionIdentifier), 1, binaryFile);

    // Liczba kroków (steps) powinna być zapisywana jako 8-bitowa wartość, a nie 32-bitowa
    uint8_t steps = (uint8_t)move_count;
    fwrite(&steps, sizeof(steps), 1, binaryFile);

    FILE *solutionFile = fopen("temp.txt", "r");
    if (solutionFile == NULL) {
        perror("Nie można otworzyć pliku z rozwiązaniem");
        fclose(binaryFile);
        exit(EXIT_FAILURE);
    }

    char direction;
    uint8_t counter = 1; // Licznik wystąpień, startujemy od 1
    while ((direction = fgetc(solutionFile)) != EOF) {
        if (direction == '\n' || direction == '\r') continue;

        uint8_t dirBin = directionToBin(direction);
        // Sprawdź, czy potrzebne jest zapisanie poprzedniego kroku
        if (dirBin != 0xFF) {
            fwrite(&dirBin, sizeof(dirBin), 1, binaryFile);
            fwrite(&counter, sizeof(counter), 1, binaryFile);
            counter = 0; // Zresetuj licznik po każdym kroku
        }
        counter++;
    }

    fclose(solutionFile);
    fclose(binaryFile);
    printf("Plik binarny został zaktualizowany o sekcję rozwiązania.\n");
}
