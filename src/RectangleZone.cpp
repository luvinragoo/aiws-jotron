#include "RectangleZone.hpp"
#include <algorithm>

RectangleZone::RectangleZone(Point a, Point b, ZoneType type)
: p1_{ std::min(a.x, b.x), std::min(a.y, b.y) },
  p2_{ std::max(a.x, b.x), std::max(a.y, b.y) },
  type_{ type }
{} 

bool RectangleZone::contains (Point p) const
{
    bool checkX = p.x >= p1_.x && p.x <= p2_.x;
    bool checkY = p.y >= p1_.y && p.y <= p2_.y;

    return checkX && checkY;
}

ZoneType RectangleZone::type() const
{
    return type_;
}
