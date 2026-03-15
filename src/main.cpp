#include <iostream>
#include "MapParser.hpp"

int main(int argc, char* argv[]) {

    if(argc < 2){
        std::cerr << "Usage: aiws <mapfile.map>\n";
        return 1;
    }
    ZoneMap zoneMap = MapParser::parse(argv[1]);

    return 0;
}
