#pragma once

#include <deque>
#include <map>
#include <ostream>
#include <string>
#include <vector>

class Poly {
public:
    struct Monomial {
        size_t power;
        int64_t coefficient;

        bool operator==(const Monomial& other) const {
            return this->power == other.power && this->coefficient == other.coefficient;
        }
    };

    Poly();
    Poly(const std::initializer_list<int64_t>& coefficients);
    Poly(const std::initializer_list<Poly::Monomial>& monomials);

    int64_t operator()(const int64_t& x) const;

    bool operator==(const Poly& other) const;

    Poly operator+(const Poly& other) const;
    const Poly& operator+=(const Poly& other);

    Poly operator-() const;
    Poly operator-(const Poly& other) const;
    const Poly& operator-=(const Poly& other);

    Poly operator*(const Poly& other) const;
    const Poly& operator*=(const Poly& other);

    // friend void operator>>(std::istream& in, Poly& poly);
    friend std::ostream& operator<<(std::ostream& out, const Poly& poly);

private:
    std::vector<Monomial> monomials_;
    size_t max_power_;
};