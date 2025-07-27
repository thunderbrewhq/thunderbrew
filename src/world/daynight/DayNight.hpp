#ifndef WORLD_DAY_NIGHT_HPP
#define WORLD_DAY_NIGHT_HPP

#include <cstdint>

class C2Vector;

namespace DayNight {

class DNInfo;

float InterpTable(const C2Vector* table, uint32_t size, float key);
void LoadMap(int32_t zoneID);
void Update();
void RenderSky();
DNInfo* GetInfo();

} // namespace DayNight

#endif
