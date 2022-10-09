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

    // Elementwise addition of two matrices which sizes are pairwise equal
    // If sizes are pairwise distinct, error message appears and matrices don't change
    Matrix operator+(const Matrix& other) const;
    const Matrix& operator+=(const Matrix& other);

    // Unary operator- replaces each element of the matrix with its opposite
    Matrix operator-() const;
    // Elementwise subtraction of two matrices which sizes are pairwise equal
    // If sizes are pairwise distinct, error message appears and matrices don't change
    Matrix operator-(const Matrix& other) const;
    const Matrix& operator-=(const Matrix& other);

    // For matrices satisfying the condition: the width of the first is equal to the height of the second
    // Multiplication according to the rule "row by column"
    // If required dimensions are distinct, error message appears and matrices don't change
    Matrix operator*(const Matrix& other) const;
    const Matrix& operator*=(const Matrix& other);


    friend void PrintMatrix(const Matrix& A);

private:
    size_t height, width; // height and width of the matrix
    std::vector<std::vector<int>> matrix; // matrix

protected:

};


