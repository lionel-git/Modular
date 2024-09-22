#pragma once
#include "number_t.h"
#include "point_t.h"

// Y^2 = X^3 + aX + b (mod p)
// 4a^3 + 27b^2 != 0 (mod p)
// b!=0 (mod p)
// infinite point is (0, 0)
class elliptic_curve
{
public:
    elliptic_curve(number_t a, number_t b);

    bool is_point_on_curve(const point_t& p) const;

    point_t add_point(const point_t& p, const point_t& q) const;
    point_t double_point(const point_t& p) const;
    point_t multiply_point(const point_t& p, int64_t k) const;

    static point_t negate_point(const point_t& p);

    static point_t infinite_point() { return point_t(0, 0); }
    static bool is_infinite_point(const point_t& p) { return p.x_ == 0 && p.y_ == 0; }

private:

    number_t a_;
    number_t b_;
};

