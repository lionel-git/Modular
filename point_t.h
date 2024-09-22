#pragma once

#include "number_t.h"

class point_t
{
public:
    point_t() = default;
    point_t(number_t x, number_t y) : x_(x), y_(y) {}
    ~point_t() = default;

    bool operator==(const point_t& other) const { return x_ == other.x_ && y_ == other.y_; }
    bool operator!=(const point_t& other) const { return !(*this == other); }

    friend std::ostream& operator<<(std::ostream& os, const point_t& point);

    number_t x_{ 0 };
    number_t y_{ 0 };
};
