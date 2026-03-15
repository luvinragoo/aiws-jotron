#pragma once
#include <memory>
#include <vector>
#include "Zone.hpp"

class ZoneMap {
    public:
        void addZone(std::unique_ptr<Zone> zone);
        ZoneType classify(Point p) const;

    private:
    std::vector<std::unique_ptr<Zone>> zones_;
    
};