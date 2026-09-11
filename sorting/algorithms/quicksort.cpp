//Tarea 1 INF221 2026-2 Sergio Fonseca 202404559-8

//GeeksforGeeks. (2023, 14 de septiembre). QuickSort using Random Pivoting.
//https://www.geeksforgeeks.org/dsa/quicksort-using-random-pivoting/

#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <unistd.h>

// Lomuto partition scheme (el pivote ya fue ubicado en vec[high] por
// partition_r antes de llamar a esta funcion)
int partition(std::vector<int>& vec, int low, int high) {
    int pivot = vec[high];
    int i = low;

    for (int j = low; j <= high - 1; j++) {
        if (vec[j] <= pivot) {
            std::swap(vec[i], vec[j]);
            i++;
        }
    }
    std::swap(vec[i], vec[high]);
    return i;
}

// Elige un pivote aleatorio en [low, high], lo intercambia a la posicion
// high, y particiona normalmente a partir de ahi.
int partition_r(std::vector<int>& vec, int low, int high) {
    int r = low + rand() % (high - low + 1);
    std::swap(vec[r], vec[high]);
    return partition(vec, low, high);
}

void quickSort(std::vector<int>& vec, int low, int high) {
    if (low < high) {
        int p = partition_r(vec, low, high);
        quickSort(vec, low, p - 1);
        quickSort(vec, p + 1, high);
    }
}

// Wrapper con firma uniforme para ser invocado desde sorting.cpp
std::vector<int> quickSortArray(std::vector<int>& vec) {
    // Semilla por proceso: cada combinacion (algoritmo, archivo) corre en
    // su propio proceso hijo (ver sorting.cpp), por lo que se re-semilla
    // aqui para no repetir la misma secuencia de pivotes en cada corrida.
    srand(static_cast<unsigned>(time(nullptr)) ^ static_cast<unsigned>(getpid()));

    if (!vec.empty())
        quickSort(vec, 0, static_cast<int>(vec.size()) - 1);
    return vec;
}
