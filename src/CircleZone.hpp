#pragma once
#include "Zone.hpp"

class CircleZone : public Zone
{
    public :
    CircleZone(Point center, int radius, ZoneType type);
    bool contains(Point p) const override;
    ZoneType type() const override;

    private:
    Point center_; 
    int radius_; 
    ZoneType type_;

};