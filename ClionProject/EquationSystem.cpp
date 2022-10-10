#include "EquationSystem.h"

void NormalizeEquationSystem(Matrix& A, Vector& b) {
    // 1).For each row i:
    //     Divide all numbers in row by their greatest common divisor (only if there is a non-zero number in row);
    for (size_t i = 0; i < A.height; i++) {
        int row_gcd = 0;
        for (size_t j = 0; j < A.width; j++) {
            row_gcd = std::gcd(row_gcd, int(A.matrix[i][j]));
        }
        if (row_gcd != 0) {
            for (size_t j = 0; j < A.width; j++) {
                A.matrix[i][j] /= Rational(row_gcd);
            }
            b.vector[i] /= row_gcd;
        }
    }

    // 2). Keep only distinct rows in matrix by deleting matches
    //     To do this, for each row, we will multiply all numbers in row by -1
    //     if first non-zero number in row is negative.
    //     Then, we sort all rows in increasing lexicographical order and use std::unique to delete matches.
    for (size_t i = 0; i < A.height; i++) {
        for (size_t j = 0; j < A.width; j++) {
            if (A.matrix[i][j] != 0) {
                if (A.matrix[i][j] < 0) {
                    for (; j < A.width; j++) {
                        A.matrix[i][j] *= Rational(-1);
                    }
                    b.vector[i] *= -1;
                }
                break;
            }
        }
    }

    // During execution of point 2)., we can execute point 3):
    // 3). Move rows so that first non-zero value in each row
    //     comes no earlier than first non-zero value in previous row.
    //     (if we swap rows in matrix A, vector b also changes)
    std::vector<std::pair<std::vector<int>, int> > EquationSystemRows(A.height);
    for (size_t i = 0; i < A.height; i++) {
        EquationSystemRows[i] = {A.matrix[i], b.vector[i]};
    }

    sort(EquationSystemRows.begin(), EquationSystemRows.end(),
         [](auto row1, auto row2) {
        for (size_t i = 0; i < row1.first.size(); i++) {
            if (row1.first[i] != 0 && row2.first[i] != 0) {
                return row1 < row2;
            } else if (row1.first[i] != 0) {
                return true;
            } else if (row2.first[i] != 0) {
                return false;
            }
        }
    });
    EquationSystemRows.erase(unique(EquationSystemRows.begin(), EquationSystemRows.end()), EquationSystemRows.end());

    A.height = EquationSystemRows.size();
    A.matrix.resize(A.height);

    b.size = EquationSystemRows.size();
    b.vector.resize(b.size);

    for (size_t i = 0; i < EquationSystemRows.size(); i++) {
        A.matrix[i] = EquationSystemRows[i].first;
        b.vector[i] = EquationSystemRows[i].second;
    }
}

std::vector<int> Gauss(Matrix A, Vector b) {
    NormalizeEquationSystem(A, b);

    // TODO
}
