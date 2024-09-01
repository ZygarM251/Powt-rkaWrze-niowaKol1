#include "Funkcje.h"
#include <iostream>
#include <fstream>
#include <cstring>

// Funkcja do alokacji fragmentarycznej dynamicznej tablicy 2D
int** allocateArray(int rows, int cols) {
    // Alokacja pamiêci dla wskaŸników na wiersze + 1 dla dodatkowego wiersza
    int** array = new int* [rows + 1];

    // Alokacja pamiêci dla dodatkowego wiersza do przechowywania rozmiarów
    array[0] = new int[1];

    // Zapisanie rozmiarów tablicy w dodatkowym wierszu
    array[0][0] = (rows << 16) | (cols & 0xFFFF);  // £¹czenie liczby wierszy i kolumn w jedn¹ liczbê

    // Alokacja pamiêci dla ka¿dego wiersza tablicy
    for (int i = 1; i <= rows; ++i) {
        array[i] = new int[cols];
    }

    return array;
}

// Funkcja do zapisu tablicy do pliku binarnego
void writeArrayToFile(int** array, int rows, int cols, const char* filename) {
    FILE* file = fopen(filename, "wb");
    if (!file) {
        cerr << "Nie mo¿na otworzyæ pliku do zapisu.\n";
        return;
    }

    // Zapisanie rozmiarów tablicy
    fwrite(&rows, sizeof(int), 1, file);
    fwrite(&cols, sizeof(int), 1, file);

    // Zapisanie danych tablicy
    for (int i = 1; i <= rows; ++i) {
        fwrite(array[i], sizeof(int), cols, file);
    }

    fclose(file);
}

// Funkcja do odczytu tablicy z pliku binarnego
int** readArrayFromFile(const char* filename, int& rows, int& cols) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        cerr << "Nie mo¿na otworzyæ pliku do odczytu.\n";
        return nullptr;
    }

    // Odczytanie rozmiarów tablicy
    fread(&rows, sizeof(int), 1, file);
    fread(&cols, sizeof(int), 1, file);

    // Alokacja tablicy o odczytanych rozmiarach
    int** array = allocateArray(rows, cols);
    if (!array) {
        fclose(file);
        return nullptr;
    }

    // Odczytanie danych tablicy
    for (int i = 1; i <= rows; ++i) {
        fread(array[i], sizeof(int), cols, file);
    }

    fclose(file);
    return array;
}

// Funkcja do zwolnienia pamiêci tablicy
void freeArray(int** array) {
    if (!array) return;

    // Pobranie liczby wierszy z dodatkowego wiersza
    int rows = array[0][0] >> 16;

    // Zwolnienie pamiêci dla ka¿dego wiersza
    for (int i = 1; i <= rows; ++i) {
        delete[] array[i];
    }

    // Zwolnienie pamiêci dla dodatkowego wiersza i tablicy wskaŸników
    delete[] array[0];
    delete[] array;
}