#pragma "once"

#include "Matrix.h"
#include "Vector.h"

// Normalizes matrix (A in form A * x = B) as follows
// (consider the system of linear equations corresponding to the given matrix):
// 1).For each row i:
//     Divide all numbers in row by their greatest common divisor (only if there is a non-zero number in row);
// 2). Keep only distinct rows in matrix by removing matches
// 3). Move rows so that first non-zero value in each row
//     comes no earlier than first non-zero value in previous row.
//     (if we swap rows in matrix A, matrix B also changes)
template<typename T>
void NormalizeEquationSystem(Matrix<T>& A, Matrix<T>& b);

// Solves linear equations system of form: A * x = b, where A is matrix n * m, b is vector n * 1 and x is tuple 1 * m
template<typename T>
std::vector<int> Gauss(Matrix<T> A, Matrix<T> b);