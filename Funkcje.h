#pragma once
#define _CRT_SECURE_NO_WARNINGS
using namespace std;

// Funkcja do alokacji fragmentarycznej dynamicznej tablicy 2D
int** allocateArray(int rows, int cols);

// Funkcja do zapisu tablicy do pliku binarnego
void writeArrayToFile(int** array, int rows, int cols, const char* filename);

// Funkcja do odczytu tablicy z pliku binarnego
int** readArrayFromFile(const char* filename, int& rows, int& cols);

// Funkcja do zwolnienia pamiêci tablicy
void freeArray(int** array);

