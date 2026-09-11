//Tarea 1 INF221 2026-2 Sergio Fonseca 202404559-8

//Algoritmo std::sort de la biblioteca estandar de C++ (introsort:
//quicksort + heapsort + insertion sort para arreglos pequenos).
//cppreference.com. (2026). std::sort.
//https://en.cppreference.com/w/cpp/algorithm/sort.html

#include <vector>
#include <algorithm>

std::vector<int> sortArray(std::vector<int>& arr) {
    std::sort(arr.begin(), arr.end());  // std::sort de la STL
    return arr;
}
