#include "world/daynight/DayNight.hpp"
#include "world/daynight/DNStars.hpp"


namespace DayNight {

static DNStars g_stars;


void LoadMap(int32_t zoneID) {
    // TODO
    g_stars.Initialize();
}

void RenderSky() {
    // TODO
    g_stars.Render();
}

} // namespace DayNight
