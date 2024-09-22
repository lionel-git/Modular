#pragma once
#include <cstdint>
#include <ostream>
#include <random>

class number_t
{
public:
    static void init_modulo(int64_t modulo, unsigned int seed);

    number_t() = default;
    number_t(int64_t value) { value_ = normalize(value % modulo_); }
    number_t(const number_t& other) { value_ = other.value_; }
    ~number_t() = default;

    number_t& operator=(const number_t& other) { value_ = other.value_; return *this; }
    number_t operator+(const number_t& other) const;
    number_t operator-(const number_t& other) const;
    number_t operator*(const number_t& other) const;
    number_t operator/(const number_t& other) const;


    bool operator==(const number_t& other) const { return value_ == other.value_; }
    bool operator!=(const number_t& other) const { return value_ != other.value_; }
    bool operator<(const number_t& other) const { return value_ < other.value_; }
    bool operator>(const number_t& other) const { return value_ > other.value_; }
    bool operator<=(const number_t& other) const { return value_ <= other.value_; }
    bool operator>=(const number_t& other) const { return value_ >= other.value_; }

    friend std::ostream& operator<<(std::ostream& os, const number_t& number);

    static int64_t get_modulo() { return modulo_; }

    static number_t get_random_number() { return number_t(distrib_(generator_)); }

private:
    static int64_t modular_mult(int64_t a, int64_t b);
    static int64_t get_inverse(int64_t b);
    static int64_t normalize(int64_t value) { return value < 0 ? value + modulo_ : value; }

    static int64_t modulo_;
    int64_t value_{ 0 }; // should always be in the range [0, modulo_)

    static std::mt19937 generator_;
    static std::uniform_int_distribution<int64_t> distrib_;
};

