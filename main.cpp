#include "number_t.h"
#include "elliptic_curve.h"
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

void test4()
{
    elliptic_curve ec(17, 22);

    point_t p(2, 8);
    point_t q(3, 10);
    point_t w(7, 22);
    point_t z(-1, 2);
    std::cout  << ec.is_point_on_curve(p) << std::endl;
    std::cout << ec.is_point_on_curve(q) << std::endl;
    std::cout << ec.is_point_on_curve(w) << std::endl;
    std::cout << ec.is_point_on_curve(z) << std::endl;

    point_t r1 = ec.add_point(p, q);
    point_t r2 = ec.double_point(p);
    std::cout << "Result: " << r1 << " " << r2 << std::endl;

    std::cout << ec.is_point_on_curve(r1) << std::endl;
    std::cout << ec.is_point_on_curve(r2) << std::endl;
}

void test5()
{
    elliptic_curve ec(17, 22);

    point_t p(2, 8);
    point_t q = ec.negate_point(p);

    std::cout << ec.is_point_on_curve(p) << std::endl; // P
    std::cout << ec.is_point_on_curve(q) << std::endl; // -P


    point_t inf_point = ec.add_point(p, q);
    std::cout << "Result: " << inf_point << std::endl;

    std::cout << ec.is_point_on_curve(inf_point) << std::endl;

    point_t r2 = ec.add_point(inf_point, p);
    std::cout << "Result: " << r2 << std::endl;

}

void test6()
{
    elliptic_curve ec(17, 22);

    point_t p(2, 8);
    point_t sum = ec.infinite_point();
    point_t sum_neg = ec.infinite_point();
    point_t q = ec.negate_point(p);

    for (int i = 0; i < 25; ++i)
    {        
        std::cout << "p: " << i << " = " << sum << std::endl;

        point_t pi = ec.multiply_point(p, i);
        if (sum != pi)
            throw std::runtime_error("error");

        point_t qi = ec.multiply_point(p, -i);
        if (sum_neg != qi)
            throw std::runtime_error("error");

        sum = ec.add_point(sum, p);
        sum_neg = ec.add_point(sum_neg, q);
    }
}

int main(int argc, char* argv[]) 
{
    try
    {
        number_t::init_modulo(9223372036854775783ll, 1234);
        test2();
        check_inverses(10000);
        //test3();
        //test4();
        test5();
        test6();
        return 0;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}

