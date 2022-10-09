#include "Problem_1.h"

#include "Matrix.h"

void Problem_1() {
    Matrix A(5, 3,
             {{1, 3, 2},
              {4, 2, -2},
              {3, -4, -7},
              {2, 4, 2},
              {-1, -3, -2}});

    Matrix B(3, 4,
             {{3, 0, 0, 1},
              {-1, 0, 1, 0},
              {2, 1, 0, 0}});

    A *= B;
    PrintMatrix(A);

    A.NormalizeEquationSystem();

    PrintMatrix(A);
}