#pragma once

#include <iostream>
#include <vector>

class Matrix {
public:
    // Default constructor which initializes empty matrix
    Matrix();
    // Constructor which initializes n * m matrix filled with zeros
    Matrix(size_t height_, size_t width_);

    // operator+ for two matrices which sizes are pairwise equal
    Matrix operator+(const Matrix& other) const;
    const Matrix& operator+=(const Matrix& other);


    void PrintMatrix();


private:
    size_t height, width; // height and width of the matrix
    std::vector<std::vector<int>> matrix; // matrix

protected:

};