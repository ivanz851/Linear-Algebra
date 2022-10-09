#pragma once

#include <iostream>
#include <vector>

class Matrix {
public:
    // Default constructor which initializes empty matrix
    Matrix();
    // Constructor which initializes height_ * width matrix filled with zeros
    Matrix(size_t height_, size_t width_);
    // Constructor which initializes height_ * width matrix filled with matrix_ values
    Matrix(size_t height_, size_t width_, std::initializer_list<std::initializer_list<int>> matrix_);

    // operator+ for two matrices which sizes are pairwise equal
    // If sizes are pairwise distinct, error message appears and matrices don't change
    Matrix operator+(const Matrix& other) const;
    // operator+= for two matrices which sizes are pairwise equal
    // If sizes are pairwise distinct, error message appears and matrices don't change
    const Matrix& operator+=(const Matrix& other);

    // operator+ for two matrices which sizes are pairwise equal
    // If sizes are pairwise distinct, error message appears and matrices don't change
    Matrix operator-(const Matrix& other) const;
    // operator+= for two matrices which sizes are pairwise equal
    // If sizes are pairwise distinct, error message appears and matrices don't change
    const Matrix& operator-=(const Matrix& other);

    friend void PrintMatrix(const Matrix& A);

private:
    size_t height, width; // height and width of the matrix
    std::vector<std::vector<int>> matrix; // matrix

protected:

};


