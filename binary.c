#include "binary.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "char_stack.h"
#include "load_maze.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>



#define FILE_ID 0x52524243
#define ESCAPE 0x1B




uint8_t directionToBin(char direction) { // Funkcja zamieniająca kierunek na wartość binarną
    switch (direction) {
        case 'N': return 0x00;
        case 'E': return 0x01;
        case 'S': return 0x02;
        case 'W': return 0x03;
        default: return 0xFF; // Nieznany kierunek
    }
}


// Funkcja zapisująca labirynt w formie txt
void generateMazeFromEncoding(FILE *binaryFile, FILE *textFile, uint32_t wordCount, uint8_t separator, uint8_t wall, uint8_t path, uint16_t cols, uint16_t rows, uint16_t entryX, uint16_t entryY, uint16_t exitX, uint16_t exitY) {
    uint8_t byte, value, countByte;
    int32_t cellsProcessed = 0;
    int32_t currentRow = 1, currentCol = 1;

    while (wordCount-- && cellsProcessed < cols * rows) {  // Czytanie kodowania labiryntu
        fread(&byte, sizeof(byte), 1, binaryFile); // Odczytaj separator
        if (byte != separator) { // Sprawdź, czy odczytany bajt jest separatorem
            fprintf(stderr, "Oczekiwano separator, otrzymano: %02x\n", byte);
            exit(EXIT_FAILURE);
        }

        fread(&value, sizeof(value), 1, binaryFile); // Odczytaj wartość
        fread(&countByte, sizeof(countByte), 1, binaryFile); // Odczytaj liczbę wystąpień

        for (int i = 0; i < countByte + 1 && cellsProcessed < cols * rows; i++) {
            // Sprawdzanie, czy wartość jest ścieżką lub ścianą 
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


// Funkcja konwertująca plik binarny na plik tekstowy
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
    fread(&separator, sizeof(separator), 1, binaryFile);
    fread(&wall, sizeof(wall), 1, binaryFile);
    fread(&path, sizeof(path), 1, binaryFile);

    // Sprawdź, czy plik binarny zawiera poprawne dane
    if (solutionOffset > 0) {
        // Ustaw wskaźnik pliku na początek danych labiryntu, pomijając sekcję rozwiązania
        fseek(binaryFile, solutionOffset, SEEK_SET);
    }

    generateMazeFromEncoding(binaryFile, textFile, counter, separator, wall, path, columns, lines, entryX, entryY, exitX, exitY);

    fclose(binaryFile);
    fclose(textFile);
    printf("Konwersja zakończona pomyślnie. Wynik zapisano w: %s\n", textFilePath);
}




// Funkcja zapisująca labirynt w formie binarnej
void writeMazeToBinary(const char* textFilePath, const char* binaryFilePath, int move_count, MazeDim dims) {


    if (dims.columns == 0 || dims.rows == 0) {
        fprintf(stderr, "Niepoprawne wymiaru labiryntu.\n");
        exit(EXIT_FAILURE);
    }



    // Otwarcie plików
    FILE *textFile = fopen(textFilePath, "r");
    FILE *binaryFile = fopen(binaryFilePath, "wb");
    if (!textFile || !binaryFile) {
        perror("Error opening files");
        exit(EXIT_FAILURE);
    }


    // Zapisanie nagłówka pliku binarnego
    uint32_t fileId = FILE_ID;
    uint8_t escape = ESCAPE;

    uint32_t counter = 0; // Licznik zapisanych bajtów
    uint32_t solutionOffset = 0; // Offset sekcji rozwiązania


    // Zapisanie danych labiryntu
    fwrite(&fileId, sizeof(fileId), 1, binaryFile);
    fwrite(&escape, sizeof(escape), 1, binaryFile);
    fwrite(&dims.columns, sizeof(dims.columns), 1, binaryFile);
    fwrite(&dims.rows, sizeof(dims.rows), 1, binaryFile);
    fwrite(&dims.entryX, sizeof(dims.entryX), 1, binaryFile);
    fwrite(&dims.entryY, sizeof(dims.entryY), 1, binaryFile);
    fwrite(&dims.exitX, sizeof(dims.exitX), 1, binaryFile);
    fwrite(&dims.exitY, sizeof(dims.exitY), 1, binaryFile);
    fseek(binaryFile, 12, SEEK_CUR); // zarezerwowane bajty

    char line[1024];
    uint8_t separator = 0xF0, wall = 'X', path = ' ';


    // Zapisanie kodowania labiryntu
    while (fgets(line, sizeof(line), textFile)) { 
        int length = strlen(line);
        if (line[length - 1] == '\n') line[length - 1] = '\0';  // Usuń znak nowej linii

        char previousChar = '\0';
        int runLength = 0;
        for (int i = 0; i < dims.columns; i++) {
            char currentChar = line[i];
            if (currentChar == previousChar) {
                runLength++;
            } else {
                if (runLength > 0) {
                    fwrite(&separator, sizeof(separator), 1, binaryFile);
                    uint8_t value = (previousChar == wall) ? wall : path;
                    fwrite(&value, sizeof(value), 1, binaryFile);
                    uint8_t count = runLength - 1;
                    fwrite(&count, sizeof(count), 1, binaryFile);
                    counter++;
                }
                previousChar = currentChar;
                runLength = 1;
            }
        }
        if (runLength > 0) { // Zapisz ostatnią sekwencję
            fwrite(&separator, sizeof(separator), 1, binaryFile);
            uint8_t value = (previousChar == wall) ? wall : path;
            fwrite(&value, sizeof(value), 1, binaryFile);
            uint8_t count = runLength - 1;
            fwrite(&count, sizeof(count), 1, binaryFile);
            counter++;
        }
    }

    // dostosowanie offsetu rozwiązania
    solutionOffset = ftell(binaryFile);

    // przechodzenie na koniec pliku, aby zaktualizować offset rozwiązania
    fseek(binaryFile, 36, SEEK_SET); 
    fwrite(&solutionOffset, sizeof(solutionOffset), 1, binaryFile);

    // powrót na koniec pliku, aby dodać sekcję rozwiązania
    fseek(binaryFile, 0, SEEK_END);

    // Zapisanie nagłówka sekcji rozwiązania
    uint32_t directionIdentifier = 0x52524243; // Identfikator sekcji rozwiązania
    fwrite(&directionIdentifier, sizeof(directionIdentifier), 1, binaryFile);

    
    // Zapisanie liczby kroków
    uint8_t steps = (uint8_t)move_count;
    fwrite(&steps, sizeof(steps), 1, binaryFile);

    

    char direction;
    uint8_t counter_solution = 1; // licznik wystąpień do zapisania


    while ((direction = fgetc(textFile) != EOF)) {
        if (direction == '\n' || direction == '\r') continue;

        uint8_t dirBin = directionToBin(direction);
        // Sprawdź, czy potrzebne jest zapisanie poprzedniego kroku
        if (dirBin != 0xFF) {
            
            fwrite(&dirBin, sizeof(dirBin), 1, binaryFile);
            fwrite(&counter_solution, sizeof(counter), 1, binaryFile);
            counter_solution = 0; // resetowanie licznika po każdym kroku
        }
        counter_solution++;
    }


    // Zamknięcie plików
    fclose(textFile);
    fclose(binaryFile);
    printf("Plik binarny z labiryntem wraz z rozwiązaniem zostało zapisane.\n");
}