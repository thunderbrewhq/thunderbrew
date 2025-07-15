#ifndef WORLD_WORLD_HPP
#define WORLD_WORLD_HPP

#include "world/CWorld.hpp"

extern uint32_t s_newZoneID;
extern C3Vector s_newPosition;
extern float s_newFacing;
extern const char* s_newMapname;

int32_t LoadNewWorld(const void* eventData);

#endif
