#include <iostream>
#include <cstdint>
#include <cstdlib>
#include <random>

#ifdef _WIN32
uint64_t modular_mult(uint64_t a, uint64_t b, uint64_t n)
{
    uint64_t high;
    uint64_t low = _umul128(a, b, &high);
    uint64_t remainder;
    uint64_t q = _udiv128(high, low, n, &remainder);
    return remainder;
}
#else
uint64_t modular_mult(uint64_t a, uint64_t b, uint64_t n)
{
    return (uint64_t)(((__uint128_t)a * (__uint128_t)b) % n);
}
#endif

uint64_t get_inverse(int64_t b, int64_t modulo)
{
    int64_t r0 = modulo;
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
    {
        if (t0 < 0)
            t0 += modulo;
        return t0;
    }
    else
        throw std::runtime_error("gcd is not one");
}

void check_inverse(int64_t a, int64_t modulo)
{
    int64_t inverse = get_inverse(a, modulo);
    int64_t result = modular_mult(a, inverse, modulo);
    if (result != 1)
        throw std::runtime_error("inverse is not correct");
}

void check_inverses(int64_t modulo, int N)
{
    std::mt19937 generator(1234);
    std::uniform_int_distribution<int64_t> distrib(0, modulo - 1);

    std::cout << "min: " << distrib.min() << std::endl;
    std::cout << "max: " << distrib.max() << std::endl;

    for (int i = 0; i < N; ++i)
    {
        int64_t a = distrib(generator);
        check_inverse(a, modulo);
    }
    std::cout << "Test passed" << std::endl;
}

void test0()
{
    int64_t m = 9223372036854775783ll;
    int64_t a = 7345678901234567890ll % m;
    int64_t b = 5765432109876543210ll % m;
    int64_t result = modular_mult(a, b, m);
    std::cout << "Result: " << result << std::endl;

    check_inverses(m, 10000);
}

int main(int argc, char* argv[]) 
{
    test0();
    return 0;
}

