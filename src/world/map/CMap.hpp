#ifndef WORLD_C_MAP_HPP
#define WORLD_C_MAP_HPP

#include "world/map/Types.hpp"
#include <storm/String.hpp>

class CMap {
    public:
    static char mapPath[STORM_MAX_PATH];
    static char mapName[STORM_MAX_PATH];
    static char wdtFilename[STORM_MAX_PATH];
    static uint32_t version;
    static SMMapHeader header;
    static SMAreaInfo areaInfo[64 * 64];
    static uint32_t uniqueId;
    static int32_t bDungeon;


    static void Load(const char* mapName, int32_t zoneID);
    static void LoadWdt();
    static void LoadTextureBlob();
};

#endif
