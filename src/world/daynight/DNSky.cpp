#include "world/daynight/DNSky.hpp"
#include "gx/Device.hpp"
#include "gx/Transform.hpp"
#include "gx/RenderState.hpp"
#include "gx/Draw.hpp"
#include <tempest/Math.hpp>
#include <tempest/Matrix.hpp>

namespace DayNight {

float DNSky::m_stripSizes[SKY_NUMBANDS] = { 0.0f, 0.17f, 0.2f, 0.23f, 0.23999999f, 0.25f, 1.0f };
float DNSky::m_fadeAngle[SKY_NUMBANDS];
float DNSky::m_darkAngle[SKY_NUMBANDS];

void DNSky::Render() {
    C44Matrix worldScale;
    worldScale.Scale(6.6666665f);
    GxXformPush(GxXform_World, worldScale);
    GxRsPush();
    GxRsSet(GxRs_Lighting, 0);
    GxRsSet(GxRs_Fog, 0);
    GxRsSet(GxRs_Culling, 0);
    GxRsSet(GxRs_DepthWrite, 0);
    GxRsSet(GxRs_BlendingMode, GxBlend_Add);
    GxRsSetAlphaRef();
    GxPrimVertexPtr(
        this->m_nVerts, this->m_geoVerts.Ptr(), 12,
        nullptr, 0,
        this->m_clrVerts.Ptr(), 4,
        nullptr, 0,
        nullptr, 0);
    GxDrawLockedElements(GxPrim_TriangleStrip, this->m_nIndices, this->m_indices.Ptr());
    GxXformPop(GxXform_World);
    GxRsPop();
}

void DNSky::GenSphere(float sphRadius) {
    const int32_t geoSize = 24;
    const int32_t idxSize = 25 * 2;

    this->m_sphThetaTess = geoSize;
    this->m_geoVerts.SetCount(SKY_NUMBANDS * geoSize); // 168
    this->m_clrVerts.SetCount(SKY_NUMBANDS * geoSize); // 168
    this->m_indices.SetCount(idxSize * (SKY_NUMBANDS - 1)); // 300

    uint16_t lastGeoIndex = 0;
    uint16_t lastIndex = 0;

    for (int32_t i = 0; i < SKY_NUMBANDS; ++i) {
        float phi = DNSky::m_stripSizes[i] * CMath::PI;

        float v10 = 0.31830987f * phi;
        int64_t v11 = static_cast<int64_t>(v10);
        if (v10 <= 0.0f) {
            v11 -= 1;
        }

        float v12 = 1.0f - (v10 - v11) * ((6.0f - (v10 - v11) * 4.0f) * (v10 - v11));
        if (v11 & 1) {
            v12 = -v12;
        }

        float v13 = 0.31830987f * phi - 0.5f;
        int64_t v14 = static_cast<int64_t>(v13);
        if (v13 <= 0.0f) {
            v14 -= 1;
        }

        float v16 = 1.0f - (6.0f - 4.0f * (v13 - v14)) * (v13 - v14) * (v13 - v14);
        if (v14 & 1) {
            v16 = -v16;
        }

        for (int32_t j = 0; j < geoSize; ++j) {
            auto& vertex = this->m_geoVerts[lastGeoIndex++];

            float v19 = static_cast<float>(j) * 0.041666668f * 6.2831855f;
            vertex.x = CMath::sinf(v19) * v16 * sphRadius;
            vertex.y = v16 * CMath::cosf(v19) * sphRadius0;
            vertex.z = sphRadius * v12 - CMath::cosf(0.7853981852531433f);

            if (CMath::fequal(phi, 0.0f) || CMath::fequal(phi, CMath::PI)) {
                break;
            }
        }

        if (i > 0) {
            for (uint16_t k = 0; k < 25; ++k) {
                uint16_t idx1 = CMath::fequal(phi, 0.0f) ? 0 : (k % 24);
                uint16_t idx2 = CMath::fequal(phi, CMath::PI) ? 0 : (k % 24);
                this->m_indices[lastIndex++] = idx1 + lastGeoIndex;
                this->m_indices[lastIndex++] = idx2 + lastGeoIndex;
            }
        }
    }

    this->m_nVerts = lastGeoIndex;
    this->m_nIndices = lastIndex; // Should be always equal to 300
}

} // namespace DayNight
