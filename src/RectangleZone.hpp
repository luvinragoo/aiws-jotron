#pragma once
#include "Zone.hpp"

class RectangleZone : public Zone{

    public:
    RectangleZone(Point a, Point b, ZoneType type);
    bool contains(Point p) const override;
    ZoneType type() const override;

    private:
    Point p1_,p2_;
    ZoneType type_;

};