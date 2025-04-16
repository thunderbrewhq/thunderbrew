#include "console/Device.hpp"
#include "client/CmdLine.hpp"
#include "os/Gui.hpp"
#include "console/CVar.hpp"
#include "console/Console.hpp"
#include "console/Detect.hpp"
#include "console/Gx.hpp"
#include "console/cvar/Gx.hpp"
#include "os/Input.hpp"
#include "gx/CGxFormat.hpp"
#include "gx/Device.hpp"
#include "gx/Types.hpp"
#include "console/command/Commands.hpp"
#include "db/Startup_Strings.hpp"
#include <storm/String.hpp>
#include <tempest/Vector.hpp>
#include <cstdio>
#include <cstring>

CVar* s_cvHwDetect;
DefaultSettings s_defaults;
Hardware s_hardware;
bool s_hardwareDetected;
bool s_hwChanged;
bool s_hwDetect;
TSGrowableArray<CGxMonitorMode> s_gxMonitorModes;
CGxDevice* s_device;
char s_windowTitle[256];
CGxFormat s_requestedFormat;
CGxFormat s_fallbackFormat = { 0, { 640, 480 }, CGxFormat::Fmt_Rgb565, CGxFormat::Fmt_Ds160, 60, true, true, false, true, true, false };
CGxFormat s_lastGoodFormat;
CGxFormat s_desktopFormat = { 0, { 800, 600 }, CGxFormat::Fmt_Rgb565,  CGxFormat::Fmt_Ds24X, 60, true, true, false, true, true, false };

uint32_t s_FormatTobpp[4] = {
    16,
    32,
    32,
    32
};

void OnGxStereoChanged() {
    // ???
}

void ValidateFormatMonitor(CGxFormat& fmt) {
    static C2iVector standardSizes[] = {
        { 1600, 1200 },
        { 1280, 1024 },
        { 1280, 960 },
        { 1152, 864 },
        { 1024, 768 },
        { 800,  600 },
        { 640,  480 }
    };

    auto fmtbpp = s_FormatTobpp[fmt.colorFormat];

    int32_t lowRate = 9999;

    int32_t i = 0;
    while (i < s_gxMonitorModes.Count()) {
        auto& size = s_gxMonitorModes[i].size;

        if (fmt.size.x == size.x && fmt.size.y == size.y && fmtbpp == s_gxMonitorModes[i].bpp) {
            uint32_t refreshRate = s_gxMonitorModes[i].refreshRate;
            if (refreshRate < lowRate) {
                lowRate = refreshRate;
            }
            if (fmt.refreshRate == refreshRate) {
                return;
            }
        }

        i++;
    }

    auto rate = lowRate;
    if (lowRate == 9999) {
        GxLog("ValidateFormatMonitor(): unable to find monitor refresh");
        rate = 60;
    }

    GxLog("ValidateFormatMonitor(): invalid refresh rate %d, set to %d", fmt.refreshRate, rate);
    fmt.refreshRate = rate;
}

void ConsoleDeviceStereoInitialize() {
    s_cvGxStereoConvergence = CVar::Register(
        "gxStereoConvergence",
        "Set stereoscopic rendering convergence depth",
        0x1,
        "1",
        CVGxStereoConvergenceCallback,
        GRAPHICS,
        false,
        nullptr,
        false
    );
    s_cvGxStereoSeparation = CVar::Register(
        "gxStereoSeparation",
        "Set stereoscopic rendering separation percentage",
        0x1,
        "25",
        CVGxStereoSeparationCallback,
        GRAPHICS,
        false,
        nullptr,
        false
    );

    // g_theGxDevicePtr->AddStereoChangedCallback(nullsub_3);
    GxAddStereoChangedCallback(OnGxStereoChanged);
}

void ConsoleDeviceInitialize(const char* title) {
    GxLogOpen();

    s_cvHwDetect = CVar::Register(
        "hwDetect",
        "do hardware detection",
        0x1,
        "1",
        nullptr,
        GRAPHICS,
        false,
        nullptr,
        false
    );

    ConsoleDetectDetectHardware(s_hardware, s_hwChanged);
    s_hardwareDetected = true;

    if (CmdLineGetBool(CMD_HW_DETECT) == 1 || s_cvHwDetect->GetInt() != 0) {
        s_hwDetect = true;
        s_cvHwDetect->Set("0", true, false, false, true);
    } else {
        s_hwDetect = false;
    }

    ConsoleAccessSetEnabled(CmdLineGetBool(CMD_CONSOLE) == 1);

    ConsoleDetectSetDefaultsFormat(s_defaults, s_hardware);

    RegisterGxCVars();

    ConsoleCommandRegister("gxRestart", CCGxRestart, GRAPHICS, nullptr);

    GxAdapterMonitorModes(s_gxMonitorModes);
    ValidateFormatMonitor(s_fallbackFormat);

    CGxMonitorMode mode;
    mode.size = { 0, 0 };
    if (GxAdapterDesktopMode(mode)) {
        s_desktopFormat.size = mode.size;
        s_desktopFormat.colorFormat = mode.bpp > 16 ? CGxFormat::Fmt_ArgbX888 : CGxFormat::Fmt_Rgb565;
        s_desktopFormat.refreshRate = mode.refreshRate;
    }
    GxLog("ConsoleDeviceInitialize(): hwDetect = %d, hwChanged = %d", s_hwDetect, s_hwChanged);

    if (CmdLineGetBool(CMD_RES_800x600)) {
        s_requestedFormat.size = { 800, 600 };
    } else if (CmdLineGetBool(CMD_RES_1024x768)) {
        s_requestedFormat.size = { 1024, 768 };
    } else if (CmdLineGetBool(CMD_RES_1280x960)) {
        s_requestedFormat.size = { 1280, 960 };
    } else if (CmdLineGetBool(CMD_RES_1280x1024)) {
        s_requestedFormat.size = { 1280, 1024 };
    } else if (CmdLineGetBool(CMD_RES_1600x1200)) {
        s_requestedFormat.size = { 1600, 1200 };
    }

    // TODO: fixed function rendering!!!
    if (s_cvFixedFunction->GetInt()) {
        // TODO: IMPORTANT: figure out what these are called
        s_requestedFormat.unk48 = 0;
        s_requestedFormat.unk38 = 0;
    }

    if (s_hwDetect || s_hwChanged) {
        ConsoleDetectSetDefaults(s_defaults, s_hardware);
        s_cvFixedFunction->Set("0", true, false, false, true);
        memcpy(&s_requestedFormat, s_defaults.format, sizeof(CGxFormat));
        s_requestedFormat.window = s_cvGxWindow->GetInt() != 0;
        s_requestedFormat.maximize = s_cvGxMaximize->GetInt() != 0;
        SetGxCVars(s_requestedFormat);
    }

    auto gxApi = GxDefaultApi();
    auto cvGxApi = CVar::Lookup("gxApi");
    if (cvGxApi) {
        auto requestedGxApi = cvGxApi->GetString();
        for (auto api = GxApi_OpenGl; api < GxApis_Last; api = static_cast<EGxApi>(static_cast<int32_t>(api) + 1)) {
            if (GxApiSupported(api) && !SStrCmpI(requestedGxApi, g_gxApiNames[api], STORM_MAX_STR)) {
                gxApi = api;
                break;
            }
        }
    }
    if (CmdLineGetBool(CMD_OPENGL) && GxApiSupported(GxApi_OpenGl)) {
        gxApi = GxApi_OpenGl;
    }
    if (CmdLineGetBool(CMD_D3D) && GxApiSupported(GxApi_D3d9)) {
        gxApi = GxApi_D3d9;
    }
    if (CmdLineGetBool(CMD_D3D9EX) && GxApiSupported(GxApi_D3d9Ex)) {
        gxApi = GxApi_D3d9Ex;
    }

    s_requestedFormat.fixLag = s_cvGxFixLag->GetInt() != 0;
    s_requestedFormat.hwTnL = CmdLineGetBool(CMD_SW_TNL) == 0;
    bool window = s_cvGxWindow->GetInt() != 0;
    if (CmdLineGetBool(CMD_FULL_SCREEN)) {
        window = false;
    } else if (CmdLineGetBool(CMD_WINDOWED)) {
        window = true;
    }
    s_requestedFormat.window = window;
    s_desktopFormat.window = window;

    bool bVar1 = false;
    CGxFormat apiFormat = s_requestedFormat;
    ValidateFormatMonitor(apiFormat);
    s_device = GxDevCreate(gxApi, OsWindowProc, apiFormat);
    while (!s_device) {
        if (apiFormat.sampleCount < 2) {
            auto colorFormat = apiFormat.colorFormat;
            if (colorFormat <= CGxFormat::Fmt_Rgb565) {
                if (bVar1) {
                    GxLog("ConsoleDeviceInitialize(): no output device available!");
                    auto titleRecord = g_Startup_StringsDB.GetRecord(MSG_TITLE_WOW);
                    auto title       = titleRecord ? titleRecord->m_message : "World of Warcraft";
                    const char* message;
                    if (gxApi == GxApi_D3d9 || gxApi == GxApi_D3d9Ex) {
                        auto messageRecord = g_Startup_StringsDB.GetRecord(MSG_GX_INIT_FAILED_D3D);
                        message = messageRecord ? messageRecord->m_message : "World of Warcraft was unable to start up 3D acceleration. Please make sure DirectX 9.0c is installed and your video drivers are up-to-date.";
                    } else {
                        auto messageRecord = g_Startup_StringsDB.GetRecord(MSG_GX_INIT_FAILED);
                        message = messageRecord ? messageRecord->m_message : "World of Warcraft was unable to start up 3D acceleration.";
                    }
                    OsGuiMessageBox(nullptr, 0, message, title);
                    GxLogClose();
                    exit(0);
                }

                apiFormat = s_desktopFormat;
                bVar1 = true;
            } else if (apiFormat.depthFormat <= CGxFormat::Fmt_Ds160) {
                apiFormat.colorFormat = static_cast<CGxFormat::Format>(static_cast<int32_t>(apiFormat.colorFormat - 1));
                apiFormat.depthFormat = colorFormat != CGxFormat::Fmt_ArgbX888 ? CGxFormat::Fmt_Ds320 : CGxFormat::Fmt_Ds160;
            } else {
                apiFormat.depthFormat = static_cast<CGxFormat::Format>(static_cast<int32_t>(apiFormat.depthFormat - 1));
            }
        } else {
            apiFormat.sampleCount = std::max(apiFormat.sampleCount - 2, static_cast<uint32_t>(1));
        }

        ValidateFormatMonitor(apiFormat);
        s_device = GxDevCreate(gxApi, OsWindowProc, apiFormat);
    }
    memcpy(&s_requestedFormat, &apiFormat, sizeof(CGxFormat));
    memcpy(&s_lastGoodFormat, &apiFormat, sizeof(CGxFormat));

    SetGxCVars(apiFormat);

    if (GxCaps().m_numTmus < 2) {
        GxDevDestroy(s_device);
        GxLog("ConsoleDeviceInitialize(): output device does not have dual TMUs!");
        auto titleRecord = g_Startup_StringsDB.GetRecord(MSG_TITLE_WOW);
        auto title       = titleRecord ? titleRecord->m_message : "World of Warcraft";
        auto messageRecord = g_Startup_StringsDB.GetRecord(MSG_HW_UNSUPPORTED);
        auto message       = messageRecord ? messageRecord->m_message : "Your 3D accelerator card is not supported by World of Warcraft. Please install a 3D acceler ator card with dual-TMU support.";
        OsGuiMessageBox(nullptr, 0, message, title);
        GxLogClose();
        exit(0);
    }

    if (!GxCaps().m_numStreams) {
        GxDevDestroy(s_device);
        GxLog("ConsoleDeviceInitialize(): output device has 0 streams");
        auto titleRecord = g_Startup_StringsDB.GetRecord(MSG_TITLE_WOW);
        auto title       = titleRecord ? titleRecord->m_message : "World of Warcraft";
        auto messageRecord = g_Startup_StringsDB.GetRecord(MSG_HW_UNSUPPORTED);
        auto message       = messageRecord ? messageRecord->m_message : "Your 3D accelerator card is not supported by World of Warcraft. Please install a 3D acceler ator card with dual-TMU support.";
        OsGuiMessageBox(nullptr, 0, message, title);
        GxLogClose();
        exit(0);
    }

    switch (GxDevApi()) {
    case GxApi_OpenGl:
    case GxApi_GLL:
    case GxApi_GLSDL:
        ConsoleGxOverride(s_hardware.videoHw->m_oglOverrides);
        break;
    case GxApi_D3d9:
    case GxApi_D3d9Ex:
        ConsoleGxOverride(s_hardware.videoHw->m_d3DOverrides);
        break;
    default:
        break;
    }
    ConsoleGxOverride(CmdLineGetString(CMD_GX_OVERRIDE));
    for (auto override = GxOverride_PixelShader; override < GxOverrides_Last; override = static_cast<EGxOverride>(static_cast<int32_t>(override) + 1)) {
        if (s_consoleGxOverrideSet[override]) {
            GxDevOverride(override, s_consoleGxOverrideVal[override]);
        }
    }

    OsGuiSetGxWindow(GxDevWindow());
    if (!title) {
        title = "";
    }
    SStrCopy(s_windowTitle, title, sizeof(s_windowTitle));
    auto gxWindow = GxDevWindow();
    if (gxWindow) {
        OsGuiSetWindowTitle(gxWindow, s_windowTitle);
    }
    if (s_hwDetect || s_hwChanged) {
        // TODO: IMPORTANT: find out what the real name is
        s_defaults.unk19 = GxCaps().m_shaderTargets[GxSh_Pixel] != 0;
    }

    char videoOptionsVersion[32];
    SStrPrintf(videoOptionsVersion, sizeof(videoOptionsVersion), "%d", 3);

    s_cvVideoOptionsVersion->Set(videoOptionsVersion, true, false, false, true);

    ConsoleDeviceStereoInitialize();

    // TODO
    // OsSetSleepInBackground(1);
    // OsSetBackgroundSleepMs(250);
}

bool ConsoleDeviceExists() {
    return s_device != nullptr;
}

void ConsoleDeviceDestroy() {
    GxRemoveStereoChangedCallback(OnGxStereoChanged);
    s_cvVideoOptionsVersion->Update();
    GxDevDestroy(s_device);
    s_device = nullptr;
    GxLogClose();
}
