#ifndef WORLD_C_MAP_HPP
#define WORLD_C_MAP_HPP

#include "world/map/Types.hpp"
#include <storm/String.hpp>
#include <storm/Array.hpp>

class CMap {
    public:
    static char mapPath[STORM_MAX_PATH];
    static char mapName[STORM_MAX_PATH];
    static char wdtFilename[STORM_MAX_PATH];
    static uint32_t version;
    static SMMapHeader header;
    static SMAreaInfo areaInfo[64 * 64];
    static int32_t uniqueId;
    static int32_t bDungeon;
    static int32_t counts[11];
    static int32_t freeCounts[11];
    static TSGrowableArray<uint32_t> scCollideList;
    static uint32_t scCollideCnt;
    static uint32_t cCount;

    static uint32_t* lightHeap;
    static uint32_t* cacheLightHeap;
    static uint32_t* mapObjGroupHeap;
    static uint32_t* mapObjHeap;
    static uint32_t* baseObjLinkHeap;
    static uint32_t* areaHeap;
    static uint32_t* areaMedHeap;
    static uint32_t* areaLowHeap;
    static uint32_t* chunkHeap;
    static uint32_t* doodadDefHeap;
    static uint32_t* entityHeap;
    static uint32_t* mapObjDefGroupHeap;
    static uint32_t* mapObjDefHeap;
    static uint32_t* chunkLiquidHeap;


    static void Initialize();
    static void MapMemInitialize();
    static void Load(const char* mapName, int32_t zoneID);
    static void LoadWdt();
    static void LoadTextureBlob();
};

#endif
