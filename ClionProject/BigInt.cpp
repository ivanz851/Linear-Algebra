#include "BigInt.h"

BigInt::BigInt() {
    is_positive_ = true;
    digits_ = {};
}

BigInt::BigInt(bool is_positive, std::vector<int64_t> digits) : is_positive_(is_positive), digits_(digits) {
    while (!digits_.empty() && digits_.back() == 0) {
        digits_.pop_back();
    }
    if (digits_.empty()) {
        is_positive_ = true;
    }
}

BigInt::BigInt(int64_t x) {
    is_positive_ = x >= 0;
    x = std::abs(x);

    digits_ = {};
    while (x) {
        digits_.push_back(x % BASE);
        x /= BASE;
    }
}

BigInt::operator bool() const {
    return !(this->is_positive_ && this->digits_.empty());
}

bool BigInt::operator==(const BigInt& other) const {
    return this->is_positive_ == other.is_positive_ && this->digits_ == other.digits_;
}

bool BigInt::operator<(const BigInt& other) const {
    if ((*this) == other) {
        return false;
    }

    if (!this->is_positive_ && !other.is_positive_) {
        return -other < -(*this);
    } else if (this->is_positive_ && !other.is_positive_) {
        return false;
    } else if (!this->is_positive_ && other.is_positive_) {
        return true;
    } else {
        // comparison of two positive numbers
        if (this->digits_.size() < other.digits_.size()) {
            return true;
        } else if (this->digits_.size() > other.digits_.size()) {
            return false;
        } else {
            for (size_t i = this->digits_.size() - 1;; --i) {
                if (this->digits_[i] < other.digits_[i]) {
                    return true;
                } else if (this->digits_[i] > other.digits_[i]) {
                    return false;
                }
                if (!i) {
                    break;
                }
            }
            // crutch for compiler; in fact, never reachable
            return true;
        }
    }
}

bool BigInt::operator<(const int64_t& other) const {
    return (*this) < BigInt(other);
}

bool BigInt::operator>(const BigInt& other) const {
    return other < (*this);
}

bool BigInt::operator>(const int64_t& other) const {
    return (*this) > BigInt(other);
}

BigInt BigInt::operator+(const BigInt& other) const {
    BigInt res;
    if (!this->is_positive_ && !other.is_positive_) {
        res = -(-(*this) + -other);
    } else if (this->is_positive_ && !other.is_positive_) {
        res = (*this) - -other;
    } else if (!this->is_positive_ && other.is_positive_) {
        res = other - -(*this);
    } else {
        // sum of positive numbers
        res = *this;
        int64_t carry = 0;
        for (size_t i = 0; i < std::max(this->digits_.size(), other.digits_.size()) || carry; ++i) {
            if (i == res.digits_.size()) {
                res.digits_.push_back(0);
            }
            res.digits_[i] += carry + (i < other.digits_.size() ? other.digits_[i] : 0);
            carry = res.digits_[i] >= BASE;
            if (carry) {
                res.digits_[i] -= BASE;
            }
        }
    }
    while (!res.digits_.empty() && res.digits_.back() == 0) {
        res.digits_.pop_back();
    }
    if (res.digits_.empty()) {
        res.is_positive_ = true;
    }
    return res;
}

const BigInt& BigInt::operator+=(const BigInt& other) {
    return *this = *this + other;
}

BigInt BigInt::operator-() const {
    return BigInt(!(this->is_positive_), this->digits_);
}

BigInt BigInt::operator-(const BigInt& other) const {
    BigInt res;
    if (!this->is_positive_ && !other.is_positive_) {
        res = -other + (*this);
    } else if (this->is_positive_ && !other.is_positive_) {
        res = (*this) + -other;
    } else if (!this->is_positive_ && other.is_positive_) {
        res - (-(*this) + other);
    } else {
        if ((*this) < other) {
            res = -(other - (*this));
        } else {
            // difference of "big" and "small" positive numbers
            res = *this;
            int64_t carry = 0;
            for (size_t i = 0; i < other.digits_.size() || carry; ++i) {
                res.digits_[i] -= carry + (i < other.digits_.size() ? other.digits_[i] : 0);
                carry = res.digits_[i] < 0;
                if (carry) {
                    res.digits_[i] += BASE;
                }
            }
        }
    }
    while (!res.digits_.empty() && res.digits_.back() == 0) {
        res.digits_.pop_back();
    }
    if (res.digits_.empty()) {
        res.is_positive_ = true;
    }
    return res;
}

const BigInt& BigInt::operator-=(const BigInt& other) {
    return *this = *this - other;
}

BigInt BigInt::operator*(const BigInt& other) const {
    if (IsZero(*this) || IsZero(other)) {
        return BigInt(0);
    }

    BigInt res;
    res.is_positive_ = (this->is_positive_ == other.is_positive_);

    res.digits_.resize(this->digits_.size() + other.digits_.size());
    for (size_t i = 0; i < this->digits_.size(); ++i) {
        int64_t carry = 0;
        for (size_t j = 0; j < other.digits_.size() || carry; ++j) {
            int64_t cur =
                    res.digits_[i + j] + this->digits_[i] * (j < other.digits_.size() ? other.digits_[j] : 0) + carry;
            res.digits_[i + j] = cur % BASE;
            carry = cur / BASE;
        }
    }
    while (!res.digits_.empty() && res.digits_.back() == 0) {
        res.digits_.pop_back();
    }

    return res;
}

const BigInt& BigInt::operator*=(const BigInt& other) {
    return *this = *this * other;
}

std::istream& operator>>(std::istream& in, BigInt& a) {
    std::string s;
    // cin >> s;

    for (int i = static_cast<int>(s.size()); i > 0; i -= 9) {
        if (i < 9) {
            a.digits_.push_back(atoi(s.substr(0, i).c_str()));
        } else {
            a.digits_.push_back(atoi(s.substr(i - 9, 9).c_str()));
        }
    }
    return in;
}

std::ostream& operator<<(std::ostream& out, const BigInt& a) {
    if (!a.is_positive_) {
        out << "-";
    }

    out << (a.digits_.empty() ? 0 : a.digits_.back());

    if (a.digits_.size() >= 2) {
        for (size_t i = a.digits_.size() - 2;; --i) {
            out << BigInt::ToNineSymbols(a.digits_[i]);
            if (!i) {
                break;
            }
        }
    }

    return out;
}

BigInt BigInt::Abs(const BigInt& a) {
    return BigInt(true, a.digits_);
}

std::string BigInt::ToNineSymbols(int64_t x) {
    std::string x_str;
    if (!x) {
        x_str = "0";
    } else {
        while (x != 0) {
            x_str += static_cast<char>('0' + (x % 10));
            x /= 10;
        }
        reverse(x_str.begin(), x_str.end());
    }
    std::string s;
    while (s.size() + x_str.size() < 9) {
        s += "0";
    }
    return s + x_str;
}

bool BigInt::IsZero(const BigInt& a) const {
    return a.digits_.empty();
}

int64_t BigInt::ToInt(const BigInt& a) {
    if (a.IsZero(a)) {
        return 0;
    } else {
        int64_t res = (a.is_positive_ ? 1 : -1) * a.digits_.back();

        if (a.digits_.size() >= 2) {
            for (size_t i = a.digits_.size() - 2;; --i) {
                res *= BASE;
                res += a.digits_[i];
                if (i == 0) {
                    break;
                }
            }
        }

        return res;
    }
}
