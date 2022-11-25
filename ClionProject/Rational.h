#pragma "once"

#include <cstdint>
#include <iostream>

class Rational {
public:

    // Default constructor which initializes rational number equal to zero (0/1)
    Rational();
    // Constructor which initializes rational number (numerator_/1)
    Rational(int numerator_);
    explicit Rational(__int128 numerator_);
    // Constructor which initializes rational number (numerator_/denominator_)
    Rational(__int128 numerator_, __int128 denominator_);

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

    explicit operator __int128() const;


    bool operator==(const Rational& other) const;
    bool operator!=(const Rational& other) const;

    // TODO: implement spaceship operator
    bool operator<(const Rational& other) const;
    bool operator>(const Rational& other) const;

    bool operator<=(const Rational& other) const;
    bool operator>=(const Rational& other) const;


    //void print() const;

// Normalizes rational number such that greatest common divisor of numerator and denominator is 1
void Normalize();

private:
    __int128 numerator;
    __int128 denominator;

    static __int128 Gcd(__int128 a, __int128 b);

};