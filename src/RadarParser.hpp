#pragma once
#include <string>
#include <vector>
#include "Zone.hpp"
#include "AircraftPosition.hpp"

class RadarParser {
    public:
    static std::vector<AircraftPosition> parseLine(const std::string& line); 
};