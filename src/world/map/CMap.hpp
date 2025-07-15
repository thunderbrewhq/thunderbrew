#ifndef WORLD_C_MAP_HPP
#define WORLD_C_MAP_HPP

#include <cstdint>

class CMap {
    public:
    static void Load(const char* mapName, int32_t zoneID);
};

#endif
