#include "ZoneMap.hpp"

void ZoneMap::addZone(std::unique_ptr<Zone> zone)
{
    zones_.push_back(std::move(zone));
}

ZoneType ZoneMap::classify(Point p) const
{
    for (auto it = zones_.rbegin(); it != zones_.rend(); ++it){
        if((*it)->contains(p)){
            return (*it)->type();
        }
    }
    return ZoneType::Normal;
}