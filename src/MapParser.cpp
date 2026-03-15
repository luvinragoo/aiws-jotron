#include "MapParser.hpp"
#include "RectangleZone.hpp"
#include "CircleZone.hpp"
#include "Utils.hpp"
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <stdexcept>

ZoneMap MapParser::parse(const std::string& filePath){

    ZoneMap map;
    // 1. Opens file.
    std::ifstream file(filePath);

    if(!file.is_open()){
        std::cerr << "Error: cannot open map file: " << filePath << std::endl;
        std::exit(1);
    }

    std::string line;
    while (std::getline(file, line)){
        // Remove trailing \r if present (Windows line endings)
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }

        // skip empty lines
        if (line.empty()){
            continue;
        }

        // defining line variables
        ZoneType type = ZoneType::Normal;
        std::string shape;
        Point p1{},p2{};
        int radius=0;

        std::vector<std::string> tokens;
        std::string word;
        std::stringstream ss(line);
        while (std::getline(ss, word, ' ')){
            // skip empty words
            if (word.empty()){
                continue;
            }
            tokens.push_back(word);
        }

        // first check if tokens is in correct format
        if(tokens.size() < 5){
            std::cerr << "Error : Invalid data!\n"; 
            std::exit(1);
        }
    
        try {
            // Parse data and create Zones
            type = Utils::parseZoneType(tokens[0]);
            if (tokens[1]!= "rectangle" && tokens[1] != "circle"){
                std::cerr << "Error : Invalid shape: " << tokens[1] << std::endl;
                std::exit(1);
            }
            shape = tokens[1];

            if (shape == "rectangle"){
                p1 = Utils::parsePoint(tokens[3]);
                p2 = Utils::parsePoint(tokens[4]);
                // create a rectangle Zone.
                map.addZone(std::make_unique<RectangleZone>(p1,p2,type));
            }else if (shape == "circle"){
                p1 = Utils::parsePoint(tokens[3]);
                radius = Utils::parseRadius(tokens[4]);
                // create a circle Zone. 
                map.addZone(std::make_unique<CircleZone>(p1,radius,type));
            }
        } catch (const std::invalid_argument& e) {
            std::cerr << "Error parsing map: " << e.what() << std::endl;
            std::exit(1);
        }
    }

    return map;
}
