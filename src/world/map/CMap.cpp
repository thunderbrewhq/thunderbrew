#include "world/map/CMap.hpp"
#include "world/daynight/DayNight.hpp"


void CMap::Load(const char* mapName, int32_t zoneID) {
    DayNight::LoadMap(zoneID);
}
