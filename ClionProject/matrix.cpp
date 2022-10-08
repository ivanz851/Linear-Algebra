#include "matrix.h"

Matrix::Matrix() {
    height = 0;
    width = 0;
    matrix = std::vector<std::vector<int>> (0, std::vector<int> (0));
}

Matrix::Matrix(size_t height_, size_t width_) : height(height_), width(width_) {
    matrix = std::vector<std::vector<int>> (height, std::vector<int> (width, 0));
}

Matrix Matrix::operator+(const Matrix& other) const {
    if (this->height != other.height || this->width != other.width) {
        // ERROR
    }

    Matrix res = *this;
    for (size_t i = 0; i < height; ++i) {
        for (size_t j = 0; j < width; j++) {
            res.matrix[i][j] += other.matrix[i][j];
        }
    }
    return res;
}

const Matrix& Matrix::operator+=(const Matrix& other) {
    return *this = *this + other;
}

void Matrix::PrintMatrix() {
    std::cout << "matrix height " << height << "\n";
    std::cout << "matrix width " << width << "\n";
    std::cout << "matrix = \n";
    for (size_t i = 0; i < height; ++i) {
        for (size_t j = 0; j < width; ++j) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

int main () {
    Matrix m;

    m.PrintMatrix();
}