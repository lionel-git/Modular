#include <iostream>
#include <cstdint>

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

int main(int argc, char* argv[]) 
{
    uint64_t modulo = 18446744073709551557ull;
    uint64_t a = 12345678901234567890ull;
    uint64_t b = 15765432109876543210ull;
    uint64_t result = modular_mult(a, b, modulo);
    std::cout << "Result: " << result << std::endl;
    return 0;
}

