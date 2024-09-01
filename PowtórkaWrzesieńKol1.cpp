
#include <iostream>
#include "Funkcje.h"



int main() {
    int rows = 3;
    int cols = 4;

    // Alokacja tablicy
    int** myArray = allocateArray(rows, cols);

    if (!myArray) {
        cerr << "Błąd alokacji pamięci.\n";
        return 1;
    }

    // Inicjalizacja tablicy przykładowymi danymi
    for (int i = 1; i <= rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            myArray[i][j] = i * j;
        }
    }

    // Zapis tablicy do pliku
    const char* filename = "test.txt";
    writeArrayToFile(myArray, rows, cols, filename);

    // Zwolnienie pamięci
    freeArray(myArray);

    // Odczyt tablicy z pliku
    int** loadedArray = readArrayFromFile(filename, rows, cols);
    if (!loadedArray) {
        cerr << "Błąd odczytu tablicy z pliku.\n";
        return 1;
    }

    // Wyświetlenie odczytanej tablicy
    cout << "Odczytana tablica:\n";
    for (int i = 1; i <= rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << loadedArray[i][j] << " ";
        }
        cout << "\n";
    }

    // Zwolnienie pamięci
    freeArray(loadedArray);

}