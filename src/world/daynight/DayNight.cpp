#include "world/daynight/DayNight.hpp"
#include "world/daynight/DNStars.hpp"
#include "gx/Transform.hpp"
#include "gx/RenderState.hpp"
#include "gx/Draw.hpp"


namespace DayNight {

static DNStars g_stars;


void LoadMap(int32_t zoneID) {
    // TODO
    g_stars.Initialize();
}

void RenderSky() {
    // TODO

    float minX;
    float maxX;
    float minY;
    float maxY;
    float minZ;
    float maxZ;
    GxXformViewport(minX, maxX, minY, maxY, minZ, maxZ);

    // TODO

    GxXformSetViewport(minX, maxX, minY, maxY, 0.99902344f, 1.0f);
    GxRsSet(GxRs_ScissorTest, 1);
    CImVector color { 0xFF000000 };
    GxSceneClear(3, color);

    g_stars.Render();
}

} // namespace DayNight
