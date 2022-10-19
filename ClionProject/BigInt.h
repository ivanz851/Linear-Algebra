#include <vector>
#include <sstream>

// https://e-maxx.ru/algo/big_integer
// https://acmp.ru/article.asp?id_text=1329
// https://acmp.ru/asp/do/index.asp?main=task&id_course=5&id_section=29&id_topic=153&id_problem=957
// https://www.eolymp.com/en/problems/3658

static const int64_t BASE = 1000 * 1000 * 1000;

class BigInt {
public:
    BigInt();
    BigInt(bool is_positive, std::vector<int64_t> digits);
    explicit BigInt(int64_t x);

    explicit operator bool() const;

    bool operator==(const BigInt& other) const;
    // bool operator==(const int64_t& other) const;

    bool operator<(const BigInt& other) const;
    bool operator<(const int64_t& other) const;
    bool operator>(const BigInt& other) const;
    bool operator>(const int64_t& other) const;

    BigInt operator+(const BigInt& other) const;
    const BigInt& operator+=(const BigInt& other);

    BigInt operator-() const;
    BigInt operator-(const BigInt& other) const;
    const BigInt& operator-=(const BigInt& other);

    BigInt operator*(const BigInt& other) const;
    const BigInt& operator*=(const BigInt& other);

    friend std::istream& operator>>(std::istream& in, BigInt& a);
    friend std::ostream& operator<<(std::ostream& out, const BigInt& a);

    static BigInt Abs(const BigInt& a);
    static int64_t ToInt(const BigInt& a);

private:
    // 0 is positive, 0 has empty digits_
    bool is_positive_;
    std::vector<int64_t> digits_;

    static std::string ToNineSymbols(int64_t x);
    bool IsZero(const BigInt& a) const;
};

