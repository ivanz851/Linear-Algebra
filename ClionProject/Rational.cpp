#include "exceptions.h"
#include "Rational.h"

Rational::Rational() {
    nominator = 0;
    denominator = 1;
}

Rational::Rational(int64_t nominator_) : nominator(nominator_), denominator(1) {

}

Rational::Rational(int64_t nominator_, int64_t denominator_) {
    if (denominator_ == 0) {
        ReportError("You are trying to create rational number with zero denominator.");
        nominator = 0;
        denominator = 0;
        return;
    }

    nominator = nominator_;
    if (denominator_ < 0) {
        denominator_ *= -1;
        nominator *= -1;
    }
    denominator = denominator_;
    Normalize();
}

std::ostream& operator<<(std::ostream& out, const Rational& a) {
    return out << a.nominator << "/" << a.denominator << "\n";
}

Rational& Rational::operator=(const Rational& other) {
    if (other.denominator == 0) {
        ReportError("You are trying to assign rational number with zero denominator.");
    } else {
        this->nominator = other.nominator;
        this->denominator = other.denominator;
    }
}

Rational Rational::operator+(const Rational& other) const {
    if (other.denominator == 0) {
        ReportError("You are trying to add rational number with zero denominator.");
        return *this;
    } else {
        return {nominator * other.denominator + other.nominator * denominator,
                        denominator * other.denominator};
    }
}

const Rational& Rational::operator+=(const Rational& other) {
    return *this = *this + other;
}

Rational Rational::operator-() const {
    Rational res = *this;
    res.nominator = -res.nominator;
    return res;
}

Rational Rational::operator-(const Rational& other) const {
    if (other.denominator == 0) {
        ReportError("You are trying to subtract rational number with zero denominator.");
        return *this;
    } else {
        return {nominator * other.denominator - other.nominator * denominator,
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
        return {nominator * other.nominator,
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
    } else if (other.nominator == 0) {
        ReportError("You are trying to divide by zero.");
        return *this;
    } else {
        return {nominator * other.denominator,
                        denominator * other.nominator};
    }
}

const Rational& Rational::operator/=(const Rational& other) {
    return *this = *this * other;
}

/*
void Rational::print() const {
    std::cout << nominator << "/" << denominator << "\n";
}
 */
Rational::operator int() const {
    if (denominator == 0) {
        // ERROR
    } else if (denominator != 1) {
        // ERROR
    }

    return nominator;
}

int64_t Rational::Gcd(int64_t a, int64_t b) {
    a = std::abs(a);
    b = std::abs(b);

    while (b != 0) {
        a %= b;
        std::swap(a, b);
    }
    return a;
}

void Rational::Normalize() {
    int64_t g = Gcd(std::abs(nominator),denominator);
    nominator /= g;
    denominator /= g;
}