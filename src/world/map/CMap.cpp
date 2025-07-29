#include "world/map/CMap.hpp"
#include "world/daynight/DayNight.hpp"
#include "util/SFile.hpp"
#include <storm/Error.hpp>



char CMap::mapPath[STORM_MAX_PATH];
char CMap::mapName[STORM_MAX_PATH];
char CMap::wdtFilename[STORM_MAX_PATH];
uint32_t CMap::version;
SMMapHeader CMap::header;
SMAreaInfo CMap::areaInfo[64 * 64];
uint32_t CMap::uniqueId;
int32_t CMap::bDungeon;


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
