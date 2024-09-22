#include "number_t.h"
#include <iostream>

void check_inverses(int N)
{
    number_t one = 1;
    for (int i = 0; i < N; ++i)
    {
        number_t a = number_t::get_random_number();
        number_t inverse = one / a;
        number_t result = a * inverse;
        if (result != one)
            throw std::runtime_error("inverse is not correct");
    }
    std::cout << "Test passed for N=" << N << std::endl;
}

void test2()
{
    number_t a = 7345678901234567890ll;
    number_t b = 5765432109876543210ll;
    number_t result = a * b;
    std::cout << "Result: " << result << std::endl;
}

void test3()
{
    number_t a = 7345678901234567890ll;
    a = 15;
    number_t b = 0ll;
    number_t result = a / b;
    std::cout << "Result: " << result << std::endl;
}


int main(int argc, char* argv[]) 
{
    try
    {
        number_t::init_modulo(9223372036854775783ll, 1234);
        test2();
        check_inverses(10000);
        //test3();
        return 0;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}

