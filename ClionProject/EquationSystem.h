#pragma "once"

#include "Matrix.h"
#include "Vector.h"

// Normalizes matrix (A in form A * x = b) as follows
// (consider the system of linear equations corresponding to the given matrix):
// 1).For each row i:
//     Divide all numbers in row by their greatest common divisor (only if there is a non-zero number in row);
// 2). Keep only distinct rows in matrix by removing matches
// 3). Move rows so that first non-zero value in each row
//     comes no earlier than first non-zero value in previous row.
//     (if we swap rows in matrix A, vector b also changes)
void NormalizeEquationSystem(Matrix& A, Vector& b);

// Solves linear equations system of form: A * x = b, where A is matrix n * m, b is vector n * 1 and x is tuple 1 * m
std::vector<int> Gauss(Matrix A, Vector b);