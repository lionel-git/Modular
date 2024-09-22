#include "elliptic_curve.h"

elliptic_curve::elliptic_curve(number_t a, number_t b) : a_(a), b_(b)
{
    number_t discrimant = (number_t)4 * a * a * a + (number_t)27 * b * b; // 4a^3 + 27b^2
    if (discrimant == 0)    
        throw std::runtime_error("Invalid curve parameters (discrimant = 0)");
    if (b == 0)
        throw std::runtime_error("Invalid curve parameters (b = 0)");
}

bool
elliptic_curve::is_point_on_curve(const point_t& p) const
{
    auto y2 = p.y_ * p.y_;
    auto value = b_ + p.x_ * (a_ + p.x_ * p.x_); // y^2 = x^3 + ax + b
    return y2 == value || is_infinite_point(p);
}

point_t 
elliptic_curve::negate_point(const point_t& p)
{
    return point_t(p.x_, -p.y_);
}

point_t
elliptic_curve::add_point(const point_t& p, const point_t& q) const
{
    if (is_infinite_point(p))
        return q;
    if (is_infinite_point(q))
        return p;
    if (p.x_ == q.x_)
    {
        if (p.y_ == q.y_)
            return double_point(p);
        else
            return infinite_point();
    }
    // Droite y = s.x + t passe par p et q, intersection avec la courbe en r, on doit renvoyer le point -r
    number_t s = (q.y_ - p.y_) / (q.x_ - p.x_); // PQy/PQx
    number_t xr = s * s - (p.x_ + q.x_);
    number_t yr = s * (p.x_ - xr) - p.y_; // PRy/PRx = s
    return point_t(xr, yr);
}

point_t
elliptic_curve::double_point(const point_t& p) const
{
    if (p.y_ == 0)
        return infinite_point();
    number_t p2x = p.x_ * p.x_;
    number_t s = (p2x + p2x + p2x + a_) / (p.y_ + p.y_); // (3*p.x^2 + a) / (2*p.y), differentielle de y^2 = x^3 + ax + b en P
    number_t xr = s * s - (p.x_ + p.x_);
    number_t yr = s * (p.x_ - xr) - p.y_; // PRy/PRx = s
    return point_t(xr, yr);
}

point_t
elliptic_curve::multiply_point(const point_t& p, int64_t k) const
{
    if (k == 0)
        return infinite_point();
    bool negate = false;
    if (k < 0)
    {
        negate = true;
        k = -k;
    }
    uint64_t target = k; // Rem: target >=1
    uint64_t mask = 1;
    while (mask <= target)
        mask <<= 1;
    mask >>= 2;
    point_t result = p;
    while (mask != 0)
    {
        result = double_point(result);
        if (target & mask)
            result = add_point(result, p);
        mask >>= 1;
    }
    if (negate)
        result = negate_point(result);
    return result;
}
