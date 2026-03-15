#pragma once
#include <string>
#include "Zone.hpp"

namespace Utils {
    Point parsePoint(const std::string& token);
    int parseRadius(const std::string& token);
    ZoneType parseZoneType(const std::string& token);
}

