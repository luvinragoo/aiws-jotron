#pragma once

struct Point{
    int x;
    int y;
};

enum class ZoneType {Normal, Restricted, Prohibited};

class Zone{
    public:
        virtual ~Zone() = default;
        virtual bool contains(Point p) const = 0;
        virtual ZoneType type() const = 0;
};