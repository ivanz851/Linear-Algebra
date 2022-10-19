#pragma "once"

#include <cstdint>
#include <iostream>

class Rational {
public:

    // Default constructor which initializes rational number equal to zero (0/1)
    Rational();
    // Constructor which initializes rational number (numerator_/1)
    explicit Rational(int64_t numerator_);
    // Constructor which initializes rational number (numerator_/denominator_)
    Rational(int64_t numerator_, int64_t denominator_);

    friend std::ostream& operator<<(std::ostream& out, const Rational& poly);

    Rational& operator=(const Rational& other);

    // Addition of two rational numbers
    Rational operator+(const Rational& other) const;
    const Rational& operator+=(const Rational& other);

    // Unary operator-: -(a/b) = (-a/b)
    Rational operator-() const;
    // Subtraction of two rational numbers
    Rational operator-(const Rational& other) const;
    const Rational& operator-=(const Rational& other);

    // Multiplication of two rational numbers
    Rational operator*(const Rational& other) const;
    const Rational& operator*=(const Rational& other);

    // Division of two rational numbers a and b where b != 0
    // If b == 0, error message appears and division does not occur
    Rational operator/(const Rational& other) const;
    const Rational& operator/=(const Rational& other);

    explicit operator int64_t() const;


    bool operator==(const Rational& other) const;
    bool operator!=(const Rational& other) const;

    // TODO: implement spaceship operator
    bool operator<(const Rational& other) const;
    bool operator>(const Rational& other) const;

    bool operator<=(const Rational& other) const;
    bool operator>=(const Rational& other) const;


    //void print() const;

private:
    int64_t numerator;
    int64_t denominator;

    static int64_t Gcd(int64_t a, int64_t b);

    // Normalizes rational number such that greatest common divisor of numerator and denominator is 1
    void Normalize();
};