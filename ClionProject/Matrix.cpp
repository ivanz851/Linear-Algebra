#include "exceptions.h"
#include "Matrix.h"

Matrix::Matrix() {
    height = 0;
    width = 0;
    matrix = std::vector<std::vector<int>> (0, std::vector<int> (0));
}

Matrix::Matrix(size_t height_, size_t width_) : height(height_), width(width_) {
    matrix = std::vector<std::vector<int>> (height, std::vector<int> (width, 0));
}

Matrix::Matrix(size_t height_, size_t width_, std::initializer_list<std::initializer_list<int>> matrix_) :
    height(height_), width(width_) {
    matrix.assign(height, std::vector<int>(width));
    size_t i = 0;
    for (const auto& row : matrix_) {
        copy(row.begin(), row.end(), matrix[i++].begin());
    }
}

Matrix Matrix::operator+(const Matrix& other) const {
    if (this->height != other.height || this->width != other.width) {
        ReportError("You are trying to find sum of matrices which sizes are pairwise distinct.");
        return *this;
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

Matrix Matrix::operator-() const {
    Matrix res = *this;
    for (size_t i = 0; i < height; ++i) {
        for (size_t j = 0; j < width; j++) {
            res.matrix[i][j] = -res.matrix[i][j];
        }
    }
    return res;
}

Matrix Matrix::operator-(const Matrix& other) const {
    if (this->height != other.height || this->width != other.width) {
        ReportError("You are trying to find difference of matrices which sizes are pairwise distinct.");
        return *this;
    }

    Matrix res = *this;
    for (size_t i = 0; i < height; ++i) {
        for (size_t j = 0; j < width; j++) {
            res.matrix[i][j] -= other.matrix[i][j];
        }
    }
    return res;
}

const Matrix& Matrix::operator-=(const Matrix& other) {
    return *this = *this - other;
}

Matrix Matrix::operator*(const Matrix& other) const {
    if (this->width != other.height) {
        ReportError("You are trying to multiply matrices such that "
                    "width of first matrix is not equal to height of second matrix.");
        return *this;
    }

    Matrix res(this->height, other.width);
    for (size_t k = 0; k < this->width; ++k) {
        for (size_t i = 0; i < this->height; ++i) {
            for (size_t j = 0; j < other.width; j++) {
                res.matrix[i][j] = this->matrix[i][k] + other.matrix[k][j];
            }
        }
    }
    return res;
}

const Matrix& Matrix::operator*=(const Matrix& other) {
    return *this = *this * other;
}

void PrintMatrix(const Matrix& A) {
    std::cout << "matrix height " << A.height << "\n";
    std::cout << "matrix width " << A.width << "\n";
    std::cout << "matrix = \n";
    for (size_t i = 0; i < A.height; ++i) {
        for (size_t j = 0; j < A.width; ++j) {
            std::cout << A.matrix[i][j] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}
