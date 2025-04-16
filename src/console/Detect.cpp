#include "console/Detect.hpp"
#include "db/Db.hpp"
#include "db/Startup_Strings.hpp"
#include "gx/CGxFormat.hpp"
#include "gx/Device.hpp"
#include "os/Debug.hpp"
#include "os/Gui.hpp"
#include <common/Processor.hpp>
#include <storm/Registry.hpp>

#if defined(WHOA_SYSTEM_MAC)
#include <OpenGL/gl.h>
#include <sys/sysctl.h>
#endif

WowClientDB<VideoHardwareRec> g_videoHardwareDB;

CGxFormat s_formats[7] = {
    { 0, { 640,  480 },  CGxFormat::Fmt_Rgb565,   CGxFormat::Fmt_Ds160, 60, 1, true, false, true, true, false },
    { 0, { 800,  600 },  CGxFormat::Fmt_Rgb565,   CGxFormat::Fmt_Ds160, 60, 1, true, false, true, true, false },
    { 0, { 640,  480 },  CGxFormat::Fmt_ArgbX888, CGxFormat::Fmt_Ds24X, 60, 1, true, false, true, true, false },
    { 0, { 800,  600 },  CGxFormat::Fmt_ArgbX888, CGxFormat::Fmt_Ds24X, 60, 1, true, false, true, true, false },
    { 0, { 1024, 768 },  CGxFormat::Fmt_ArgbX888, CGxFormat::Fmt_Ds24X, 60, 1, true, false, true, true, false },
    { 0, { 1280, 1024 }, CGxFormat::Fmt_ArgbX888, CGxFormat::Fmt_Ds24X, 60, 1, true, false, true, true, false },
    { 0, { 1600, 1200 }, CGxFormat::Fmt_ArgbX888, CGxFormat::Fmt_Ds24X, 60, 1, true, false, true, true, false }
};

CpuHardware s_cpuHwSettings[2] = {
    { 0, 0, 0, 0, 0, 0 },
    { 1, 1, 1, 1, 1, 1 }
};

SoundHardware s_soundHwSettings[1] = {
    { 1, false }
};

uint32_t s_detailDoodadDensity[4] = {
    8,
    12,
    16,
    24
};

bool s_animatingDoodads[2][2] = {
    { false, false },
    { false, true }
};

uint32_t s_waterLOD[2][2] = {
    { 0, 0 },
    { 0, 1 }
};

float s_particleDensity[4][2] = {
    { 0.3f, 0.4f },
    { 0.5f, 0.6f },
    { 0.9f, 1.0f },
    { 1.0f, 1.0f }
};

float s_unitDrawDist[4][2] = {
    { 35.0f,  50.0f },
    { 50.0f,  75.0f },
    { 75.0f,  300.0f },
    { 300.0f, 300.0f }
};

float s_smallCull[4][2] = {
    { 0.08f, 0.08f },
    { 0.07f, 0.07f },
    { 0.07f, 0.07f },
    { 0.04f, 0.04f }
};

float s_distCull[4][2] = {
    { 350.0f, 350.0f },
    { 400.0f, 400.0f },
    { 450.0f, 450.0f },
    { 500.0f, 500.0f },
};

float s_farClip[5][2] = {
    { 200.0f, 277.0f },
    { 300.0f, 350.0f },
    { 350.0f, 400.0f },
    { 450.0f, 550.0f },
    { 450.0f, 777.0f }
};

void AddResolution(TSGrowableArray<C2iVector>& resolutions, const C2iVector& resolution) {
    resolutions.Add(1, &resolution);
}

void ConsoleDetectGetResolutions(TSGrowableArray<C2iVector>& resolutions, int32_t widescreen) {
    if (widescreen) {
        TSGrowableArray<CGxMonitorMode> modes;
        GxAdapterMonitorModes(modes);

        C2iVector prev = { 0, 0 };

        for (uint32_t i = 0; i < modes.Count(); i++) {
            auto& mode = modes[i];
            if ((static_cast<float>(mode.size.x) / static_cast<float>(mode.size.y)) > 1.248f &&
                mode.size.x >= 640 &&
                mode.size.y >= 480 &&
                mode.size.x != prev.x && mode.size.y != prev.y) {
                AddResolution(resolutions, mode.size);
                prev = mode.size;
            }
        }
    }

    if (!resolutions.Count() || !widescreen) {
        // Add generic 4:3 fallback resolutions
        AddResolution(resolutions, { 640,  480 });
        AddResolution(resolutions, { 800,  600 });
        AddResolution(resolutions, { 1024, 768 });
        AddResolution(resolutions, { 1152, 864 });
        AddResolution(resolutions, { 1280, 960 });
        AddResolution(resolutions, { 1280, 1024 });
        AddResolution(resolutions, { 1600, 1200 });
    }
}

void ConsoleDetectSaveHardware(Hardware& hardware, bool& hwChanged) {
    uint32_t cpuIdx;
    uint32_t memIdx;
    uint32_t videoID;
    uint32_t soundIdx;

    if (!SRegLoadValue("World of Warcraft\\Client", "HWCpuIdx", 0, &cpuIdx)) {
        cpuIdx = hardware.cpuIdx;
    }
    if (!SRegLoadValue("World of Warcraft\\Client", "HWMemIdx", 0, &memIdx)) {
        memIdx = hardware.memIdx;
    }
    if (!SRegLoadValue("World of Warcraft\\Client", "HWVideoID", 0, &videoID)) {
        videoID = hardware.videoID;
    }
    if (!SRegLoadValue("World of Warcraft\\Client", "HWSoundIdx", 0, &soundIdx)) {
        soundIdx = hardware.soundIdx;
    }

    bool v2 = (((videoID == 1 || videoID == 168) || (videoID == 169)) || videoID == 170);
    if (hardware.cpuIdx == cpuIdx && hardware.memIdx == memIdx && (v2 || hardware.videoID == videoID) && hardware.soundIdx == soundIdx) {
        hwChanged = false;
    } else {
#if defined(WHOA_SYSTEM_WIN) || defined(WHOA_SYSTEM_LINUX)
        auto titleRecord = g_Startup_StringsDB.GetRecord(MSG_TITLE_WOW);
        auto title       = titleRecord ? titleRecord->m_message : "World of Warcraft";
        auto hwChangedMessageRecord = g_Startup_StringsDB.GetRecord(MSG_HW_CHANGED);
        auto message                = hwChangedMessageRecord ? hwChangedMessageRecord->m_message : "Hardware changed.  Reload default settings?";

        hwChanged = !OsGuiMessageBox(OsGuiGetWindow(2), 2, message, title);
#endif
#if defined(WHOA_SYSTEM_MAC)
        hwChanged = true;
#endif
    }

    SRegSaveValue("World of Warcraft\\Client", "HWCpuIdx", 0, hardware.cpuIdx);
    SRegSaveValue("World of Warcraft\\Client", "HWMemIdx", 0, hardware.memIdx);
    SRegSaveValue("World of Warcraft\\Client", "HWVideoID", 0, hardware.videoID);
    SRegSaveValue("World of Warcraft\\Client", "HWSoundIdx", 0, hardware.soundIdx);
}

[[noreturn]] void PrintStartupError(int32_t messageID, const char* fallbackMessage) {
    auto titleRecord   = g_Startup_StringsDB.GetRecord(MSG_TITLE_WOW);
    auto title         = titleRecord ? titleRecord->m_message : "World of Warcraft";
    auto messageRecord = g_Startup_StringsDB.GetRecord(messageID);
    auto message       = messageRecord ? messageRecord->m_message : fallbackMessage;

    OsGuiMessageBox(OsGuiGetWindow(2), 0, message, title);

    exit(0);
}

void SetVideoIdx(Hardware& hardware) {
    int32_t index = 1;

    while (index < g_videoHardwareDB.m_numRecords) {
        auto videoHw = g_videoHardwareDB.GetRecordByIndex(index);
        if (hardware.videoDevice.vendorID == videoHw->m_vendorID &&
            hardware.videoDevice.deviceID == videoHw->m_deviceID) {
            hardware.videoID = videoHw->m_ID;
        }
        index++;
    }
}

#if defined(WHOA_SYSTEM_WIN) || defined(WHOA_SYSTEM_LINUX)

void ConsoleDetectDetectHardware(Hardware& hardware, bool& hwChanged) {
    // anti-feature

    // if (OsIsRemoteSession()) {
    //     PrintStartupError(12, "Running World of Warcraft through a Remote Desktop connection is not supported.  Exiting program.");
    // }

    //

    g_videoHardwareDB.Load(__FILE__, __LINE__);

    hardware.cpuIdx   = (static_cast<float>(OsGetProcessorTicksPerSecond()) * 0.000001f) > 1500.0f;
    hardware.memIdx   = 0;
    hardware.videoID  = 0;

    if (GxAdapterID(hardware.videoDevice.vendorID,
                    hardware.videoDevice.deviceID,
                    hardware.videoDevice.driverVersionHi,
                    hardware.videoDevice.driverVersionLo)) {
        SetVideoIdx(hardware);
    }

    if (!hardware.videoID) {
        hardware.videoDevice.vendorID = 0xFFFF;
        if (GxAdapterInfer(hardware.videoDevice.deviceID)) {
            SetVideoIdx(hardware);
        }

        if (!hardware.videoID) {
            PrintStartupError(MSG_GX_NO_DEVICE, "Failed to find a suitable display device.  Exiting program.");
        }
    }

    hardware.cpuHw   = &s_cpuHwSettings[hardware.cpuIdx];
    hardware.videoHw = g_videoHardwareDB.GetRecord(hardware.videoID);
    hardware.soundHw = &s_soundHwSettings[hardware.soundIdx];

    ConsoleDetectSaveHardware(hardware, hwChanged);

    char str[1024];
    GxLog("ConsoleDetectDetectHardware():");
    SStrPrintf(str, 1024, "\tcpuIdx: %d", hardware.cpuIdx);
    GxLog(str);
    SStrPrintf(str, 1024, "\tvideoID: %d", hardware.videoID);
    GxLog(str);
    SStrPrintf(str, 1024, "\tsoundIdx: %d", hardware.soundIdx);
    GxLog(str);
    SStrPrintf(str, 1024, "\tmemIdx: %d", hardware.memIdx);
    GxLog(str);
}

#endif

#if defined(WHOA_SYSTEM_MAC)

uint32_t FindVRAMSize() {
    CGDirectDisplayID activeDisplays[32];
    uint32_t displayCount;
    if (CGGetActiveDisplayList(32, activeDisplays, &displayCount)) {
        return 0;
    }

    CGLRendererInfoObj rend;
    GLint nrend;
    GLint accelerated;
    GLint vram_size;

    auto display_mask = CGDisplayIDToOpenGLDisplayMask(activeDisplays[0]);
    if (!CGLQueryRendererInfo(display_mask, &rend, &nrend)) {
        CGLDescribeRenderer(rend, 0, kCGLRPRendererCount, &nrend);
        for (int32_t i = 0; i < nrend; i++) {
            CGLDescribeRenderer(rend, i, kCGLRPAccelerated, &accelerated);
            if (accelerated) {
                CGLDescribeRenderer(rend, i, kCGLRPVideoMemory, &vram_size);
                CGLDestroyRendererInfo(rend);
                return static_cast<uint32_t>(vram_size);
            }
        }
    }

    CGLDestroyRendererInfo(rend);
    return 0;
}

void ConsoleDetectDetectHardware(Hardware& hardware, bool& hwChanged) {
    g_videoHardwareDB.Load(__FILE__, __LINE__);

    if (GxAdapterID(hardware.videoDevice.vendorID,
                    hardware.videoDevice.deviceID,
                    hardware.videoDevice.driverVersionHi,
                    hardware.videoDevice.driverVersionLo)) {
        SetVideoIdx(hardware);
    }

    if (!hardware.videoIdx) {
        hardware.videoDevice.vendorID = 0xFFFF;
        if (GxAdapterInfer(hardware.videoDevice.deviceID)) {
            SetVideoIdx(hardware);
        }
    }

    uint32_t hw_cputype          = 0;
    uint32_t hw_cpusubtype       = 0;
    uint32_t hw_ncpu             = 0;
    uint64_t hw_cpufrequency_max = 0;
    uint64_t hw_busfrequency_max = 0;
    uint64_t hw_l2cachesize      = 0;
    uint64_t hw_l3cachesize      = 0;

    size_t size32 = sizeof(uint32_t);
    size_t size64 = sizeof(uint64_t);

    uint32_t hw_cputype;
    auto hw_cputype_error = sysctlbyname("hw.cputype", &hw_cputype, &size32, nullptr, 0);
    if (hw_cputype_error) {
        OsOutputDebugString("[Mac sys detect] ! error %d reading hw.cputype\n", hw_cputype_error);
    }

    auto hw_cpusubtype_error = sysctlbyname("hw.cpusubtype", &hw_cpusubtype, &size32, nullptr, 0);
    if (hw_cpusubtype_error) {
        OsOutputDebugString("[Mac sys detect] ! error %d reading hw.cpusubtype\n", hw_cpusubtype_error);
    }

    auto hw_ncpu_error = sysctlbyname("hw.ncpu", &hw_ncpu, &size32, nullptr, 0);
    if (hw_ncpu_error) {
        OsOutputDebugString("[Mac sys detect] ! error %d reading hw.ncpu\n", hw_ncpu_error);
    }

    auto hw_cpufrequency_max_error = sysctlbyname("hw.cpufrequency_max", &hw_cpufrequency_max, &size64, nullptr, 0);
    if (hw_cpufrequency_max_error) {
        OsOutputDebugString("[Mac sys detect] ! error %d reading hw.cpufrequency_max\n", hw_cpufrequency_max_error);
    }

    auto hw_busfrequency_max_error = sysctlbyname("hw.busfrequency_max", hw_busfrequency_max, &size64, nullptr, 0);
    if (hw_busfrequency_max_error) {
        OsOutputDebugString("[Mac sys detect] ! error %d reading hw.busfrequency_max\n", iVar6);
    }

    auto hw_l2cachesize_error = sysctlbyname("hw.l2cachesize", &hw_l2cachesize, &size64, nullptr, 0);
    if (hw_l2cachesize_error) {
        hw_l2cachesize_error = 0;
        OsOutputDebugString("[Mac sys detect] ! error %d reading hw.l2cachesize\n", hw_l2cachesize_error);
    }
    auto hw_l3cachesize_error = sysctlbyname("hw.l3cachesize", &hw_l3cachesize, &size64, nullptr, 0);
    if (hw_l3cachesize_error) {
        hw_l3cachesize_error = 0;
        OsOutputDebugString("[Mac sys detect] ! error %d reading hw.l3cachesize\n", iVar8);
    }

    auto hw_memsize_error = sysctlbyname("hw.memsize", &hw_memsize, &size64, nullptr, 0);
    if (hw_memsize_error) {
        OsOutputDebugString("[Mac sys detect] ! error %d reading hw.memsize\n", hw_memsize_error);
    }

    auto vram_size = FindVRAMSize();

    bool ddr_ram;
    if (hw_busfrequency_max > 110000000 && (hw_busfrequency_max > 140000000 || h2_l3cachesize > 0xFFFFF && hw_l2cachesize > 0x7FFFF)) {
        OsOutputDebugString("[Mac sys detect] - DDR RAM\n");
        ddr_ram = true;
    } else {
        OsOutputDebugString("[Mac sys detect] - non DDR RAM\n");
        ddr_ram = false;
    }

    uint32_t cpuIdx;
    uint32_t macTier;

    if (hw_cpusubtype_error || hw_cputype_error || hw_ncpu_error || hw_cpufrequency_max_error || hw_busfrequency_max_error || hw_l2cachesize_error || hw_l3cachesize_error || hw_memsize_error) {
        OsOutputDebugString("[Mac sys detect] ! error reading specs, down to tier 0\n", v27);
        cpuIdx  = 0;
        macTier = 0;
    } else {
        macTier = 3;
        if (hw_ncpu < 2) {
            OsOutputDebugString("[Mac sys detect] - non dual proc, down to tier 2\n");
            macTier = 2;
        }
        if (hw_busfrequency_max < 500000000) {
            OsOutputDebugString("[Mac sys detect] - sub 500MHz FSB, down to tier 2\n");
            macTier = 2;
        }
        if (hw_memsize < 0x30000000) {
            OsOutputDebugString("[Mac sys detect] - under 768MB RAM, down to tier 2\n");
            macTier = 2;
        }
        if (hw_cpufrequency_max < 1100000000) {
            OsOutputDebugString("[Mac sys detect] - under 1.1GHz CPU, down to tier 1\n");
            macTier = 1;
        }
        if (vram_size < 0x4000000) {
            OsOutputDebugString("[Mac sys detect] - < 64MB VRAM, down to tier 1\n");
            macTier = 1;
        }
        if (hw_cputype == 18 && hw_cpusubtype < 11) {
            OsOutputDebugString("[Mac sys detect] - G3 or G4, down to tier 0\n");
            macTier = 0;
        }
        if (vram_size <= 0x2000000) {
            OsOutputDebugString("[Mac sys detect] - <= 32 MB VRAM, down to tier 0\n");
            macTier = 0;
        }
        if (!ddr_ram) {
            OsOutputDebugString("[Mac sys detect] - no DDR RAM, down to tier 0\n");
            macTier = 0;
        }
        if (hw_l2cachesize <= 0x40000 && hw_l3cachesize <= 0xFFFFF) {
            OsOutputDebugString("[Mac sys detect] - L2 <= 256K and L3 <= 1MB, down to tier 0\n");
            macTier = 0;
        }
        if (hw_memsize < 0x20000000) {
            OsOutputDebugString("[Mac sys detect] - < 512MB RAM, down to tier 0\n");
            cpuIdx  = 0;
            macTier = 0;
        } else {
            cpuIdx = macTier / 2;
        }
    }

    hardware.cpuIdx     = cpuIdx;
    hardware.memIdx     = 0;
    hardware.soundIdx   = 0;
    hardware.macTierIdx = macTier;
    hardware.macVramMB  = vram_size / 0x100000;

    hardware.cpuHw   = s_cpuHwSettings[cpuIdx];
    hardware.videoHw = g_videoHardwareDB.GetRecord(hardware.videoID);
    hardware.soundHw = s_soundHwSettings[hardware.soundIdx];

    ConsoleDetectSaveHardware(hardware, hwChanged);

    char str[1024];
    GxLog("ConsoleDetectDetectHardware [Mac] ():");
    SStrPrintf(str, 1024, "\tcpuIdx: %d", hardware.cpuIdx);
    GxLog(str);
    SStrPrintf(str, 1024, "\tvideoID: %d", hardware.videoIdx);
    GxLog(str);
    SStrPrintf(str, 1024, "\tsoundIdx: %d", hardware.soundIdx);
    GxLog(str);
    SStrPrintf(str, 1024, "\tmemIdx: %d", hardware.memIdx);
    GxLog(str);
    SStrPrintf(str, 1024, "\tmacTierIdx: %d", hardware.macTierIdx);
    GxLog(str);
    SStrPrintf(str, 1024, "\tmacVramMB: %d", hardware.macVramMB);
    GxLog(str);
}

#endif

void ConsoleDetectSetDefaultsFormat(DefaultSettings& defaults, const Hardware& hardware) {
    defaults.format = &s_formats[hardware.videoHw->m_resolutionIdx];
}

void ConsoleDetectSetDefaults(DefaultSettings& defaults, const Hardware& hw) {
    defaults.farClip = s_farClip[hw.videoHw->m_farclipIdx][hw.cpuHw->farclipIdx];
    defaults.terrainShadowLOD = hw.videoHw->m_terrainShadowLod;
    defaults.detailDoodadDensity = s_detailDoodadDensity[hw.videoHw->m_detailDoodadDensityIdx];
    defaults.detailDoodadAlpha = hw.videoHw->m_detailDoodadAlpha;
    defaults.animatingDoodads = s_animatingDoodads[hw.videoHw->m_animatingDoodadIdx][hw.cpuHw->animatingDoodadIdx];
    defaults.trilinear = hw.videoHw->m_trilinear != 0;
    defaults.numLights = hw.videoHw->m_numLights;
    auto specularity = hw.videoHw->m_specularity != 0;
    defaults.unk1A = specularity;
    defaults.specularity = specularity;
    defaults.waterLOD = s_waterLOD[hw.videoHw->m_waterLodidx][hw.cpuHw->waterLODIdx];
    defaults.particleDensity = s_particleDensity[hw.videoHw->m_particleDensityIdx][hw.cpuHw->particleDensityIdx];
    defaults.unitDrawDist = s_unitDrawDist[hw.videoHw->m_unitDrawDistIdx][hw.cpuHw->unitDrawDistIdx];
    defaults.smallCull = s_smallCull[hw.videoHw->m_smallCullDistIdx][hw.cpuHw->smallCullDistIdx];
    defaults.distCull = s_distCull[hw.videoHw->m_smallCullDistIdx][hw.cpuHw->smallCullDistIdx];
    defaults.format = s_formats + hw.videoHw->m_resolutionIdx;
    defaults.baseMipLevel = hw.videoHw->m_baseMipLevel;
    defaults.unk19 = true;
    defaults.numChannels = 0;
    defaults.fivePointOne = false;
}
