#include "point_t.h"

std::ostream& operator<<(std::ostream& os, const point_t& point)
{
    os << "(" << point.x_ << ", " << point.y_ << ")";
    return os;
}
