using permutation = std::vector<int>;

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
            std::swap(p_next[i], p_next[min_ind]);
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

int get_sign(permutation p) {
    int n = p.size();

    int res = 0;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            res += p[i] > p[j];
        }
    }

    if (res & 1) {
        return -1;
    } else {
        return 1;
    }
}