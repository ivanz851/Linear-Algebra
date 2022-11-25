#include "Problem_1.h"

#include "Matrix.h"

void Problem_1() {
    Matrix<int> A(5, 3,
             {{1, 3, 2},
              {4, 2, -2},
              {3, -4, -7},
              {2, 4, 2},
              {-1, -3, -2}});

    Matrix<int> B(3, 4,
             {{3, 0, 0, 1},
              {-1, 0, 1, 0},
              {2, 1, 0, 0}});

    A *= B;
    PrintMatrix(A);

    /*
    matrix height 5
    matrix width 4
    matrix =
    4 2 3 1
    6 -2 2 4
    -1 -7 -4 3
    6 2 4 2
    -4 -2 -3 -1
     */

    //A.NormalizeEquationSystem();

    //PrintMatrix(A);
}