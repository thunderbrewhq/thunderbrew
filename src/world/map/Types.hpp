#ifndef WORLD_MAP_TYPES_HPP
#define WORLD_MAP_TYPES_HPP

#include <cstdint>
#include <tempest/Vector.hpp>
#include <tempest/Box.hpp>

struct SIffChunk {
    uint32_t token;
    uint32_t size;
};

struct SMMapHeader {
    uint32_t flags;
    uint32_t something;
    uint32_t unused[6];
};

struct SMAreaInfo {
    uint32_t flags;
    uint32_t unused;
};

struct SMMapObjDef {
    uint32_t nameId;
    int32_t uniqueId;
    C3Vector pos;
    C3Vector rot;
    CAaBox extents;
    uint16_t flags;
    uint16_t doodadSet;
    uint16_t nameSet;
    uint16_t pad;
};


#endif
