//Tarea 1 INF221 2026-2 Sergio Fonseca 202404559-8

//Algoritmo de Strassen para multiplicacion de matrices (divide y venceras,
//7 multiplicaciones recursivas en vez de 8), O(n^log2(7)) ~ O(n^2.807).
//Formulas y estructura de la recursion tomadas de:
//GeeksforGeeks. (2025, 29 de agosto). Strassen's Matrix Multiplication.
//https://www.geeksforgeeks.org/dsa/strassens-matrix-multiplication/

#include <vector>
#include <cmath>

using Matrix = std::vector<std::vector<int>>;

// Suma (sign=1) o resta (sign=-1) dos matrices size x size.
static Matrix addSub(const Matrix& A, const Matrix& B, int size, int sign) {
    Matrix res(size, std::vector<int>(size));
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            res[i][j] = A[i][j] + sign * B[i][j];
    return res;
}

// Rellena una matriz con ceros hasta convertirla en newSize x newSize.
static Matrix resize(const Matrix& mat, int newSize) {
    Matrix res(newSize, std::vector<int>(newSize, 0));
    for (size_t i = 0; i < mat.size(); i++)
        for (size_t j = 0; j < mat[i].size(); j++)
            res[i][j] = mat[i][j];
    return res;
}

// Multiplicacion naive, usada como caso base de la recursion (para
// matrices pequenas resulta mas eficiente que seguir dividiendo).
static Matrix baseMultiply(const Matrix& A, const Matrix& B, int size) {
    Matrix C(size, std::vector<int>(size, 0));
    for (int i = 0; i < size; i++)
        for (int k = 0; k < size; k++)
            for (int j = 0; j < size; j++)
                C[i][j] += A[i][k] * B[k][j];
    return C;
}

// Multiplica dos matrices cuadradas size x size (size potencia de 2)
// usando el algoritmo de Strassen de forma recursiva.
static Matrix strassenRec(const Matrix& A, const Matrix& B, int size) {

    // Caso base: por debajo de este tamano, la multiplicacion naive es
    // mas rapida que seguir dividiendo (evita el overhead de la recursion).
    const int BASE_CASE_SIZE = 32;
    if (size <= BASE_CASE_SIZE)
        return baseMultiply(A, B, size);

    int half = size / 2;
    Matrix A11(half, std::vector<int>(half)), A12(half, std::vector<int>(half)),
           A21(half, std::vector<int>(half)), A22(half, std::vector<int>(half)),
           B11(half, std::vector<int>(half)), B12(half, std::vector<int>(half)),
           B21(half, std::vector<int>(half)), B22(half, std::vector<int>(half));

    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + half];
            A21[i][j] = A[i + half][j];
            A22[i][j] = A[i + half][j + half];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + half];
            B21[i][j] = B[i + half][j];
            B22[i][j] = B[i + half][j + half];
        }
    }

    // Las 7 multiplicaciones de Strassen (en vez de las 8 del metodo
    // por bloques directo).
    Matrix M1 = strassenRec(addSub(A11, A22, half, 1), addSub(B11, B22, half, 1), half);
    Matrix M2 = strassenRec(addSub(A21, A22, half, 1), B11, half);
    Matrix M3 = strassenRec(A11, addSub(B12, B22, half, -1), half);
    Matrix M4 = strassenRec(A22, addSub(B21, B11, half, -1), half);
    Matrix M5 = strassenRec(addSub(A11, A12, half, 1), B22, half);
    Matrix M6 = strassenRec(addSub(A21, A11, half, -1), addSub(B11, B12, half, 1), half);
    Matrix M7 = strassenRec(addSub(A12, A22, half, -1), addSub(B21, B22, half, 1), half);

    // Combinacion de los 7 productos en los 4 cuadrantes de C.
    Matrix C11 = addSub(addSub(addSub(M1, M4, half, 1), M5, half, -1), M7, half, 1);
    Matrix C12 = addSub(M3, M5, half, 1);
    Matrix C21 = addSub(M2, M4, half, 1);
    Matrix C22 = addSub(addSub(addSub(M1, M2, half, -1), M3, half, 1), M6, half, 1);

    Matrix C(size, std::vector<int>(size));
    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            C[i][j] = C11[i][j];
            C[i][j + half] = C12[i][j];
            C[i + half][j] = C21[i][j];
            C[i + half][j + half] = C22[i][j];
        }
    }

    return C;
}

// Wrapper: acepta matrices cuadradas de cualquier tamano n x n.
// Si n no es potencia de 2, rellena con ceros hasta la siguiente
// potencia de 2 y luego recorta el resultado a n x n.
// (No es necesario para los tamanos del enunciado: 2^4, 2^6, 2^8, 2^10
// ya son todos potencias de 2, pero se deja de forma generica.)
std::vector<std::vector<int>> strassenMultiply(const std::vector<std::vector<int>>& A,
                                                const std::vector<std::vector<int>>& B) {
    int n = static_cast<int>(A.size());

    int m = 1;
    while (m < n) m <<= 1;

    if (m == n) {
        return strassenRec(A, B, n);
    }

    Matrix Apad = resize(A, m);
    Matrix Bpad = resize(B, m);
    Matrix Cpad = strassenRec(Apad, Bpad, m);

    Matrix C(n, std::vector<int>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = Cpad[i][j];

    return C;
}
