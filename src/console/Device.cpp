#include "console/Device.hpp"
#include "client/CmdLine.hpp"
#include "client/Gui.hpp"
#include "console/Console.hpp"
#include "console/CVar.hpp"
#include "console/Command.hpp"
#include "event/Input.hpp"
#include "gx/Gx.hpp"
#include "gx/Device.hpp"
#include <cstring>
#include <cstdio>


CVar* s_cvHwDetect;
CVar* s_cvGxFixedFunction;
CVar* s_cvGxWindowResizeLock;
CVar* s_cvGxVideoOptionsVersion;
CVar* s_cvGxMaxFPSBk;
CVar* s_cvGxMaxFPS;
CVar* s_cvGxOverride;
CVar* s_cvGxStereoEnabled;
CVar* s_cvGxFixLag;
CVar* s_cvGxMultisampleQuality;
CVar* s_cvGxMultisample;
CVar* s_cvGxCursor;
CVar* s_cvGxAspect;
CVar* s_cvGxVSync;
CVar* s_cvGxTripleBuffer;
CVar* s_cvGxRefresh;
CVar* s_cvGxDepthBits;
CVar* s_cvGxColorBits;
CVar* s_cvGxMaximize;
CVar* s_cvGxResolution;
CVar* s_cvGxWidescreen;
CVar* s_cvGxWindow;
CVar* s_cvGxApi;
DefaultSettings s_defaults;
bool s_hwDetect;
bool s_hwChanged;
CGxFormat s_requestedFormat;

const char* g_gxApiNames[GxApis_Last] = {
    "OpenGL", // GxApi_OpenGl
    "D3D9",   // GxApi_D3d9
    "D3D9Ex", // GxApi_D3d9Ex
    "D3D10",  // GxApi_D3d10
    "D3D11",  // GxApi_D3d11
    "GLL",    // GxApi_GLL
    "GLSDL"   // GxApi_GLSDL
};

EGxApi g_gxApiSupported[] = {
#if defined(WHOA_SYSTEM_WIN)
    GxApi_D3d9,
#endif

#if defined(WHOA_SYSTEM_MAC)
    GxApi_GLL,
#endif

#if defined(WHOA_BUILD_GLSDL)
    GxApi_GLSDL,
#endif
};

size_t g_numGxApiSupported = sizeof(g_gxApiSupported) / sizeof(EGxApi);


bool CVGxWindowResizeLockCallback(CVar*, const char*, const char*, void*) {
    // TODO
    return true;
}

bool GxVideoOptionsVersionCallback(CVar*, const char*, const char*, void*) {
    return true;
}

bool CVGxMaxFPSBkCallback(CVar*, const char*, const char*, void*) {
    // TODO
    return true;
}

bool CVGxMaxFPSCallback(CVar*, const char*, const char*, void*) {
    // TODO
    return true;
}

bool CVGxOverrideCallback(CVar*, const char*, const char*, void*) {
    // TODO
    return true;
}

bool CVGxStereoEnabledCallback(CVar*, const char*, const char*, void*) {
    // TODO
    return true;
}

bool CVGxFixLagCallback(CVar*, const char*, const char*, void*) {
    // TODO
    return true;
}

bool CVGxMultisampleQualityCallback(CVar*, const char*, const char*, void*) {
    // TODO
    return true;
}

bool CVGxMultisampleCallback(CVar*, const char*, const char*, void*) {
    // TODO
    return true;
}

bool CVGxCursorCallback(CVar*, const char*, const char* value, void*) {
    s_requestedFormat.hwCursor = SStrToInt(value) != 0;
    ConsoleWrite("set pending gxRestart", DEFAULT_COLOR);
    return true;
}

bool CVGxAspectCallback(CVar*, const char*, const char*, void*) {
    // TODO
    return true;
}

bool CVGxVSyncCallback(CVar*, const char*, const char*, void*) {
    // TODO
    return true;
}

bool CVGxTripleBufferCallback(CVar*, const char*, const char*, void*) {
    // TODO
    return true;
}

bool CVGxRefreshCallback(CVar*, const char*, const char*, void*) {
    // TODO
    return true;
}

bool CVGxDepthBitsCallback(CVar*, const char*, const char*, void*) {
    // TODO
    return true;
}

bool CVGxColorBitsCallback(CVar*, const char*, const char*, void*) {
    // TODO
    return true;
}

bool CVGxMaximizeCallback(CVar*, const char*, const char*, void*) {
    // TODO
    return true;
}

bool CVGxResolutionCallback(CVar*, const char*, const char*, void*) {
    // static C2iVector legalSizes[] = {
    //     {}
    // }

    // TODO
    return true;
}

bool CVGxWindowCallback(CVar*, const char*, const char*, void*) {
    // TODO
    return true;
}

bool CVGxApiCallback(CVar* h, const char* oldValue, const char* newValue, void* arg) {
    for (size_t api = 0; api < g_numGxApiSupported; api++) {
        auto apiString = g_gxApiNames[g_gxApiSupported[api]];
        if (SStrCmpI(newValue, apiString, STORM_MAX_STR) == 0) {
            // New gxApi is supported, pass
            ConsoleWrite("GxApi set pending gxRestart", DEFAULT_COLOR);
            return true;
        }
    }

    // Supported gxApi not supplied, show available apis
    constexpr size_t msgsize = 1024;
    char msg[msgsize] = {0};
    SStrPack(msg, "unsupported api, must be one of ", msgsize);

    for (size_t api = 0; api < g_numGxApiSupported; api++) {
        if (api > 0) {
            SStrPack(msg, ", ", msgsize);
        }
        auto apiString = g_gxApiNames[g_gxApiSupported[api]];
        SStrPack(msg, "'", msgsize);
        SStrPack(msg, apiString, msgsize);
        SStrPack(msg, "'", msgsize);
    }

    ConsoleWrite(msg, DEFAULT_COLOR);
    return false;
}

int32_t CCGxRestart(const char*, const char*) {
    // TODO
    return 1;
}

EGxApi GxApiDefault() {
#if defined(WHOA_SYSTEM_WIN)
    return GxApi_D3d9;
#endif

#if defined(WHOA_SYSTEM_MAC)
    return GxApi_GLL;
#endif

#if defined(WHOA_SYSTEM_LINUX)
    return GxApi_GLSDL;
#endif
}

void RegisterGxCVars() {
    const auto& format = s_defaults.format;

    // TODO: bool isChinese = s_currentLocaleIndex == 4 (zhCN)
    bool isChinese = false;

    const uint32_t graphics = CATEGORY::GRAPHICS;

    s_cvGxWidescreen = CVar::Register("widescreen", "Allow widescreen support", 0x0, "1", nullptr, graphics);
    s_cvGxWindow = CVar::Register("gxWindow", "toggle fullscreen/window", 0x1 | 0x2, isChinese ? "1" : "0", &CVGxWindowCallback, graphics);
    s_cvGxMaximize = CVar::Register("gxMaximize", "maximize game window", 0x1 | 0x2, isChinese ? "1" : "0", &CVGxMaximizeCallback, graphics);

    char value[260] = {};
    SStrPrintf(value, sizeof(value), "%s", CGxFormat::formatToColorBitsString[format.colorFormat]);
    s_cvGxColorBits = CVar::Register("gxColorBits", "color bits", 0x1 | 0x2, value, &CVGxColorBitsCallback, graphics);

    SStrPrintf(value, sizeof(value), "%s", CGxFormat::formatToColorBitsString[format.depthFormat]);
    s_cvGxDepthBits = CVar::Register("gxDepthBits", "depth bits", 0x1 | 0x2, value, &CVGxDepthBitsCallback, graphics);

    SStrPrintf(value, 260, "%dx%d", format.size.x, format.size.y);
    s_cvGxResolution = CVar::Register("gxResolution", "resolution", 0x1 | 0x2, value, &CVGxResolutionCallback, graphics);

    s_cvGxRefresh = CVar::Register("gxRefresh", "refresh rate", 0x1 | 0x2, "75", &CVGxRefreshCallback, graphics);
    s_cvGxTripleBuffer = CVar::Register("gxTripleBuffer", "triple buffer", 0x1 | 0x2, "0", &CVGxTripleBufferCallback, graphics);
    s_cvGxApi = CVar::Register("gxApi", "graphics api", 0x1 | 0x2, g_gxApiNames[GxApiDefault()], &CVGxApiCallback, graphics);

    s_cvGxVSync = CVar::Register("gxVSync", "vsync on or off", 0x1 | 0x2, "1", &CVGxVSyncCallback, graphics);
    s_cvGxAspect = CVar::Register("gxAspect", "constrain window aspect", 0x1 | 0x2, "1", &CVGxAspectCallback, graphics);

    s_cvGxCursor = CVar::Register("gxCursor", "toggle hardware cursor", 0x1 | 0x2, "1", &CVGxCursorCallback, graphics);

    // TODO: v10 = *(_DWORD*)(dword_CABB60 + 84);
    int v10 = 0;
    SStrPrintf(value, sizeof(value), "%d", v10);
    s_cvGxMultisample = CVar::Register("gxMultisample", "multisample", 0x1 | 0x2, value, &CVGxMultisampleCallback, graphics);
    s_cvGxMultisampleQuality = CVar::Register("gxMultisampleQuality", "multisample quality", 0x1 | 0x2, "0.0", &CVGxMultisampleQualityCallback, graphics);

    // TODO: v10 = *(_DWORD*)(dword_CABB60 + 80);
    SStrPrintf(value, sizeof(value), "%d", v10);
    s_cvGxFixLag = CVar::Register("gxFixLag", "prevent cursor lag", 0x1 | 0x2, value, &CVGxFixLagCallback, graphics);
    s_cvGxStereoEnabled = CVar::Register("gxStereoEnabled", "Enable stereoscopic rendering", 0x1, "0", &CVGxStereoEnabledCallback, graphics);
    s_cvGxOverride = CVar::Register("gxOverride", "gx overrides", 0x1, "", &CVGxOverrideCallback, graphics);
    s_cvGxMaxFPS = CVar::Register("maxFPS", "Set FPS limit", 0x1, "200", &CVGxMaxFPSCallback, graphics);
    s_cvGxMaxFPSBk = CVar::Register("maxFPSBk", "Set background FPS limit", 0x1, "30", &CVGxMaxFPSBkCallback, graphics);
    s_cvGxVideoOptionsVersion = CVar::Register("videoOptionsVersion", "Video options version", 0x1 | 0x2, "0", &GxVideoOptionsVersionCallback, graphics);
    s_cvGxWindowResizeLock = CVar::Register("windowResizeLock", "prevent resizing in windowed mode", 1, "0", &CVGxWindowResizeLockCallback, graphics);
    s_cvGxFixedFunction = CVar::Register("fixedFunction", "Force fixed function rendering", 0x1 | 0x2, "0", 0, graphics);
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
    char value[1024] = {};

    s_cvGxColorBits->Set(CGxFormat::formatToColorBitsString[format.colorFormat], true, false, false, true);
    s_cvGxDepthBits->Set(CGxFormat::formatToColorBitsString[format.depthFormat], true, false, false, true);

    SStrPrintf(value, sizeof(value), "%d", format.window);
    s_cvGxWindow->Set(value, true, false, false, true);

    SStrPrintf(value, sizeof(value), "%dx%d", format.size.x, format.size.y);
    s_cvGxResolution->Set(value, true, false, false, true);

    SStrPrintf(value, sizeof(value), "%d", format.refreshRate);
    s_cvGxRefresh->Set(value, true, false, false, true);

    // TODO: (format + 28) > 1
    s_cvGxTripleBuffer->Set("0", true, false, false, true);

    SStrPrintf(value, sizeof(value), "%d", format.vsync);
    s_cvGxVSync->Set(value, true, false, false, true);

    // TODO: format.aspectRatio
    SStrPrintf(value, sizeof(value), "%d", 0);
    s_cvGxAspect->Set(value, true, false, false, true);

    SStrPrintf(value, sizeof(value), "%d", format.maximize);
    s_cvGxMaximize->Set(value, true, false, false, true);

    SStrPrintf(value, sizeof(value), "%d", format.hwCursor);
    s_cvGxCursor->Set(value, true, false, false, true);

    SStrPrintf(value, sizeof(value), "%d", format.sampleCount);
    s_cvGxMultisample->Set(value, true, false, false, true);

    // TODO: format.multisampleQuality
    SStrPrintf(value, sizeof(value), "%f", 0.0f);
    s_cvGxMultisampleQuality->Set(value, true, false, false, true);

    SStrPrintf(value, sizeof(value), "%d", format.fixLag);
    s_cvGxFixLag->Set(value, true, false, false, true);

    UpdateGxCVars();
}

void ConsoleDeviceInitialize(const char* title) {
    GxLogOpen();

    s_cvHwDetect = CVar::Register("hwDetect", "do hardware detection", 0x1, "1", nullptr, CATEGORY::GRAPHICS);

    // TODO: sub_76BA30(&unk_CABB38, &byte_CABCBD); << ConsoleDetect
    // TODO: byte_CABCBC = 1;

    if (CmdLineGetBool(WOWCMD_HW_DETECT) || s_cvHwDetect->GetInt() != 0) {
        s_hwDetect = true;
        s_cvHwDetect->Set("0", true, false, false, true);
    } else {
        s_hwDetect = false;
    }


    ConsoleAccessSetEnabled(CmdLineGetBool(WOWCMD_CONSOLE));

    // TODO: sub_76B520(&unk_CABAF0, &unk_CABB38);

    // CHANGE: Remove this when the rest will be ready
    s_defaults.format.size.x = 1024;
    s_defaults.format.size.y = 768;
    s_defaults.format.colorFormat = CGxFormat::Fmt_Argb8888;
    s_defaults.format.depthFormat = CGxFormat::Fmt_Ds248;

    RegisterGxCVars();
    ConsoleCommandRegister("gxRestart", &CCGxRestart, CATEGORY::GRAPHICS, nullptr);

    // TODO: GxAdapterMonitorModes((int)&unk_CABCC8);
    // TODO: ValidateFormatMonitor(&unk_CABDA8);

    // TODO: if ( GxAdapterDesktopMode(&v28) )
    if (true) {
        s_requestedFormat.size.x = 1024;
        s_requestedFormat.size.y = 768;
        s_requestedFormat.colorFormat = CGxFormat::Fmt_Argb8888;
        s_requestedFormat.depthFormat = CGxFormat::Fmt_Ds248;
    }

    GxLog("ConsoleDeviceInitialize(): hwDetect = %d, hwChanged = %d", s_hwDetect, s_hwChanged);

    if (CmdLineGetBool(WOWCMD_RES_800x600)) {
        s_requestedFormat.size.x = 800;
        s_requestedFormat.size.y = 600;
    } else if (CmdLineGetBool(WOWCMD_RES_1024x768)) {
        s_requestedFormat.size.x = 1024;
        s_requestedFormat.size.y = 768;
    } else if (CmdLineGetBool(WOWCMD_RES_1280x960)) {
        s_requestedFormat.size.x = 1280;
        s_requestedFormat.size.y = 960;
    } else if (CmdLineGetBool(WOWCMD_RES_1280x1024)) {
        s_requestedFormat.size.x = 1280;
        s_requestedFormat.size.y = 1024;
    } else if (CmdLineGetBool(WOWCMD_RES_1600x1200)) {
        s_requestedFormat.size.x = 1600;
        s_requestedFormat.size.y = 1200;
    }

    if (s_cvGxFixedFunction->GetInt() != 0) {
        // TODO: (dword_CABD20 = 0) s_requestedFormat.unknown_field = 0;
        s_requestedFormat.pos.y = 0; // <--- CHECK THIS
        s_requestedFormat.pos.x = 0;
    }

    if (s_hwDetect || s_hwChanged) {
        // TODO Sub76B3F0(&UnkCABAF0, &UnkCABB38);
        s_cvGxFixedFunction->Set("0", true, false, false, true);
        // TODO memcpy(&s_requestedFormat, &s_defaults.format, sizeof(s_requestedFormat));

        s_requestedFormat.window = s_cvGxWindow->GetInt() != 0;
        s_requestedFormat.maximize = s_cvGxMaximize->GetInt() != 0;

        // TODO temporary override
        s_requestedFormat.maximize = 0;

        SetGxCVars(s_requestedFormat);
    }

    EGxApi api = GxApiDefault();

    auto gxApiName = s_cvGxApi->GetString();

    auto gxOverride = CmdLineGetString(WOWCMD_GX_OVERRIDE);
    if (*gxOverride != '\0') {
        gxApiName = gxOverride;
    } else if (CmdLineGetBool(CMD_OPENGL)) {
        gxApiName = g_gxApiNames[GxApi_OpenGl];
    } else if (CmdLineGetBool(CMD_D3D)) {
        gxApiName = g_gxApiNames[GxApi_D3d9];
    } else if (CmdLineGetBool(CMD_D3D9EX)) {
        gxApiName = g_gxApiNames[GxApi_D3d9Ex];
    }

    // Sanitize chosen gxApi against list of supported gxApis
    for (size_t i = 0; i < g_numGxApiSupported; i++) {
        EGxApi supportedApi = g_gxApiSupported[i];
        if (SStrCmpI(gxApiName, g_gxApiNames[supportedApi], STORM_MAX_STR) == 0) {
            api = supportedApi;
            break;
        }
    }

    s_requestedFormat.fixLag = s_cvGxFixLag->GetInt() != 0;
    s_requestedFormat.hwTnL = !CmdLineGetBool(CMD_SW_TNL);

    bool windowed = s_cvGxWindow->GetInt() != 0;
    if (CmdLineGetBool(CMD_FULL_SCREEN)) {
        windowed = false;
    } else if (CmdLineGetBool(WOWCMD_WINDOWED)) {
        windowed = true;
    }

    s_requestedFormat.window = windowed;
    // TODO: byte_CABD47 = windowed;

    GxLog("GxApi_%s selected\n", g_gxApiNames[api]);

    // Set internally (CVar value reflects the current gxApi at launch),
    // this will not Set() as CVar gxApi is latched
    s_cvGxApi->InternalSet(g_gxApiNames[api], true, false, false, true);

    CGxFormat format;
    memcpy(&format, &s_requestedFormat, sizeof(s_requestedFormat));

    CGxDevice* device = GxDevCreate(api, OsWindowProc, format);

    // TODO

    auto gxWindow = GxDevWindow();
    OsGuiSetGxWindow(gxWindow);

    // TODO
}
