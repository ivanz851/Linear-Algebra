#include "exceptions.h"
#include "matrix.h"

#include <iostream>

using namespace std;

int main() {
    Matrix A(2, 3, {{1, 2, 3}, {4, 5, 6}});
    Matrix B(2, 3, {{10, 20, 30}, {40, 50, 60}});

    A = A - B;
    PrintMatrix(A);
    PrintMatrix(-A);

    Matrix C;
    A += C;

    A *= C;

    cout << "OK\n";
}