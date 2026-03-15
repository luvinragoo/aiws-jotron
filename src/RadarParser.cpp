#include "RadarParser.hpp"
#include "Utils.hpp"
#include <sstream>
#include <iostream>
#include <stdexcept>

std::vector<AircraftPosition> RadarParser::parseLine(const std::string& line){
    std::vector<AircraftPosition> aircraftList;
    std::stringstream ss(line);
    std::string token;

    while (std::getline(ss, token, ' ')){
        if(token.empty()) {
            continue;
        }

        // Find the '(' character
        size_t bracketPos = token.find('(');
        if (bracketPos == std::string::npos){
            std::cerr << "Warning: Invalid Aircraft Data (Missing '('): " << token << std::endl;
            continue;
        }

        std::string idStr = token.substr(0, bracketPos);
        std::string pointStr = token.substr(bracketPos);
        
        try {
            Point p = Utils::parsePoint(pointStr);
            AircraftPosition aircraft{idStr, p};
            aircraftList.push_back(aircraft);
        } catch (const std::invalid_argument& e) {
            std::cerr << "Warning: Skipping invalid aircraft data '" << token << "': " << e.what() << std::endl;
            continue;
        }
    }

    return aircraftList;
}
