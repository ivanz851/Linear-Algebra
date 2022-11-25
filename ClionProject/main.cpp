#pragma "once"

#include <vector>
#include <iostream>
#include <algorithm>


#include "Matrix.h"
#include "Poly.h"
#include "EquationSystem.h"

using namespace std;


class Problem1 {

    using permutation = std::vector<int>;

public:
    void solve() {
        std::vector<permutation> res;

        permutation a = {3, 7, 1, 6, 4, 5, 8, 2};
        permutation b = power(composition(FindInverse({7, 2, 3, 1, 4, 6, 5, 8}),
                                          power({6, 8, 2, 4, 3, 5, 1, 7}, 13)), 167);

        permutation p = get_id(8);
        do {
            if (composition({p, a, p}) == b) {
                res.push_back(p);
            }
        } while(NextPermutation(p));

        for (auto it : res) {
            for (int i : it) {
                std::cout << i << " ";
            }
            std::cout << "\n";
        }
    }
};

class Problem2 {

public:
    void solve() {

        Matrix<Rational> A(4, 4,
                           {{-3, 1, -3, 1},
                            {3, 3, 1, -1},
                            {-1, 3, 2, 2},
                            {-3, 3, -3, 2}});;

        Matrix<Rational> B(4, 4,
                            {{4, 4, 2, -1},
                            {4, -8, 7, -2},
                            {-4, 7, -3, 6},
                            {-4, -7, 3, -3}});

        Matrix<Rational> C(4, 4,
                            {{2, -1, -2, 3},
                            {-2, -1, 3, -2},
                            {1, -3, 2, 3},
                            {3, -2, -1, 1}});

        Matrix<Rational> D(4, 4,
                            {{1, -1, 1, 1},
                            {1, -2, 2, 2},
                            {1, -2, 3, 1},
                            {-1, 2, -1, -2}});





        Matrix<Rational> X = FindInverse(A) * D * FindInverse(C);
        X = FindInverse(X) - B;


        for (size_t i = 0; i < X.height; ++i) {
            for (size_t j = 0; j < X.width; ++j) {
                cout << X.matrix[i][j] << " ";
            }
            cout << "\n";
        }
    }
};

class Problem3 {
public:
    void solve() {
        /*
        Matrix<int> A(4, 4, {{4, 3, 3, 5},
                             {4, 2, -2, -4},
                             {-2, 2, -2, -1},
                             {0, 0, 3, 5}});
        */

        Matrix<int> A(4, 4, {{-2, 4, 3, 4},
                             {-1, 2, 4, -2},
                             {-1, 1, -1, -3},
                             {0, 0, -1, -1}});

        int n = A.height;
        Matrix<Poly> P(n, n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                P.matrix[i][j] = Poly({{{0, (A.matrix)[i][j]}}});
            }
        }

        /*
        cout << "C = \n";
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << C.matrix[i][j] << " ";
            }
            cout << "\n";
        }
        cout << "\n\n";
        */


        auto res_char_poly = P.GetCharacteristicPolynomial();
        cout << "RES_CHAR_POLY = " << res_char_poly << "\n";

        Matrix<Rational> E(n, n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                E.matrix[i][j] = 1;
            }
        }

        Matrix<Rational> Ar(n, n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                Ar.matrix[i][j] = A.matrix[i][j];
            }
        }

        auto T = Ar*Ar - E;
        cout << "T = \n";
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << T.matrix[i][j] << " ";
            }
            cout << "\n";
        }
        cout << "\n\n";

        auto Inv = FindInverse((Ar * Ar - E));
        auto Matrix_res = Inv * Inv;

        cout << "Matrix_res = \n";
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << Matrix_res.matrix[i][j] << " ";
            }
            cout << "\n";
        }
        cout << "END\n\n";

        auto res_det = Matrix_res.GetDetRational();

        cout << "Res_det = " << res_det << "\n";
    }
};

class Problem4 {
public:
    void solve() {


        Matrix<Poly> A(7, 7,{
                          {{{0, -4}}, {{0, 3}}, {{0, -3}}, {{0, 4}}, {{1, 1}}, {{0, -7}}, {{0, 2}}},
                          {{{0, 5}}, {{0, 2}}, {{1, 1}}, {{0, 2}}, {{0, -9}}, {{0, 7}}, {{0, -8}}},
                          {{{0, 1}}, {{0, 1}}, {{0, -4}}, {{0, -9}}, {{1, 1}}, {{0, 5}}, {{0, -5}}},
                          {{{0, -7}}, {{0, 2}}, {{0, 9}}, {{0, -4}}, {{0, 2}}, {{1, 1}}, {{0, 7}}},
                          {{{1, 1}}, {{0, 3}}, {{0, 3}}, {{0, 1}}, {{0, 5}}, {{0, -4}}, {{0, -8}}},
                          {{{0, 7}}, {{1, 1}}, {{0, 5}}, {{0, 1}}, {{0, 3}}, {{0, 3}}, {{0, 7}}},
                          {{{0, -4}}, {{0, -7}}, {{0, -8}}, {{1, 1}}, {{0, 5}}, {{0, 6}}, {{1, 1}}}});




        for (auto it : A.matrix) {
            for (auto jt : it) {
                cout << jt << " ";
            }
            cout << "\n";
        }

        Poly det = A.GetDet();
        std::cout << det << "\n";
    }
};

class Problem5 {
public:
    void solve() {


        Matrix<int> A(5, 2,
                      {{3, -3},
                       {4, -4},
                       {-1, 1},
                       {-4, 4},
                       {1, -1}});

        Matrix<int> B(2, 5,
                      {{1, -3, 3, -1, 2},
                       {2, -1, 1, 3, -3}});

        Matrix<int> C = A * B;

        int n = C.height;
        Matrix<Poly> P(n, n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                P.matrix[i][j] = Poly({{{0, (C.matrix)[i][j]}}});
            }
        }

        /*
        cout << "C = \n";
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << C.matrix[i][j] << " ";
            }
            cout << "\n";
        }
        cout << "\n\n";
        */


        auto res = P.GetCharacteristicPolynomial();

        cout << res << "\n";
    }
};

//#include <bits/stdc++.h>
//using namespace std;

int main() {
    //Problem1 problem1;
    //problem1.solve();

    //Problem2 problem2;
    //problem2.solve();

    Problem3 problem3;
    problem3.solve();

    //Problem4 problem4;
    //problem4.solve();

    //Problem5 problem5;
    //problem5.solve();

    return 0;
}