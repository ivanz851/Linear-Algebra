template<typename T>
std::vector<T> plus_vector(std::vector<T> a, std::vector<T> b) {
    /// TODO check that a.size() == b.size()

    for (size_t i = 0; i < a.size(); i++) {
        a[i] += b[i];
    }
    return a;
}

template<typename T>
std::vector<T> minus_vector(std::vector<T> a, std::vector<T> b) {
    /// TODO check that a.size() == b.size()

    for (size_t i = 0; i < a.size(); i++) {
        a[i] -= b[i];
    }
    return a;
}

template<typename T>
std::vector<T> mult_vector(std::vector<T> v, T x) {
    for (auto i : v) {
        i *= x;
    }
    return v;
}

template<typename T>
std::vector<T> div_vector(std::vector<T> v, T x) {
    for (auto i : v) {
        i /= x;
    }
    return v;
}

template<typename T>
ssize_t find_first_not_null(std::vector<T> v) {
    for (size_t i = 0; i < v.size(); i++) {
        if (v[i] != 0) {
            return i;
        }
    }
    return -1;
}

template<typename T>
void NormalizeEquationSystem(Matrix<T>& A, Matrix<T>& B) {
    // 1).For each row i:
    //     Divide all numbers in row by first non-zero number (only if there is a non-zero number in row);
    for (size_t i = 0; i < A.height; i++) {
        ssize_t ind_A = find_first_not_null(A.matrix[i]);

        T val;
        val = (ind_A != -1 && A.matrix[i][ind_A] != 0) ? A.matrix[i][ind_A] : 0;
        if (val == 0) {
            ssize_t ind_B = find_first_not_null(B.matrix[i]);
            val = (ind_B != -1 && B.matrix[i][ind_A] != 0) ? B.matrix[i][ind_A] : 0;
        }

        if (val != 0) {
            A.matrix[i] = div_vector(A.matrix[i], val);
            B.matrix[i] = div_vector(B.matrix[i], val);
        }
    }

    // Move rows so that first non-zero value in each row
    // comes no earlier than first non-zero value in previous row.
    // (if we swap rows in matrix A, vector b also changes)
    std::vector<std::pair<std::vector<T>, std::vector<T>> > EquationSystemRows(A.height);
    for (size_t i = 0; i < A.height; i++) {
        EquationSystemRows[i] = {A.matrix[i], B.matrix[i]};
    }

    sort(EquationSystemRows.begin(), EquationSystemRows.end(),
         [] (auto row1, auto row2) {

             ssize_t ind_row1 = find_first_not_null(row1.first);
             ssize_t ind_row2 = find_first_not_null(row2.first);

             if (ind_row1 == -1) {
                 return false;
             } else {
                 return ind_row1 < ind_row2;
             }
         });
    EquationSystemRows.erase(unique(EquationSystemRows.begin(), EquationSystemRows.end()), EquationSystemRows.end());

    A.height = EquationSystemRows.size();
    A.matrix.resize(A.height);

    B.height = EquationSystemRows.size();
    B.matrix.resize(B.height);

    for (size_t i = 0; i < EquationSystemRows.size(); i++) {
        A.matrix[i] = EquationSystemRows[i].first;
        B.matrix[i] = EquationSystemRows[i].second;
    }
}

template<typename T>
Matrix<T> Gauss(Matrix<T> A, Matrix<T> B) {

    while (true) {
        NormalizeEquationSystem(A, B);

        int flag = false;

        for (size_t i = 0; i + 1 < A.height; i++) {
            ssize_t ind_1 = find_first_not_null(A.matrix[i]);
            ssize_t ind_2 = find_first_not_null(A.matrix[i + 1]);

            if (ind_1 == ind_2) {
                A.matrix[i + 1] = minus_vector(A.matrix[i + 1], A.matrix[i]);
                B.matrix[i + 1] = minus_vector(B.matrix[i + 1], B.matrix[i]);
                flag = true;
                break;
            }
        }
        if (!flag) {
            break;
        }
    }

    for (int i = (int)A.height - 1; i >= 0; --i) {
        ssize_t ind = find_first_not_null(A.matrix[i]);
        for (int j = i - 1; j >= 0; --j) {
            if (A.matrix[j][ind] != 0) {
                A.matrix[j] = minus_vector(A.matrix[j], mult_vector(A.matrix[i], -A.matrix[j][ind] ));
                B.matrix[j] = minus_vector(B.matrix[j], mult_vector(B.matrix[i], -B.matrix[j][ind] ));
            }
        }
    }

    return B;
}

