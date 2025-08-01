#include "world/map/CMap.hpp"
#include "world/daynight/DayNight.hpp"
#include "util/SFile.hpp"
#include <storm/Error.hpp>
#include <common/ObjectAlloc.hpp>
#include <common/Processor.hpp>

#include <cstring>



char CMap::mapPath[STORM_MAX_PATH];
char CMap::mapName[STORM_MAX_PATH];
char CMap::wdtFilename[STORM_MAX_PATH];
uint32_t CMap::version;
SMMapHeader CMap::header;
SMAreaInfo CMap::areaInfo[64 * 64];
int32_t CMap::uniqueId;
int32_t CMap::bDungeon;
int32_t CMap::counts[11];
int32_t CMap::freeCounts[11];
TSGrowableArray<uint32_t> CMap::scCollideList;
uint32_t CMap::scCollideCnt;
uint32_t CMap::cCount;

uint32_t* CMap::lightHeap;
uint32_t* CMap::cacheLightHeap;
uint32_t* CMap::mapObjGroupHeap;
uint32_t* CMap::mapObjHeap;
uint32_t* CMap::baseObjLinkHeap;
uint32_t* CMap::areaHeap;
uint32_t* CMap::areaMedHeap;
uint32_t* CMap::areaLowHeap;
uint32_t* CMap::chunkHeap;
uint32_t* CMap::doodadDefHeap;
uint32_t* CMap::entityHeap;
uint32_t* CMap::mapObjDefGroupHeap;
uint32_t* CMap::mapObjDefHeap;
uint32_t* CMap::chunkLiquidHeap;



void CMap::Initialize() {
    // TODO
    memset(&CMap::counts, 0, sizeof(CMap::counts));
    memset(&CMap::freeCounts, 0, sizeof(CMap::freeCounts));
    memset(&CMap::areaInfo, 0, sizeof(CMap::areaInfo));
    CMap::scCollideList.SetCount(2048);
    CMap::scCollideCnt = 0;
    CMap::cCount = 0;
    CMap::uniqueId = -2;
    CMap::bDungeon = 0;

    // TODO

    // CMap::MapMemInitialize();
}

void CMap::MapMemInitialize() {
    CMap::lightHeap = NEW(uint32_t);
    *CMap::lightHeap = ObjectAllocAddHeap(212, 128, "WLIGHT", true);

    CMap::cacheLightHeap = NEW(uint32_t);
    *CMap::cacheLightHeap = ObjectAllocAddHeap(132, 256, "WCACHELIGHT", true);

    CMap::mapObjGroupHeap = NEW(uint32_t);
    *CMap::mapObjGroupHeap = ObjectAllocAddHeap(444, 128, "WMAPOBJGROUP", true);

    CMap::mapObjHeap = NEW(uint32_t);
    *CMap::mapObjHeap = ObjectAllocAddHeap(2552, 32, "WMAPOBJ", true);

    CMap::baseObjLinkHeap = NEW(uint32_t);
    *CMap::baseObjLinkHeap = ObjectAllocAddHeap(28, 10000, "WBASEOBJLINK", true);

    CMap::areaHeap = NEW(uint32_t);
    *CMap::areaHeap = ObjectAllocAddHeap(1212, 16, "WAREA", true);

    CMap::areaMedHeap = NEW(uint32_t);
    *CMap::areaMedHeap = ObjectAllocAddHeap(33404, 16, "WAREAMED", true);

    CMap::areaLowHeap = NEW(uint32_t);
    *CMap::areaLowHeap = ObjectAllocAddHeap(92, 16, "WAREALOW", true);

    CMap::chunkHeap = NEW(uint32_t);
    *CMap::chunkHeap = ObjectAllocAddHeap(344, 256, "WCHUNK", true);

    CMap::doodadDefHeap = NEW(uint32_t);
    *CMap::doodadDefHeap = ObjectAllocAddHeap(368, 5000, "WDOODADDEF", true);

    CMap::entityHeap = NEW(uint32_t);
    *CMap::entityHeap = ObjectAllocAddHeap(208, 128, "WENTITY", true);

    CMap::mapObjDefGroupHeap = NEW(uint32_t);
    *CMap::mapObjDefGroupHeap = ObjectAllocAddHeap(192, 128, "WMAPOBJDEFGROUP", true);

    CMap::mapObjDefHeap = NEW(uint32_t);
    *CMap::mapObjDefHeap = ObjectAllocAddHeap(344, 64, "WMAPOBJDEF", true);

    CMap::chunkLiquidHeap = NEW(uint32_t);
    *CMap::chunkLiquidHeap = ObjectAllocAddHeap(1092, 64, "WCHUNKLIQUID", true);

    int32_t vendor;
    if (OsGetProcessorFeaturesEx(vendor) & 4) {
        // TODO: dword_CF08F8 = 1;
    }
}

void CMap::Load(const char* mapName, int32_t zoneID) {
    // TODO
    auto length = SStrCopy(CMap::mapPath, "World\\Maps\\", STORM_MAX_STR);
    SStrCopy(&CMap::mapPath[length], mapName, STORM_MAX_STR);
    SStrCopy(CMap::mapName, mapName, STORM_MAX_STR);
    SStrPrintf(CMap::wdtFilename, 0x100u, "%s\\%s.wdt", CMap::mapPath, CMap::mapName);

    // TODO: create sunLight

    // TODO

    CMap::LoadWdt();
    CMap::LoadTextureBlob();
    DayNight::LoadMap(zoneID);

    // TODO
}

void CMap::LoadWdt() {
    SFile* file = nullptr;
    if (!SFile::Open(CMap::wdtFilename, &file) || !file) {
        SErrDisplayAppFatal("CMap::LoadWdt() failed %s\n", CMap::wdtFilename);
    }

    SIffChunk iffChunk = {};

    SFile::Read(file, &iffChunk, sizeof(iffChunk), nullptr, nullptr, nullptr);
    STORM_ASSERT(iffChunk.token == 'MVER' && iffChunk.size == sizeof(CMap::version));
    SFile::Read(file, &CMap::version, sizeof(CMap::version), nullptr, nullptr, nullptr);

    SFile::Read(file, &iffChunk, sizeof(iffChunk), nullptr, nullptr, nullptr);
    STORM_ASSERT(iffChunk.token == 'MPHD' && iffChunk.size == sizeof(CMap::header));
    SFile::Read(file, &CMap::header, sizeof(CMap::header), nullptr, nullptr, nullptr);

    SFile::Read(file, &iffChunk, sizeof(iffChunk), nullptr, nullptr, nullptr);
    STORM_ASSERT(iffChunk.token == 'MAIN' && iffChunk.size == sizeof(CMap::areaInfo));
    SFile::Read(file, &CMap::areaInfo, sizeof(CMap::areaInfo), nullptr, nullptr, nullptr);

    // wdt_uses_global_map_obj
    if (CMap::header.flags & 1) {
        char globalWmoName[256];
        SFile::Read(file, &iffChunk, sizeof(iffChunk), nullptr, nullptr, nullptr);
        STORM_ASSERT(iffChunk.token == 'MWMO' && iffChunk.size <= 256);
        SFile::Read(file, globalWmoName, iffChunk.size, nullptr, nullptr, nullptr);

        SFile::Read(file, &iffChunk, sizeof(iffChunk), nullptr, nullptr, nullptr);
        if (iffChunk.token == 'MODF') {
            SMMapObjDef globalMapObjDef = {};
            SFile::Read(file, &globalMapObjDef, sizeof(globalMapObjDef), nullptr, nullptr, nullptr);
            globalMapObjDef.uniqueId = CMap::uniqueId--;

            // TODO
        }
        CMap::bDungeon = 1;
    }

    if (CMap::header.flags & 2) {
        // TODO: sub_7B7330(2);
    } else {
        // TODO: sub_7B7330(1);
    }

    // sub_7BD8A0();

    SFile::Close(file);
}

void CMap::LoadTextureBlob() {
    char path[STORM_MAX_PATH];
    SStrCopy(path, CMap::wdtFilename, STORM_MAX_STR);
    char* suffix = SStrChrR(path, '.');
    SStrCopy(suffix, ".tex", STORM_MAX_STR);
    // TODO: TextureLoadBlob(path);
}
