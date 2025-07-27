#ifndef WORLD_DAY_NIGHT_SKY_HPP
#define WORLD_DAY_NIGHT_SKY_HPP

#include <cstdint>
#include <storm/Array.hpp>
#include <tempest/Vector.hpp>

namespace DayNight {

class DNSky {
    public:
    enum {
        SKY_NUMBANDS = 7
    };

    void Render();
    void GenSphere(float sphRadius);
    void SetColors();

    static float m_stripSizes[SKY_NUMBANDS];
    static float m_fadeAngle[SKY_NUMBANDS];
    static float m_darkAngle[SKY_NUMBANDS];

    TSFixedArray<C3Vector> m_geoVerts;
    TSFixedArray<CImVector> m_clrVerts;
    TSFixedArray<uint16_t> m_indices;
    int32_t m_sphThetaTess = 0;
    uint16_t m_nVerts = 0;
    uint16_t m_nIndices = 0;
    float m_sphRadius = 0.0f;
};

} // namespace DayNight

#endif
