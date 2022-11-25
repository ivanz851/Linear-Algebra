#pragma once

#include <iostream>
#include <numeric>
#include <vector>

template<typename T>
class Matrix {
public:
    // height and width of the matrix
    size_t height;
    size_t width;
    // matrix
    std::vector<std::vector<T>> matrix;

    // Default constructor which initializes empty matrix
    Matrix();
    // Constructor which initializes height_ * width matrix filled with zeros
    Matrix(size_t height_, size_t width_);
    // Constructor which initializes height_ * width matrix filled with matrix_ values
    Matrix(size_t height_, size_t width_, std::initializer_list<std::initializer_list<T>> matrix_);

    // Elementwise addition of two matrices which sizes are pairwise equal
    // If sizes are pairwise distinct, error message appears and matrices don't change
    Matrix<T> operator+(const Matrix<T>& other) const;
    const Matrix<T>& operator+=(const Matrix<T>& other);

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

    Matrix FindInverse() {
        /// TODO Inverse matrix exists only for square matrices


    }

    // Prints matrix
    friend void PrintMatrix(const Matrix& A);
};


