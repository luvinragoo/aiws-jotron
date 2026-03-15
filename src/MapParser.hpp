#pragma once
#include <string>
#include "ZoneMap.hpp"

class MapParser {
    public:
        static ZoneMap parse(const std::string& filePath);
};