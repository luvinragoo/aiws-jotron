#include "CircleZone.hpp"

CircleZone::CircleZone(Point center, int radius, ZoneType type)
:  center_{center} , radius_{radius}, type_{type}
{}

bool CircleZone::contains (Point p) const
{
    long long dx = p.x - center_.x;
    long long dy = p.y - center_.y;

    // we use long long in case for very large radius values overflowing the stack, when it is squared.
    long long r2 = static_cast<long long>(radius_) * radius_;
    return (dx*dx + dy*dy) <= r2;
}

ZoneType CircleZone::type() const
{
    return type_;
}