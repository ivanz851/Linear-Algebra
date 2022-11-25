#pragma "once"

#include <vector>
#include <iostream>
#include <algorithm>


#include "Matrix.h"
#include "EquationSystem.h"


using namespace std;

class Problem1 {

    using permutation = std::vector<int>;

public:
    permutation get_id(int n) {
        permutation res(n);
        for (int i = 0; i < n; i++) {
            res[i] = i + 1;
        }
        return res;
    }

    // To test this function I used https://www.eolymp.com/ru/problems/1788
    // Solution: https://site.ada.edu.az/~medv/acm/Docs%20e-olimp/Volume%2018/1788.htm
    permutation FindInverse(const permutation p) {
        size_t n = p.size();
        permutation p_inverse(n);

        for (size_t i = 0; i < n; ++i) {
            p_inverse[p[i] - 1] = i + 1;
        }

        return p_inverse;
    }

    permutation composition(const permutation a, const permutation b) {
        // TODO check that a.size() == b.size()

        size_t n = a.size();
        permutation c(n);

        for (size_t i = 0; i < n; ++i) {
            c[i] = a[b[i] - 1];
        }

        return c;
    }

    permutation composition(std::vector<permutation> v) {
        // TODO check that a.size() == b.size()

        reverse(v.begin(), v.end());
        permutation c = v.front();

        for (size_t i = 1; i < v.size(); ++i) {
            c = composition(v[i], c);
        }

        return c;
    }

    permutation power(const permutation a, int p) {
        // TODO check that p >= 0

        size_t n = a.size();
        permutation res = get_id(n);

        for (int i = 0; i < p; i++) {
            res = composition(a, res);
        }

        return res;
    }

    // To test this function I used https://www.eolymp.com/ru/problems/2386
    // Solution: https://neerc.ifmo.ru/wiki/index.php?title=%D0%9F%D0%BE%D0%BB%D1%83%D1%87%D0%B5%D0%BD%D0%B8%D0%B5_%D1%81%D0%BB%D0%B5%D0%B4%D1%83%D1%8E%D1%89%D0%B5%D0%B3%D0%BE_%D0%BE%D0%B1%D1%8A%D0%B5%D0%BA%D1%82%D0%B0
    bool NextPermutation(permutation& p) {
        size_t n = p.size();
        permutation p_next = p;

        if (n == 1) {
            p = get_id(1);
            return false;
        }

        for (size_t i = n - 2; ; --i) {
            if (p_next[i] < p_next[i + 1]) {
                size_t min_ind = i + 1;

                for (size_t j = i + 1; j < n; ++j) {
                    if (p_next[j] < p_next[min_ind] && p_next[j] > p_next[i]) {
                        min_ind = j;
                    }
                }
                swap(p_next[i], p_next[min_ind]);
                reverse(p_next.begin() + i + 1, p_next.end());

                p = p_next;
                return true;
            }
            if (i == 0) {
                break;
            }
        }

        p = get_id(n);
        return false;
    }

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

        /*
         *
         *
         */

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

        cout << "OK1\n";

        //Matrix<Rational> X = A.FindInverse() * D * C.FindInverse();
        Matrix<Rational> X;
        X = FindInverse<Rational>(X);
        cout << "X = " << X.height << " " << X.width << "\n";
        for (size_t i = 0; i < X.height; ++i) {
            for (size_t j = 0; j < X.width; ++j) {
                cout << X.matrix[i][j] << " ";
            }
            cout << "\n";
        }

        X = FindInverse<Rational>(X) - B;

        cout << "OK2\n";

        for (size_t i = 0; i < X.height; ++i) {
            for (size_t j = 0; j < X.width; ++j) {
                cout << X.matrix[i][j] << " ";
            }
            cout << "\n";
        }
    }
};

class Problem3 {

};

class Problem4 {

};

class Problem5 {

};

//#include <bits/stdc++.h>
//using namespace std;

int main() {
    //Problem1 problem1;
    //problem1.solve();

    Problem2 problem2;
    problem2.solve();

    return 0;
}