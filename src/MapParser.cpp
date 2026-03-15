#include "MapParser.hpp"
#include "RectangleZone.hpp"
#include "CircleZone.hpp"
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>

// forward declarations
static ZoneType parseZoneType(const std::string& token);
static Point parsePoint(const std::string& token);
static int parseRadius(const std::string& token);

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
    
        // Parse data and create Zones
        type = parseZoneType(tokens[0]);
        if (tokens[1]!= "rectangle" && tokens[1] != "circle"){
            std::cerr << "Error : Invalid shape: " << tokens[1] << std::endl;
            std::exit(1);
        }
        shape = tokens[1];

        if (shape == "rectangle"){
            p1 = parsePoint(tokens[3]);
            p2 = parsePoint(tokens[4]);
            // create a rectangle Zone.
            map.addZone(std::make_unique<RectangleZone>(p1,p2,type));
        }else if (shape == "circle"){
            p1 = parsePoint(tokens[3]);
            radius = parseRadius(tokens[4]);
            // create a circle Zone. 
            map.addZone(std::make_unique<CircleZone>(p1,radius,type));
        }
    }

    return map;
}

static Point parsePoint(const std::string& token) {
    Point p{};

    // 1. Remove brackets
    if (token.length() < 3 || token.front() != '(' || token.back() != ')') {
        std::cerr << "Error: Malformed point formatting: " << token << std::endl;
        std::exit(1);
    }
    std::string inner = token.substr(1, token.length() - 2);

    // 2. Split by comma
    size_t commaPos = inner.find(',');
    if (commaPos == std::string::npos) {
        std::cerr << "Error: Missing comma in point: " << token << std::endl;
        std::exit(1);
    }

    std::string xStr = inner.substr(0, commaPos);
    std::string yStr = inner.substr(commaPos + 1);

    // 3. Convert to int safely
    try {
        p.x = std::stoi(xStr);
        p.y = std::stoi(yStr);
    } catch (const std::exception& e) {
        std::cerr << "Error: Coordinate contains invalid characters: " << token << std::endl;
        std::exit(1);
    }

    return p;
}

static int parseRadius(const std::string& token) {
    try {
        int radius = std::stoi(token);
        if (radius <= 0) {
            std::cerr << "Error: Radius must be a positive integer: " << token << std::endl;
            std::exit(1);
        }
        return radius;
    } catch (const std::exception& e) {
        std::cerr << "Error: Invalid radius value: " << token << std::endl;
        std::exit(1);
    }
}

static ZoneType parseZoneType(const std::string& token){
    if(token == "normal") return ZoneType::Normal;
    if(token == "restricted") return ZoneType::Restricted;
    if(token == "prohibited") return ZoneType::Prohibited;

    std::cerr << "Error : Unknown zone type: " << token << std::endl;
    std::exit(1);

}


