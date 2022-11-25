#include "exceptions.h"
#include "Rational.h"

Rational::Rational() {
    numerator = 0;
    denominator = 1;
}

Rational::Rational(int numerator_) : numerator(numerator_), denominator(1) {

}

Rational::Rational(__int128 numerator_) : numerator(numerator_), denominator(1) {

}

Rational::Rational(__int128 numerator_, __int128 denominator_) {
    if (denominator_ == 0) {
        ReportError("You are trying to create rational number with zero denominator.");
        numerator = 0;
        denominator = 0;
        return;
    }

    numerator = numerator_;
    if (denominator_ < 0) {
        denominator_ *= -1;
        numerator *= -1;
    }
    denominator = denominator_;
    Normalize();
}

std::ostream& operator<<(std::ostream& out, const Rational& a) {
    if (a.denominator == 1) {
        return out << (int64_t)a.numerator;
    } else {
        return out << (int64_t)a.numerator << "/" << (int64_t)a.denominator;
    }
}

Rational& Rational::operator=(const Rational& other) {
    if (other.denominator == 0) {
        ReportError("You are trying to assign rational number with zero denominator.");
    } else {
        this->numerator = other.numerator;
        this->denominator = other.denominator;
    }
}

Rational Rational::operator+(const Rational& other) const {
    if (other.denominator == 0) {
        ReportError("You are trying to add rational number with zero denominator.");
        return *this;
    } else {
        return {numerator * other.denominator + other.numerator * denominator,
                        denominator * other.denominator};
    }
}

const Rational& Rational::operator+=(const Rational& other) {
    return *this = *this + other;
}

Rational Rational::operator-() const {
    Rational res = *this;
    res.numerator = -res.numerator;
    return res;
}

Rational Rational::operator-(const Rational& other) const {
    if (other.denominator == 0) {
        ReportError("You are trying to subtract rational number with zero denominator.");
        return *this;
    } else {
        return {numerator * other.denominator - other.numerator * denominator,
                        denominator * other.denominator};
    }
}

const Rational& Rational::operator-=(const Rational& other) {
    return *this = *this - other;
}

Rational Rational::operator*(const Rational& other) const {
    if (other.denominator == 0) {
        ReportError("You are trying to multiply by rational number with zero denominator.");
        return *this;
    } else {
        return {numerator * other.numerator,
                        denominator * other.denominator};
    }
}

const Rational& Rational::operator*=(const Rational& other) {
    return *this = *this * other;
}

Rational Rational::operator/(const Rational& other) const {
    if (other.denominator == 0) {
        ReportError("You are trying to divide by rational number with zero denominator.");
        return *this;
    } else if (other.numerator == 0) {
        ReportError("You are trying to divide by zero.");
        return *this;
    } else {
        return {numerator * other.denominator,
                        denominator * other.numerator};
    }
}

const Rational& Rational::operator/=(const Rational& other) {
    return *this = *this / other;
}

/*
void Rational::print() const {
    std::cout << numerator << "/" << denominator << "\n";
}
 */
Rational::operator __int128() const {
    if (denominator == 0) {
        // ERROR
    } else if (denominator != 1) {
        // ERROR
    }

    return numerator;
}

__int128 Rational::Gcd(__int128 a, __int128 b) {
    a = std::abs(a);
    b = std::abs(b);

    while (b != 0) {
        a %= b;
        std::swap(a, b);
    }
    return a;
}

void Rational::Normalize() {
    __int128 g = Gcd(std::abs(numerator),denominator);
    numerator /= g;
    denominator /= g;
}

bool Rational::operator==(const Rational& other) const {
    return this->numerator == other.numerator && this->denominator == other.denominator;
}

bool Rational::operator!=(const Rational& other) const {
    return !(*this == other);
}

bool Rational::operator<(const Rational& other) const {
    return this->numerator * other.denominator < other.numerator * this->denominator;
}

bool Rational::operator>(const Rational& other) const {
    return this->numerator * other.denominator > other.numerator * this->denominator;
}

bool Rational::operator<=(const Rational& other) const {
    return this->numerator * other.denominator <= other.numerator * this->denominator;
}

bool Rational::operator>=(const Rational& other) const {
    return this->numerator * other.denominator >= other.numerator * this->denominator;
}
