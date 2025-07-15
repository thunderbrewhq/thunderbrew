#include "world/World.hpp"

uint32_t s_newZoneID = 0;
C3Vector s_newPosition;
float s_newFacing = 0.0f;
const char* s_newMapname = nullptr;


int32_t LoadNewWorld(const void* eventData) {
    // TODO
    CWorld::LoadMap(s_newMapname, s_newPosition, s_newZoneID);
    return 1;
}
