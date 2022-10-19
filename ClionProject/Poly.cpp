#include "Poly.h"

Poly::Poly() {
    monomials_ = {};
    max_power_ = 0;
}

Poly::Poly(const std::initializer_list<int64_t>& coefficients) {
    size_t i = 0;
    for (auto it : coefficients) {
        if (it) {
            monomials_.push_back({i, it});
        }
        ++i;
    }
    /*
    for (size_t i = 0; i < coefficients.size(); ++i) {
        if (coefficients[i]) {
            monomials_.push_back({i, coefficients[i]});
        }
    }
    */
    max_power_ = monomials_.empty() ? 0 : monomials_.back().power;
}

Poly::Poly(const std::initializer_list<Poly::Monomial>& monomials) {
    for (const auto& [power, coefficient] : monomials) {
        if (coefficient) {
            monomials_.push_back({power, coefficient});
        }
    }

    max_power_ = monomials_.empty() ? 0 : monomials_.back().power;
}

int64_t Poly::operator()(const int64_t& x) const {
    int64_t res = 0;
    size_t x_power = 0;
    int64_t x_power_val = 1;
    for (const auto& [power, coefficient] : monomials_) {
        while (x_power < power) {
            ++x_power;
            x_power_val *= x;
        }

        res += x_power_val * coefficient;
    }

    return res;
}

bool Poly::operator==(const Poly& other) const {
    return this->monomials_ == other.monomials_;
}

Poly Poly::operator+(const Poly& other) const {
    Poly res = Poly();

    auto other_it = other.monomials_.begin();
    for (const auto& [power, coefficient] : this->monomials_) {
        while (other_it != other.monomials_.end() && other_it->power < power) {
            res.monomials_.push_back({other_it->power, other_it->coefficient});
            other_it++;
        }
        if (other_it != other.monomials_.end() && other_it->power == power) {
            if (coefficient + other_it->coefficient) {
                res.monomials_.push_back({power, coefficient + other_it->coefficient});
            }
            other_it++;
        } else {
            res.monomials_.push_back({power, coefficient});
        }
    }
    while (other_it != other.monomials_.end()) {
        res.monomials_.push_back({other_it->power, other_it->coefficient});
        other_it++;
    }

    res.max_power_ = res.monomials_.empty() ? 0 : res.monomials_.back().power;
    return res;
}

const Poly& Poly::operator+=(const Poly& other) {
    return *this = *this + other;
}

Poly Poly::operator-() const {
    Poly res = *this;
    for (auto& [power, coefficient] : res.monomials_) {
        coefficient = -coefficient;
    }
    return res;
}

Poly Poly::operator-(const Poly& other) const {
    Poly res = Poly();

    auto other_it = other.monomials_.begin();
    for (const auto& [power, coefficient] : this->monomials_) {
        while (other_it != other.monomials_.end() && other_it->power < power) {
            res.monomials_.push_back({other_it->power, other_it->coefficient});
            other_it++;
        }
        if (other_it != other.monomials_.end() && other_it->power == power) {
            if (coefficient - other_it->coefficient) {
                res.monomials_.push_back({power, coefficient - other_it->coefficient});
            }
            other_it++;
        } else {
            res.monomials_.push_back({power, coefficient});
        }
    }
    while (other_it != other.monomials_.end()) {
        res.monomials_.push_back({other_it->power, other_it->coefficient});
        other_it++;
    }

    res.max_power_ = res.monomials_.empty() ? 0 : res.monomials_.back().power;
    return res;
}

const Poly& Poly::operator-=(const Poly& other) {
    return *this = *this - other;
}

Poly Poly::operator*(const Poly& other) const {
    Poly res = Poly();

    std::map<size_t, int64_t> res_mono;
    for (const auto& [power1, coefficient1] : this->monomials_) {
        for (const auto& [power2, coefficient2] : other.monomials_) {
            res_mono[power1 + power2] += coefficient1 * coefficient2;
        }
    }
    for (const auto& [power, coefficient] : res_mono) {
        if (coefficient) {
            res.monomials_.push_back({power, coefficient});
        }
    }

    res.max_power_ = res.monomials_.empty() ? 0 : res.monomials_.back().power;
    return res;
}

const Poly& Poly::operator*=(const Poly& other) {
    return *this = *this * other;
}

/*
void operator>>(std::istream& in, Poly& poly) {
    std::string s;
    // cin >> s;

    std::vector<Poly::Monomial> v;

    std::map<size_t, int64_t> acc;

    int power = 0;
    int coefficient = 0;
    int ok = 0;
    int is_coef_pos = 1;
    for (size_t i = 0; i < s.size(); i++) {
        if (s[i] == 'x') {
            if (!coefficient) {
                coefficient = 1;
            }

            if (i + 1 == s.size()) {
                power = 1;
                break;
            }

            if (i + 1 < s.size() && s[i + 1] == '^') {
                ok = 1;
                i++;
                continue;
            } else if (i + 1 < s.size()) {
                power = 1;
                if (is_coef_pos) {
                    acc[power] += coefficient;
                } else {
                    acc[power] -= coefficient;
                }

                power = 0;
                coefficient = 0;
                is_coef_pos = 1;
                ok = 0;

                continue;
            }
        } else if (s[i] == '+') {
            if (is_coef_pos) {
                acc[power] += coefficient;
            } else {
                acc[power] -= coefficient;
            }
            coefficient = 0;
            is_coef_pos = 1;
            power = 0;
            ok = 0;

            is_coef_pos = 1;
        } else if (s[i] == '-') {
            if (is_coef_pos) {
                acc[power] += coefficient;
            } else {
                acc[power] -= coefficient;
            }
            coefficient = 0;
            is_coef_pos = 1;
            power = 0;
            ok = 0;

            is_coef_pos = 0;
        } else {
            if (ok == 0) {
                coefficient = coefficient * 10 + (s[i] - '0');
            } else {
                power = power * 10 + (s[i] - '0');
            }
        }
    }

    if (coefficient) {
        if (is_coef_pos) {
            acc[power] += coefficient;
        } else {
            acc[power] -= coefficient;
        }
    }

    for (const auto& [pow, coef] : acc) {
        if (coef) {
            v.push_back({pow, coef});
        }
    }

    poly = Poly(v);
}
 */

std::ostream& operator<<(std::ostream& out, const Poly& poly) {
    out << "y = ";
    if (poly.monomials_.empty()) {
        return out << "0";
    } else {
        bool was_first = false;
        for (size_t i = poly.monomials_.size() - 1;; i--) {
            if (!poly.monomials_[i].coefficient) {
                continue;
            }
            if (was_first) {
                if (poly.monomials_[i].coefficient > 0) {
                    out << " + ";
                } else {
                    out << " - ";
                }
            } else {
                if (poly.monomials_[i].coefficient < 0) {
                    out << "-";
                }
                was_first = true;
            }

            if (poly.monomials_[i].power > 0) {
                out << std::abs(poly.monomials_[i].coefficient);
                if (poly.monomials_[i].power == 1) {
                    out << "x";
                } else {
                    out << "x^" << poly.monomials_[i].power;
                }
            } else {
                out << std::abs(poly.monomials_[i].coefficient);
            }
            if (i == 0) {
                break;
            }
        }
        return out;
    }
}
