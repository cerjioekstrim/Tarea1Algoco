//Tarea 1 INF221 2026-2 Sergio Fonseca 202404559-8

//Multiplicacion de matrices por definicion (triple ciclo for),
//el metodo "de libro" O(n^3). Referencia:
//GeeksforGeeks. (2025, 29 de agosto). Strassen's Matrix Multiplication.
//https://www.geeksforgeeks.org/dsa/strassens-matrix-multiplication/
//Cormen, T. H., Leiserson, C. E., Rivest, R. L., & Stein, C. (2009).
//Introduction to Algorithms (3rd ed.). MIT Press. Seccion 4.2.

#include <vector>

// Multiplica dos matrices cuadradas n x n usando el algoritmo naive
// (definicion de producto matricial), en O(n^3).
std::vector<std::vector<int>> naiveMultiply(const std::vector<std::vector<int>>& A,
                                             const std::vector<std::vector<int>>& B) {
    int n = static_cast<int>(A.size());
    std::vector<std::vector<int>> C(n, std::vector<int>(n, 0));

    for (int i = 0; i < n; i++) {
        for (int k = 0; k < n; k++) {
            // Reordenar los ciclos (i, k, j) en vez de (i, j, k) mejora
            // la localidad de cache al recorrer B[k] y C[i] por fila,
            // sin cambiar la cantidad de operaciones: sigue siendo O(n^3)
            // y no depende de los valores de la matriz (no se salta ceros),
            // para no sesgar la comparacion entre matrices dispersa/densa.
            int aik = A[i][k];
            for (int j = 0; j < n; j++) {
                C[i][j] += aik * B[k][j];
            }
        }
    }

    return C;
}
