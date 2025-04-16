#ifndef CONSOLE_DETECT_HPP
#define CONSOLE_DETECT_HPP

#include <storm/Array.hpp>
#include <tempest/Vector.hpp>

#include "gx/CGxFormat.hpp"

#include "db/rec/VideoHardwareRec.hpp"

struct CpuHardware {
    uint32_t farclipIdx;
    uint32_t animatingDoodadIdx;
    uint32_t waterLODIdx;
    uint32_t particleDensityIdx;
    uint32_t smallCullDistIdx;
    uint32_t unitDrawDistIdx;
};

struct SoundHardware {
    uint32_t numChannels;
    bool fivePointOne;
};

struct Hardware {
    struct Device {
        uint16_t vendorID;
        uint16_t deviceID;
        uint32_t driverVersionHi;
        uint32_t driverVersionLo;
    };

    Device videoDevice;
    Device soundDevice;
    uint32_t cpuIdx;
    uint32_t videoID;
    uint32_t soundIdx;
    uint32_t memIdx;
    VideoHardwareRec* videoHw;
    CpuHardware* cpuHw;
    SoundHardware* soundHw;
};

struct DefaultSettings {
    float farClip;
    uint32_t terrainShadowLOD;
    uint32_t detailDoodadDensity;
    uint32_t detailDoodadAlpha;
    bool animatingDoodads;
    bool trilinear;
    uint32_t numLights;
    bool specularity;
    bool unk19;
    bool unk1A;
    uint32_t waterLOD;
    float particleDensity;
    float unitDrawDist;
    float smallCull;
    float distCull;
    CGxFormat* format;
    uint32_t baseMipLevel;
    uint32_t numChannels;
    bool fivePointOne;
};

void ConsoleDetectGetResolutions(TSGrowableArray<C2iVector>& list, int32_t widescreen);

void ConsoleDetectDetectHardware(Hardware& hardware, bool& hwChanged);

void ConsoleDetectSetDefaultsFormat(DefaultSettings& defaults, const Hardware& hardware);

void ConsoleDetectSetDefaults(DefaultSettings& defaults, const Hardware& hw);

#endif
