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
    GxPrimLockVertexPtrs(
        this->m_nVerts, this->m_geoVerts.Ptr(), sizeof(C3Vector),
        nullptr, 0,
        this->m_clrVerts.Ptr(), sizeof(CImVector),
        nullptr, 0,
        nullptr, 0,
        nullptr, 0);
    GxDrawLockedElements(GxPrim_TriangleStrip, this->m_nIndices, this->m_indices.Ptr());
    GxPrimUnlockVertexPtrs();
    GxXformPop(GxXform_World);
    GxRsPop();
}

void DNSky::GenSphere(float sphRadius) {
    const uint16_t totalSlices = 24;
    const uint16_t totalIndices = (totalSlices + 1) * 2;

    this->m_sphThetaTess = totalSlices;
    this->m_geoVerts.SetCount(SKY_NUMBANDS * totalSlices); // 168
    this->m_clrVerts.SetCount(SKY_NUMBANDS * totalSlices); // 168
    this->m_indices.SetCount((SKY_NUMBANDS - 1) * totalIndices); // 300

    uint16_t lastIndex = 0;

    uint16_t lastRowIndex = 0;
    uint16_t thisRowIndex = 0;
    uint16_t prevRowIndex = 0;

    float prevPhi = 0.0f;

    for (int32_t i = 0; i < SKY_NUMBANDS; ++i) {
        float phi = DNSky::m_stripSizes[i] * CMath::PI;

        float cosPhi = CMath::cos(phi);
        float sinPhi = CMath::sin(phi);

        thisRowIndex = lastRowIndex;

        for (uint16_t j = 0; j < totalSlices; ++j) {
            auto& vertex = this->m_geoVerts[lastRowIndex++];

            float theta = static_cast<float>(j) / static_cast<float>(totalSlices) * CMath::TWO_PI;
            vertex.x = CMath::sin(theta) * sinPhi * sphRadius;
            vertex.y = CMath::cos(theta) * sinPhi * sphRadius;
            vertex.z = cosPhi * sphRadius;

            if (CMath::fequal(phi, 0.0f) || CMath::fequal(phi, CMath::PI)) {
                break;
            }
        }

        if (i > 0) {
            for (uint16_t k = 0; k < totalIndices / 2; ++k) {
                uint16_t idx1 = CMath::fequal(prevPhi, 0.0f) ? 0 : (k % totalSlices);
                uint16_t idx2 = CMath::fequal(phi, CMath::PI) ? 0 : (k % totalSlices);
                this->m_indices[lastIndex++] = idx1 + prevRowIndex;
                this->m_indices[lastIndex++] = idx2 + thisRowIndex;
            }
        }

        prevPhi = phi;
        prevRowIndex = thisRowIndex;
    }

    this->m_nVerts = lastRowIndex;
    this->m_nIndices = lastIndex; // Should be always equal to 300
}

void DNSky::SetColors() {
    // TODO
    for (uint32_t i = 0; i < this->m_clrVerts.Count(); ++i) {
        this->m_clrVerts[i] = { 0xFF, 0, 0xFF, 0xFF };
    }
}

} // namespace DayNight
