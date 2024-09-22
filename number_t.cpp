#include "number_t.h"
#include <stdexcept>
#include <cstdint>
#include <cstdlib>
#include <format>


int64_t number_t::modulo_ = 0;
std::mt19937 number_t::generator_;
std::uniform_int_distribution<int64_t> number_t::distrib_;

void 
number_t::init_modulo(int64_t modulo, unsigned int seed)
{
    if (modulo <= 0)
        throw std::runtime_error("modulo should be positive");
    modulo_ = modulo;
    number_t::generator_.seed(seed);
    number_t::distrib_ = std::uniform_int_distribution<int64_t>(0, modulo - 1);
}

#ifdef _WIN32
int64_t 
number_t::modular_mult(int64_t a, int64_t b)
{
    uint64_t high;
    uint64_t low = _umul128(a, b, &high);
    uint64_t remainder;
    uint64_t q = _udiv128(high, low, number_t::modulo_, &remainder);
    return remainder;
}
#else
int64_t
number_t::modular_mult(int64_t a, int64_t b)
{
    return (int64_t)(((__uint128_t)a * (__uint128_t)b) % number_t::modulo_);
}
#endif

int64_t 
number_t::get_inverse(int64_t b)
{
    int64_t r0 = number_t::modulo_;
    int64_t r1 = b;
    int64_t s0 = 1;
    int64_t s1 = 0;
    int64_t t0 = 0;
    int64_t t1 = 1;

    while (r1 != 0)
    {
        auto qr = std::div(r0, r1);
        r0 = r1;
        r1 = qr.rem;
        int64_t s2 = s0 - qr.quot * s1;
        s0 = s1;
        s1 = s2;
        int64_t t2 = t0 - qr.quot * t1;
        t0 = t1;
        t1 = t2;
    }
    if (r0 == 1)
        return normalize(t0);
    else
        throw std::runtime_error(std::format("gcd is not one, divider={}", b));
}

number_t 
number_t::operator+(const number_t& other) const
{
    uint64_t result = (uint64_t)value_ + (uint64_t)other.value_;
    return number_t(result % modulo_);
}

number_t 
number_t::operator-(const number_t& other) const
{
    uint64_t result = (uint64_t)value_ + (uint64_t)(modulo_- other.value_);
    return number_t(result % modulo_);
}

number_t number_t::operator-() const
{
    return number_t(modulo_ - value_);
}

number_t 
number_t::operator*(const number_t& other) const
{
    return number_t(modular_mult(value_, other.value_));
}

number_t 
number_t::operator/(const number_t& other) const
{
    return number_t(modular_mult(value_, get_inverse(other.value_)));
}

std::ostream& operator<<(std::ostream& os, const number_t& number)
{
    os << number.value_;
    return os;
}
