#include "console/cvar/Gx.hpp"
#include "console/Gx.hpp"
#include "console/Console.hpp"
#include "console/Detect.hpp"
#include "console/Device.hpp"
#include "console/Types.hpp"
#include "gx/CGxFormat.hpp"
#include "gx/CGxMonitorMode.hpp"
#include "gx/Device.hpp"
#include "gx/Types.hpp"
#include "gx/Gx.hpp"
#include "os/Input.hpp"
#include "storm/String.hpp"
#include <storm/Array.hpp>
#include <cstdio>

CVar* s_cvGxStereoEnabled;
CVar* s_cvGxRefresh;
CVar* s_cvGxMaximize;
CVar* s_cvGxMultisample;
CVar* s_cvGxCursor;
CVar* s_cvGxStereoSeparation;
CVar* s_cvGxMultisampleQuality;
CVar* s_cvGxResolution;
CVar* s_cvGxOverride;
CVar* s_cvGxFixLag;
CVar* s_cvMaxFPS;
CVar* s_cvGxVSync;
CVar* s_cvVideoOptionsVersion;
CVar* s_cvGxStereoConvergence;
CVar* s_cvMaxFPSBk;
CVar* s_cvGxTripleBuffer;
CVar* s_cvGxDepthBits;
CVar* s_cvGxColorBits;
CVar* s_cvGxApi;
CVar* s_cvGxAspect;
CVar* s_cvFixedFunction;
CVar* s_cvWidescreen;
CVar* s_cvGxWindow;
CVar* s_cvWindowResizeLock;

static const char* formatToInt[CGxFormat::Formats_Last] = {
    "16",
    "24",
    "24",
    "30",
    "16",
    "24",
    "24",
    "32"
};

bool CVGxColorBitsCallback(CVar* h, const char* oldValue, const char* newValue, void* arg) {
    auto colorBits = SStrToInt(newValue);
    switch (colorBits) {
    case 16:
        s_requestedFormat.colorFormat = CGxFormat::Fmt_Rgb565;
        break;
    case 24:
        s_requestedFormat.colorFormat = CGxFormat::Fmt_ArgbX888;
        break;
    case 30:
        s_requestedFormat.colorFormat = CGxFormat::Fmt_Argb2101010;
        break;
    default:
        ConsoleWrite("Color bits must be 16, 24, or 30", DEFAULT_COLOR);
        return false;
    }

    ConsoleWrite("set pending gxRestart", DEFAULT_COLOR);
    return true;
}

bool CVGxDepthBitsCallback(CVar* h, const char* oldValue, const char* newValue, void* arg) {
    auto depthBits = SStrToInt(newValue);
    switch (depthBits) {
    case 16:
        s_requestedFormat.depthFormat = CGxFormat::Fmt_Ds160;
        break;
    case 24:
        s_requestedFormat.depthFormat = CGxFormat::Fmt_Ds24X;
        break;
    case 32:
        s_requestedFormat.depthFormat = CGxFormat::Fmt_Ds320;
        break;
    default:
        ConsoleWrite("Depth bits must be 16, 24, or 32", DEFAULT_COLOR);
        return false;
    }

    ConsoleWrite("set pending gxRestart", DEFAULT_COLOR);
    return true;
}

bool CVGxTripleBufferCallback(CVar* h, const char* oldValue, const char* newValue, void* arg) {
    auto tripleBuffer = SStrToInt(newValue);
    if (tripleBuffer > 1) {
        ConsoleWrite("TripleBuffer must be 0 or 1", DEFAULT_COLOR);
        return false;
    }

    // TODO
    // s_requestedFormat.unk1C = (tripleBuffer != 0) + 1;
    ConsoleWrite("set pending gxRestart", DEFAULT_COLOR);
    return 1;
}

bool CVGxApiCallback(CVar* h, const char* oldValue, const char* newValue, void* arg) {
    for (EGxApi api = GxApi_OpenGl; api < GxApis_Last; api = static_cast<EGxApi>(static_cast<int32_t>(api) + 1)) {
        if (GxApiSupported(api)) {
            if (!SStrCmpI(newValue, g_gxApiNames[api], STORM_MAX_STR)) {
                ConsoleWrite("GxApi set pending gxRestart", DEFAULT_COLOR);
                return true;
            }
        }
    }

    // User supplied an unknown gxApi string
    // display list of available gxApis
    char message[1024];
    SStrCopy(message, "unsupported api, must be one of ", sizeof(message));

    uint32_t i = 0;
    for (EGxApi api = GxApi_OpenGl; api < GxApis_Last; api = static_cast<EGxApi>(static_cast<int32_t>(api) + 1)) {
        if (GxApiSupported(api)) {
            if (i) {
                SStrPack(message, ", ", sizeof(message));
            }

            SStrPack(message, "'", sizeof(message));
            SStrPack(message, g_gxApiNames[api], sizeof(message));
            SStrPack(message, "'", sizeof(message));
            i++;
        }
    }

    ConsoleWrite(message, DEFAULT_COLOR);
    return false;
}

bool CVGxVSyncCallback(CVar* h, const char* oldValue, const char* newValue, void* arg) {
    s_requestedFormat.vsync = SStrToInt(newValue);
    ConsoleWrite("set pending gxRestart", DEFAULT_COLOR);
    return true;
}

bool CVGxWindowCallback(CVar* h, const char* oldValue, const char* newValue, void* arg) {
    s_requestedFormat.window = SStrToInt(newValue) != 0;
    ConsoleWrite("set pending gxRestart", DEFAULT_COLOR);
    return true;
}

bool CVGxAspectCallback(CVar* h, const char* oldValue, const char* newValue, void* arg) {
    s_requestedFormat.aspect = SStrToInt(newValue) != 0;
    ConsoleWrite("set pending gxRestart", DEFAULT_COLOR);
    return true;
}

bool CVGxMaximizeCallback(CVar* h, const char* oldValue, const char* newValue, void* arg) {
    s_requestedFormat.maximize = SStrToInt(newValue) != 0;
    ConsoleWrite("set pending gxRestart", DEFAULT_COLOR);
    return true;
}

bool CVGxCursorCallback(CVar* h, const char* oldValue, const char* newValue, void* arg) {
    s_requestedFormat.hwCursor = SStrToInt(newValue) != 0;
    ConsoleWrite("set pending gxRestart", DEFAULT_COLOR);
    return true;
}

bool CVGxMultisampleCallback(CVar* h, const char* oldValue, const char* newValue, void* arg) {
    auto sampleCount = SStrToInt(newValue);
    s_requestedFormat.sampleCount = std::max(1, std::min(sampleCount, 16));
    ConsoleWrite("set pending gxRestart", DEFAULT_COLOR);
    return true;
}

bool CVGxMultisampleQualityCallback(CVar* h, const char* oldValue, const char* newValue, void* arg) {
    auto sampleQuality = SStrToFloat(newValue);
    s_requestedFormat.sampleQuality = std::max(0.0f, std::min(sampleQuality, 1.0f));
    ConsoleWrite("set pending gxRestart", DEFAULT_COLOR);
    return true;
}

bool CVGxFixLagCallback(CVar* h, const char* oldValue, const char* newValue, void* arg) {
    s_requestedFormat.fixLag = SStrToInt(newValue) != 0;
    ConsoleWrite("set pending gxRestart", DEFAULT_COLOR);
    return true;
}

bool CVGxOverrideCallback(CVar* h, const char* oldValue, const char* newValue, void* arg) {
    ConsoleGxOverride(newValue);
    return true;
}

bool CVGxMaxFPSCallback(CVar* h, const char* oldValue, const char* newValue, void* arg) {
    auto maxFPS = SStrToInt(newValue);
    GxSetMaxFPS(std::max(8, maxFPS));
    return true;
}

bool CVGxMaxFPSBkCallback(CVar* h, const char* oldValue, const char* newValue, void* arg) {
    auto maxFPSBk = SStrToInt(newValue);
    GxSetMaxFPSBk(std::max(8, maxFPSBk));
    return true;
}

bool CVGxWindowResizeLockCallback(CVar* h, const char* oldValue, const char* newValue, void* arg) {
    OsInputSetWindowResizeLock(SStrToInt(newValue));
    return true;
}

bool CVGxStereoEnabledCallback(CVar* h, const char* oldValue, const char* newValue, void* arg) {
    s_requestedFormat.stereoEnabled = SStrToInt(newValue) == 1;
    return true;
}

bool CVGxStereoConvergenceCallback(CVar* h, const char* oldValue, const char* newValue, void* arg) {
    GxStereoSetConvergence(SStrToFloat(newValue));
    return true;
}

bool CVGxStereoSeparationCallback(CVar* h, const char* oldValue, const char* newValue, void* arg) {
    GxStereoSetSeparation(SStrToFloat(newValue));
    return true;
}

bool CVGxResolutionCallback(CVar* h, const char* oldValue, const char* newValue, void* arg) {
    C2iVector size = { -1, -1 };
    uint8_t x;
    sscanf(newValue, "%d%c%d", &size.x, &x, &size.y);

    if (s_requestedFormat.window) {
        s_requestedFormat.size = size;
        ConsoleWrite("set pending gxRestart", DEFAULT_COLOR);
        return true;
    }

    TSGrowableArray<C2iVector> resolutions;
    ConsoleDetectGetResolutions(resolutions, s_cvWidescreen->GetInt());

    uint32_t i;
    for (i = 0; i < resolutions.Count(); i++) {
        if (size.x == resolutions[i].x && size.y == resolutions[i].y) {
            break;
        }
    }

    char str[256];
    char rez[16];
    if (i == resolutions.Count()) {
        SStrCopy(str, "invalid resolution, must be one of ", sizeof(str));
        for (uint32_t i = 0; i < resolutions.Count(); i++) {
            if (i) {
                SStrPack(str, ", ", sizeof(str));
            }

            // flush line
            if (SStrLen(str) > 100) {
                ConsoleWrite(str, DEFAULT_COLOR);
                *str = '\0';
            }

            SStrPrintf(rez, sizeof(rez), "%dx%d", resolutions[i].x, resolutions[i].y);
            SStrPack(str, rez, sizeof(str));
        }

        ConsoleWrite(str, DEFAULT_COLOR);
        return 0;
    }

    s_requestedFormat.size = size;
    ConsoleWrite("set pending gxRestart", DEFAULT_COLOR);
    return true;
}

bool CVGxRefreshCallback(CVar* h, const char* oldValue, const char* newValue, void* arg) {
    auto refreshRate = SStrToUnsigned(newValue);

    TSGrowableArray<CGxMonitorMode> modes;
    GxAdapterMonitorModes(modes);

    uint32_t i;
    for (i = 0; i < modes.Count(); i++) {
        if (modes[i].refreshRate == refreshRate) {
            break;
        }
    }

    if (i == modes.Count()) {
        ConsoleWrite("Unsupported refresh rate", DEFAULT_COLOR);
        return false;
    }

    s_requestedFormat.refreshRate = refreshRate;
    ConsoleWrite("set pending gxRestart", DEFAULT_COLOR);
    return true;
}

bool CVGxVideoOptionsVersionCallback(CVar* h, const char* oldValue, const char* newValue, void* arg) {
    return true;
}

void RegisterGxCVars() {
    auto format = s_defaults.format;

    // TODO CURRENT_LANGUAGE check
    auto v1 = true;

    s_cvWidescreen = CVar::Register(
        "widescreen",
        "Allow widescreen support",
        0,
        "1",
        nullptr,
        GRAPHICS,
        false,
        nullptr,
        false
    );

    s_cvGxWindow = CVar::Register(
        "gxWindow",
        "toggle fullscreen/window",
        0x1 | 0x2,
        v1 ? "1" : "0",
        CVGxWindowCallback,
        GRAPHICS,
        false,
        nullptr,
        false
    );

    s_cvGxMaximize = CVar::Register(
        "gxMaximize",
        "maximize game window",
        0x1 | 0x2,
        v1 ? "1" : "0",
        CVGxMaximizeCallback,
        GRAPHICS,
        false,
        nullptr,
        false
    );

    char colorBits[260];
    SStrPrintf(colorBits, 260, "%s", formatToInt[format->colorFormat]);
    s_cvGxColorBits = CVar::Register(
        "gxColor",
        "color bits",
        0x1 | 0x2,
        colorBits,
        CVGxColorBitsCallback,
        GRAPHICS,
        false,
        nullptr,
        false
    );

    char depthBits[260];
    SStrPrintf(depthBits, 260, "%s", formatToInt[format->depthFormat]);
    s_cvGxDepthBits = CVar::Register(
        "gxDepthBits",
        "depth bits",
        0x1 | 0x2,
        colorBits,
        CVGxDepthBitsCallback,
        GRAPHICS,
        false,
        nullptr,
        false);

    char resolution[260];
    SStrPrintf(resolution, 260, "%dx%d", format->size.x, format->size.y);
    s_cvGxResolution = CVar::Register(
        "gxResolution",
        "resolution",
        0x1 | 0x2,
        resolution,
        CVGxResolutionCallback,
        GRAPHICS,
        false,
        nullptr,
        false
    );

    s_cvGxRefresh = CVar::Register(
        "gxRefresh",
        "refresh rate",
        0x1 | 0x2,
        "75",
        CVGxRefreshCallback,
        GRAPHICS,
        false,
        nullptr,
        false
    );

    s_cvGxTripleBuffer = CVar::Register(
        "gxTripleBuffer",
        "triple buffer",
        0x1 | 0x2,
        "0",
        CVGxTripleBufferCallback,
        GRAPHICS,
        false,
        nullptr,
        false
    );

    s_cvGxApi = CVar::Register(
        "gxApi",
        "graphics api",
        0x1 | 0x2,
        g_gxApiNames[GxDefaultApi()],
        CVGxApiCallback,
        GRAPHICS,
        false,
        nullptr,
        false
    );

    s_cvGxVSync = CVar::Register(
        "gxVSync",
        "vsync on or off",
        0x1 | 0x2,
        "1",
        CVGxVSyncCallback,
        GRAPHICS,
        false,
        nullptr,
        false
    );

    s_cvGxAspect = CVar::Register(
        "gxAspect",
        "constrain window aspect",
        0x1 | 0x2,
        "1",
        CVGxAspectCallback,
        GRAPHICS,
        false,
        nullptr,
        false
    );

    s_cvGxCursor = CVar::Register(
        "gxCursor",
        "toggle hardware cursor",
        0x1 | 0x2,
        "1",
        CVGxCursorCallback,
        GRAPHICS,
        false,
        nullptr,
        false
    );

    char multisample[260];
    SStrPrintf(multisample, 260, "%d", s_hardware.videoHw->m_multisample);
    s_cvGxMultisample = CVar::Register(
        "gxMultisample",
        "multisample",
        0x1 | 0x2,
        multisample,
        CVGxMultisampleCallback,
        GRAPHICS,
        false,
        nullptr,
        false
    );

    s_cvGxMultisampleQuality = CVar::Register(
        "gxMultisampleQuality",
        "multisample quality",
        0x1 | 0x2,
        "0.0",
        CVGxMultisampleQualityCallback,
        GRAPHICS,
        false,
        nullptr,
        false
    );

    char fixLag[260];
    SStrPrintf(fixLag, 260, "%d", s_hardware.videoHw->m_fixLag);
    s_cvGxFixLag = CVar::Register(
        "gxFixLag",
        "prevent cursor lag",
        0x1 | 0x2,
        fixLag,
        CVGxFixLagCallback,
        GRAPHICS,
        false,
        nullptr,
        false
    );

    s_cvGxStereoEnabled = CVar::Register(
        "gxStereoEnabled",
        "Enable stereoscopic rendering",
        0x1,
        "0",
        CVGxStereoEnabledCallback,
        GRAPHICS,
        false,
        nullptr,
        false
    );

    s_cvGxOverride = CVar::Register(
        "gxOverride",
        "gx overrides",
        0x1,
        "",
        CVGxOverrideCallback,
        GRAPHICS,
        false,
        nullptr,
        false
    );

    s_cvMaxFPS = CVar::Register(
        "maxFPS",
        "Set FPS limit",
        0x1,
        "200",
        CVGxMaxFPSCallback,
        GRAPHICS,
        false,
        nullptr,
        false
    );

    s_cvMaxFPSBk = CVar::Register(
        "maxFPSBk",
        "Set background FPS limit",
        0x1,
        "30",
        CVGxMaxFPSBkCallback,
        GRAPHICS,
        false,
        nullptr,
        false
    );

    s_cvVideoOptionsVersion = CVar::Register(
        "videoOptionsVersion",
        "Video options version",
        0x1 | 0x2,
        "0",
        CVGxVideoOptionsVersionCallback,
        GRAPHICS,
        false,
        nullptr,
        false
    );

    s_cvWindowResizeLock = CVar::Register(
        "windowResizeLock",
        "prevent resizing in windowed mode",
        0x1,
        "0",
        CVGxWindowResizeLockCallback,
        GRAPHICS,
        false,
        nullptr,
        false
    );

    s_cvFixedFunction = CVar::Register(
        "fixedFunction",
        "Force fixed function rendering",
        0x1 | 0x2,
        "0",
        nullptr,
        GRAPHICS,
        false,
        nullptr,
        false
    );
}

void UpdateGxCVars() {
    s_cvGxColorBits->Update();
    s_cvGxDepthBits->Update();
    s_cvGxWindow->Update();
    s_cvGxResolution->Update();
    s_cvGxRefresh->Update();
    s_cvGxTripleBuffer->Update();
    s_cvGxApi->Update();
    s_cvGxVSync->Update();
    s_cvGxAspect->Update();
    s_cvGxMaximize->Update();
    s_cvGxCursor->Update();
    s_cvGxMultisample->Update();
    s_cvGxMultisampleQuality->Update();
    s_cvGxFixLag->Update();
}

void SetGxCVars(const CGxFormat& format) {
    char value[1024];

    s_cvGxColorBits->Set(formatToInt[format.colorFormat], true, false, false, true);

    s_cvGxDepthBits->Set(formatToInt[format.depthFormat], true, false, false, true);

    SStrPrintf(value, 1024, "%d", format.window);
    s_cvGxWindow->Set(value, true, false, false, true);

    SStrPrintf(value, 1024, "%dx%d", format.size.x, format.size.y);
    s_cvGxResolution->Set(value, true, false, false, true);

    SStrPrintf(value, 1024, "%d", format.refreshRate);
    s_cvGxRefresh->Set(value, true, false, false, true);

    s_cvGxTripleBuffer->Set(format.backbuffers > 1 ? "1" : "0", true, false, false, true);

    SStrPrintf(value, 1024, "%d", format.vsync);
    s_cvGxVSync->Set(value, true, false, false, true);

    SStrPrintf(value, 1024, "%d", format.aspect);
    s_cvGxAspect->Set(value, true, false, false, true);

    SStrPrintf(value, 1024, "%d", format.maximize);
    s_cvGxMaximize->Set(value, true, false, false, true);

    SStrPrintf(value, 1024, "%d", format.hwCursor);
    s_cvGxCursor->Set(value, true, false, false, true);

    SStrPrintf(value, 1024, "%d", format.sampleCount);
    s_cvGxMultisample->Set(value, true, false, false, true);

    SStrPrintf(value, 1024, "%f", format.sampleQuality);
    s_cvGxMultisampleQuality->Set(value, true, false, false, true);

    SStrPrintf(value, 1024, "%d", format.fixLag);
    s_cvGxFixLag->Set(value, true, false, false, true);

    UpdateGxCVars();
}
