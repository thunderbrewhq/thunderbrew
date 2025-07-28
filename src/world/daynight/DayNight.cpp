#include "world/daynight/DayNight.hpp"
#include "world/daynight/DNInfo.hpp"
#include "world/daynight/DNStars.hpp"
#include "world/daynight/DNSky.hpp"
#include "gx/Transform.hpp"
#include "gx/RenderState.hpp"
#include "gx/Draw.hpp"
#include "storm/Error.hpp"


namespace DayNight {

static DNInfo g_dnInfo;
static DNStars g_stars;
static DNSky g_sky;


float InterpTable(const C2Vector* table, uint32_t size, float key) {
    STORM_ASSERT(size);

    uint32_t i = 0;
    uint32_t j = 0;

    for (i = 0; i < size; ++i) {
        if (key <= table[i].x) {
            break;
        }
    }

    if (i == size) {
        i = 0;
        j = size - 1;
    } else if (i > 0) {
        j = i - 1;
    } else {
        j = size - 1;
    }

    float v5 = table[i].x - table[j].x;
    if (v5 < 0.0) {
        v5 = v5 + 1.0;
    }

    float v6 = key - table[j].x;
    if (v6 < 0.0) {
        v6 = v6 + 1.0;
    }

    float v7 = v6 / v5;

    if (table[i].y < table[j].y) {
        return table[j].y - v7 * (table[j].y - table[i].y);
    } else {
        return table[j].y + v7 * (table[i].y - table[j].y);
    }
}

void LoadMap(int32_t zoneID) {
    // TODO
    g_sky.GenSphere(1.0f);
    g_stars.Initialize();
}

void SetColors() {
    // TODO
    g_sky.SetColors();
}

void UpdateLighting() {
    // TODO
    SetColors();
}

void Update() {
    // TODO
    UpdateLighting();
    g_stars.Update();
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
    CImVector clearColor = { 124, 125, 61, 0xFF };
    GxSceneClear(3, clearColor);

    g_stars.Render();
    g_sky.Render();
}

DNInfo* GetInfo() {
    return &g_dnInfo;
}

} // namespace DayNight
