template<typename T>
Matrix<T>::Matrix() {
    height = 0;
    width = 0;
    matrix = std::vector<std::vector<T>> (0, std::vector<T> (0));
}


template<typename T>
Matrix<T>::Matrix(size_t height_, size_t width_) : height(height_), width(width_) {
    matrix = std::vector<std::vector<T>> (height, std::vector<T> (width, T()));
}

template<typename T>
Matrix<T>::Matrix(size_t height_, size_t width_, std::initializer_list<std::initializer_list<T>> matrix_) {
    height = height_, width = width_;

    matrix.assign(height, std::vector<T>(width));
    size_t matrix_row = 0;
    for (const auto& row : matrix_) {
        size_t matrix_column = 0;
        for (const auto &i: row) {
            matrix[matrix_row][matrix_column++] = i;
        }
        matrix_row++;
    }
}

template<typename T>
Matrix<T>::Matrix(Matrix<T> const &other) {
    height = other.height, width = other.width;

    matrix.assign(height, std::vector<T>(width));
    size_t matrix_row = 0;
    for (const auto& row : other.matrix) {
        size_t matrix_column = 0;
        for (const auto &i: row) {
            matrix[matrix_row][matrix_column++] = i;
        }
        matrix_row++;
    }
}


template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& other) const {
    if (this->height != other.height || this->width != other.width) {
        //ReportError("You are trying to find sum of matrices which sizes are pairwise distinct.");
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

template<typename T>
const Matrix<T>& Matrix<T>::operator+=(const Matrix<T>& other) {
    return *this = *this + other;
}

template<typename T>
Matrix<T> Matrix<T>::operator-() const {
    Matrix res = *this;
    for (size_t i = 0; i < height; ++i) {
        for (size_t j = 0; j < width; j++) {
            res.matrix[i][j] = -res.matrix[i][j];
        }
    }
    return res;
}

template<typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T>& other) const {
    if (this->height != other.height || this->width != other.width) {
        //ReportError("You are trying to find difference of matrices which sizes are pairwise distinct.");
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

template<typename T>
const Matrix<T>& Matrix<T>::operator-=(const Matrix<T>& other) {
    return *this = *this - other;
}

template<typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& other) const {
    if (this->width != other.height) {
        //ReportError("You are trying to multiply matrices such that "
        //            "width of first matrix is not equal to height of second matrix.");
        return *this;
    }

    Matrix<T> res(this->height, other.width);
    for (size_t k = 0; k < this->width; ++k) {
        for (size_t i = 0; i < this->height; ++i) {
            for (size_t j = 0; j < other.width; j++) {
                res.matrix[i][j] += this->matrix[i][k] * other.matrix[k][j];
            }
        }
    }
    return res;
}

template<typename T>
const Matrix<T>& Matrix<T>::operator*=(const Matrix<T>& other) {
    return *this = *this * other;
}

template<typename T>
void PrintMatrix(const Matrix<T>& A) {
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
