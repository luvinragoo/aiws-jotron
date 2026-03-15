#include <iostream>
#include "MapParser.hpp"
#include "RadarParser.hpp"

int main(int argc, char* argv[]) {

    if(argc < 2){
        std::cerr << "Usage: aiws <mapfile.map>\n";
        return 1;
    }
    ZoneMap zoneMap = MapParser::parse(argv[1]);

    std::string line;
    while (std::getline(std::cin, line)){

        if(!line.empty() && line.back() == '\r'){
            line.pop_back();
        }

        std::vector<AircraftPosition> aircraftList = RadarParser::parseLine(line);
        for (const auto& aircraft : aircraftList){
            ZoneType type = zoneMap.classify(aircraft.position);

            std::string typeStr;
            if(type != ZoneType::Normal){
                if (type == ZoneType::Prohibited) {
                    typeStr = "prohibited";

                }else{
                    typeStr = "restricted";
                }

                std::cout << aircraft.id << " is in " 
                          << typeStr << " zone at (" 
                          << aircraft.position.x << "," 
                          << aircraft.position.y << ")" 
                          << "\n";
            }
        }

    }

    return 0;
}
