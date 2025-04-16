#include "client/Client.hpp"
#include "async/AsyncFile.hpp"
#include "client/ClientServices.hpp"
#include "client/CmdLine.hpp"
#include "client/ClientHandlers.hpp"
#include "console/CVar.hpp"
#include "console/Client.hpp"
#include "console/Device.hpp"
#include "console/Screen.hpp"
#include "console/Command.hpp"
#include "console/Console.hpp"
#include "db/Db.hpp"
#include "db/Startup_Strings.hpp"
#include "glue/CGlueMgr.hpp"
#include "gameui/CGGameUI.hpp"
#include "gx/Screen.hpp"
#include "gx/Texture.hpp"
#include "model/Model2.hpp"
#include "net/Poll.hpp"
#include "ui/FrameScript.hpp"
#include "ui/FrameXML.hpp"
#include "world/World.hpp"
#include "util/Filesystem.hpp"
#include <bc/Debug.hpp>
#include <common/Prop.hpp>
#include <common/Time.hpp>
#include <common/Processor.hpp>
#include <storm/Error.hpp>
#include <storm/Log.hpp>
#include <storm/Registry.hpp>
#include <storm/Option.hpp>
#include <bc/os/Path.hpp>
#include <bc/File.hpp>
#include <cstdio>

CVar* Client::g_accountNameVar;
CVar* Client::g_accountListVar;
CVar* Client::g_accountUsesTokenVar;
CVar* Client::g_movieVar;
CVar* Client::g_expansionMovieVar;
CVar* Client::g_movieSubtitleVar;


HEVENTCONTEXT Client::g_clientEventContext;
char Client::g_currentLocaleName[5] = {};


static uint8_t s_expansionLevel;
static bool g_hasIsoLocale[12];
static const char* s_localeArray[12] = {
    "deDE", "enGB", "enUS", "esES", "frFR", "koKR",
    "zhCN", "zhTW", "enCN", "enTW", "esMX", "ruRU"
};

static int32_t s_timeTestError;

int32_t CCommand_ReloadUI(const char*, const char*) {
    CGlueMgr::m_reload = 1;
    // CGGameUI::Reload();
    return 1;
}

int32_t CCommand_Perf(const char*, const char*) {
    return 1;
}

#if defined(WHOA_SYSTEM_WIN)

int32_t CCommand_TimingInfo(const char* command, const char* arguments) {
    auto desiredTimingMethod = static_cast<TimingMethod>(CVar::LookupRegistered("timingMethod")->GetInt());
    auto timingTestError = CVar::LookupRegistered("timingTestError")->GetInt();
    auto selectedTimingMethod = OsTimeGetTimingMethod();

    ConsolePrintf("Timing method desired: %d - %s", desiredTimingMethod, OsTimeGetTimingMethodName(desiredTimingMethod));
    ConsolePrintf("Timing method selected: %d - %s", selectedTimingMethod, OsTimeGetTimingMethodName(selectedTimingMethod));

    ConsolePrintf("Timing test error: %d", timingTestError);
    return 1;
}

#endif

void AsyncFileInitialize() {
    // TODO
    AsyncFileReadInitialize(0, 100);
}

void BaseInitializeGlobal() {
    PropInitialize();
}

void ClientMiscInitialize() {
    // TODO
}

void ClientRegisterConsoleCommands() {
    ConsoleCommandRegister("reloadUI", CCommand_ReloadUI, GRAPHICS, nullptr);
    ConsoleCommandRegister("perf",     CCommand_Perf,     DEBUG,    nullptr);

    Client::g_accountNameVar = CVar::Register(
        "accountName",
        "Saved account name",
        64,
        "",
        nullptr,
        GAME,
        false,
        nullptr,
        false
    );

    Client::g_accountListVar = CVar::Register(
        "accountList",
        "List of wow accounts for saved Blizzard account",
        0,
        "",
        nullptr,
        GAME,
        false,
        nullptr,
        false
    );

    Client::g_accountUsesTokenVar = CVar::Register(
        "g_accountUsesToken",
        "Saved whether uses authenticator",
        0,
        "0",
        nullptr,
        GAME,
        false,
        nullptr,
        false
    );

    Client::g_movieVar = CVar::Register(
        "movie",
        "Show movie on startup",
        0,
        "1",
        nullptr,
        GAME,
        false,
        nullptr,
        false
    );

    Client::g_expansionMovieVar = CVar::Register(
        "expansionMovie",
        "Show expansion movie on startup",
        0,
        "1",
        nullptr,
        GAME,
        false,
        nullptr,
        false
    );
    Client::g_movieSubtitleVar = CVar::Register(
        "movieSubtitle",
        "Show movie subtitles",
        0,
        "0",
        nullptr,
        GAME,
        false,
        nullptr,
        false
    );

    // TODO
}

void ClientPostClose(int32_t a1) {
    // TODO s_finalDialog = a1;
    EventPostCloseEx(nullptr);
}

int32_t DestroyEngineCallback(const void* a1, void* a2) {
    // TODO
    return 1;
}

int32_t InitializeEngineCallback(const void* a1, void* a2) {
    // TODO
    // sub_4D2A30();

    AsyncFileInitialize();
    TextureInitialize();

    // ModelBlobLoad("world\\model.blob");

    // if (SFile::IsStreamingMode()) {
    //     TextureLoadBlob("world\\liquid.tex");
    // }

    ScrnInitialize(0);
    ConsoleScreenInitialize(nullptr); // TODO argument

    // s_cvarTextureFilteringMode = CVar::Register(
    //     "textureFilteringMode",
    //     "Texture filtering mode",
    //     1,
    //     "1",
    //     &TextureFilteringCallback,
    //     1,
    //     0,
    //     0,
    //     0
    // );

    // s_cvarUIFaster = CVar::Register(
    //     "UIFaster",
    //     "UI acceleration option",
    //     0,
    //     "3",
    //     &UIFasterCalllback,
    //     1,
    //     0,
    //     0,
    //     0
    // );

    // s_cvarTextureCacheSize = CVar::Register(
    //     "textureCacheSize",
    //     "Texture cache size in bytes",
    //     1,
    //     "32",
    //     &TextureCacheSizeCallback,
    //     1,
    //     0,
    //     0,
    //     0
    // );

    // sub_4B6580(*(_DWORD *)(dword_B2F9FC + 48) << 20);

    // AddConsoleDeviceDefaultCallback(SetDefaults);

    // if (ConsoleDeviceHardwareChanged()) {
    //     v3 = 0;

    //     do {
    //         SetDefaults(v3++);
    //     } while (v3 < 3);
    // }

    auto m2Flags = M2RegisterCVars();
    M2Initialize(m2Flags, 0);

    // v4 = *(_DWORD *)(dword_B2FA00 + 48);
    // sub_4B61C0(dword_AB6128[v4]);
    // sub_4B6230(dword_AB6140[v4]);

    WowClientInit();

    return 1;
}

uint8_t GetExpansionLevel() {
    return s_expansionLevel;
}

const char* UpdateInstallLocation() {
    // TODO
    return nullptr;
}

bool UpdateInstallLocationForName(int32_t a1, size_t size, const char* filename, char* buffer, const char* locale) {
    if (a1 == 2) {
        auto location = UpdateInstallLocation();
        if (!location) {
            return false;
        }
        SStrPrintf(buffer, size, "%s%s%s", location, "Data\\", filename);
    } else {
        SStrPrintf(buffer, size, "%s%s", "Data\\", filename);
    }
    for (auto i = SStrStr(buffer, "****"); i; i = SStrStr(buffer, "****")) {
        size_t offset = static_cast<size_t>(i - buffer);
        memcpy(&buffer[offset], locale, 4);
    }
    return true;
}

void SetPaths() {
    // SFile::DisableSFileCheckDisk();
    // SFile::EnableDirectAccess(0);

    char buffer[STORM_MAX_PATH] = {0};

    const char* datadir = CmdLineGetString(CMD_DATA_DIR);
    if (*datadir == '\0') {
        OsGetExePath(buffer, STORM_MAX_PATH);
        datadir = buffer;
    }

    SLogSetDefaultDirectory(datadir);
    SFile::SetBasePath(datadir);
    SFile::SetDataPath("Data\\");

    OsSetCurrentDirectory(datadir);
}

bool IsCommonMpqExists() {
    char path1[1024];
    SStrPrintf(path1, sizeof(path1), "%s%s", "Data\\", "common.MPQ");
    for (auto i = SStrStr(path1, "****"); i; i = SStrStr(path1, "****")) {
        size_t offset = static_cast<size_t>(i - path1);
        memcpy(&path1[offset], "----", 4);
    }

    char path2[1024];
    SStrPrintf(path2, sizeof(path2), "%s%s", "..\\Data\\", "common.MPQ");
    for (auto i = SStrStr(path2, "****"); i; i = SStrStr(path2, "****")) {
        size_t offset = static_cast<size_t>(i - path2);
        memcpy(&path2[offset], "----", 4);
    }

    auto location = UpdateInstallLocation();
    if (location) {
        char path3[1024];
        SStrPrintf(path3, sizeof(path3), "%s%s%s", location, "Data\\", "common.MPQ");
        for (auto i = SStrStr(path3, "****"); i; i = SStrStr(path3, "****")) {
            size_t offset = static_cast<size_t>(i - path3);
            memcpy(&path3[offset], "----", 4);
        }

        if (!Blizzard::File::Exists(path1) && !Blizzard::File::Exists(path2)) {
            return Blizzard::File::Exists(path3);
        }
    } else if (!Blizzard::File::Exists(path1)) {
        return Blizzard::File::Exists(path2);
    }

    return true;
}

size_t GetLocaleIndex(const char* locale) {
    for (size_t i = 0; i < 12; ++i) {
        if (SStrCmpI(locale, s_localeArray[i], 4) == 0) {
            return i;
        }
    }
    return 2; // s_localeArray[2] == "enUS"
}

void CheckAvailableLocales(char* locale) {
    if (!IsCommonMpqExists()) {
        return;
    }

    for (size_t localeIndex = 0; localeIndex < 12; ++localeIndex) {
        g_hasIsoLocale[localeIndex] = false;

        const char* filename = "****\\locale-****.MPQ";

        char path[1024];
        SStrPrintf(path, sizeof(path), "%s%s", "Data\\", filename);
        for (auto i = SStrStr(path, "****"); i; i = SStrStr(path, "****")) {
            size_t offset = static_cast<size_t>(i - path);
            memcpy(&path[offset], s_localeArray[localeIndex], 4);
        }

        if (Blizzard::File::Exists(path)) {
            g_hasIsoLocale[localeIndex] = true;
            continue;
        }

        SStrPrintf(path, sizeof(path), "%s%s", "..\\Data\\", filename);
        for (auto i = SStrStr(path, "****"); i; i = SStrStr(path, "****")) {
            size_t offset = static_cast<size_t>(i - path);
            memcpy(&path[offset], s_localeArray[localeIndex], 4);
        }

        if (Blizzard::File::Exists(path)) {
            g_hasIsoLocale[localeIndex] = true;
            continue;
        }

        if (UpdateInstallLocationForName(2, sizeof(path), filename, path, s_localeArray[localeIndex]) &&
            Blizzard::File::Exists(path)) {
            g_hasIsoLocale[localeIndex] = true;
        }
    }

    size_t localeIndex = GetLocaleIndex(locale);
    for (size_t i = 0; i < 12; ++i) {
        if (g_hasIsoLocale[localeIndex]) {
            break;
        }
        localeIndex = (localeIndex + 1) % 12;
    }
    SStrCopy(locale, s_localeArray[localeIndex], STORM_MAX_STR);
}

bool LocaleChangedCallback(CVar*, const char*, const char* value, void*) {
    SStrCopy(Client::g_currentLocaleName, value, sizeof(Client::g_currentLocaleName));
    return true;
}

#if defined(WHOA_SYSTEM_WIN)

bool TimingMethodCallback(CVar* h, const char* oldValue, const char* newValue, void* param) {
    auto cv = static_cast<CVar*>(param);
    auto newMethod = static_cast<TimingMethod>(atol(newValue));
    if (newMethod < TimingMethods) {
        if (oldValue) {
            auto oldMethod = static_cast<TimingMethod>(atol(oldValue));
            if ((newMethod != oldMethod) && cv->GetInt()) {
                cv->SetReadOnly(false);
                cv->Set("0", true, false, false, true);
                cv->SetReadOnly(true);
            }
        }
        return true;
    }

    ConsolePrintf("\'%s\' is not a valid timing method. Valid methods are:", newValue);
    auto method = Timing_BestAvailable;
    while (method < TimingMethods) {
        ConsolePrintf("  %d - %s", method, OsTimeGetTimingMethodName(method));
        method = static_cast<TimingMethod>(static_cast<int32_t>(method) + 1);
    }
    return false;
}

#endif

int32_t InitializeGlobal() {
    ProcessCommandLine();
    SetPaths();

    // TODO:
    // WowConfigureFileSystem::ReadBuildKeyFromFile("WoW.mfil");

    // if (dword_B2FA10 != 2) {
    //     sub_403560();
    // }

    // LOBYTE(v24) = 0;

    // if (sub_422140()) {
    //     LOBYTE(v24) = OsDirectoryExists((int)"WTF/Account") == 0;
    // }

    ClientServices::LoadCDKey();

    ConsoleInitializeClientCommand();
    ConsoleInitializeClientCVar("Config.wtf");
    // TODO: CVar::ArchiveCodeRegisteredOnly();

    // v18 = 0;
    // v19 = 0;
    // ptr = 0;
    // v21 = 0;

    // ::ForEveryRunOnceWTF::Execute(&v18, &CVar::Load);

    // if (ptr) {
    //     SMemFree(ptr, a_pad, -2, 0);
    // }

    CVar::Register(
        "dbCompress",
        "Database compression",
        0,
        "-1",
        nullptr,
        CATEGORY::DEFAULT,
        false,
        nullptr,
        false
    );

    CVar* locale = CVar::Register(
        "locale",
        "Set the game locale",
        0,
        "****",
        &LocaleChangedCallback,
        CATEGORY::DEFAULT,
        false,
        nullptr,
        false
    );

    if (!SStrCmp(locale->GetString(), "****", STORM_MAX_STR)) {
        locale->Set("enUS", true, false, false, true);
    }

    CVar::Register(
        "useEnglishAudio",
        "override the locale and use English audio",
        0,
        "0",
        nullptr,
        CATEGORY::DEFAULT,
        false,
        nullptr,
        false
    );

    // TODO: SFile::IsTrial() check
    // if (sub_422140()) {
    //     sub_4036B0(v24, 0, a2, (int)v2, (char)v24);
    // }

    char existingLocale[5] = {};
    SStrCopy(existingLocale, locale->GetString(), sizeof(existingLocale));
    CheckAvailableLocales(existingLocale);
    locale->Set(existingLocale, true, false, false, true);

    char path[STORM_MAX_PATH];
    SStrPrintf(path, sizeof(path), "%s%s", "Data\\", locale->GetString());
    SFile::SetDataPathAlternate(path);
    SFile::RebuildHash();


    OpenArchives();

    // TODO: This method should be placed inside OpenArchives
    ClientServices::InitLoginServerCVars(1, locale->GetString());

    // sub_405DD0();

    // CVar* v3 = CVar::Register(
    //     "processAffinityMask",
    //     "Sets which core(s) WoW may execute on - changes require restart to take effect",
    //     2,
    //     "0",
    //     &sub_4022E0,
    //     0,
    //     0,
    //     0,
    //     0
    // );

    // CVar* v4 = CVar::Lookup("videoOptionsVersion");

    // if (!v4 || v4->m_intValue < 3) {
    //     SStrPrintf(v23, 8, "%u", 0);
    //     CVar::Set(v3, v23, 1, 0, 0, 1);
    //     CVar::Update((int)v3);
    // }

    // v5 = v3->m_intValue;

    // if (v5) {
    //     SSetCurrentProcessAffinityMask(v5);
    // }

    BaseInitializeGlobal();

    EventInitialize(1, 0);

#if defined(WHOA_SYSTEM_WIN)

    auto cvTimingTestError = CVar::Register(
        "timingTestError",
        "Error reported by the timing validation system",
        0x2 | 0x4,
        "0",
        0,
        DEFAULT,
        false,
        nullptr,
        false
    );
    auto cvTimingMethod = CVar::Register(
        "timingMethod",
        "Desired method for game timing",
        0x2,
        "0",
        TimingMethodCallback,
        DEFAULT,
        false,
        cvTimingTestError,
        false
    );
    OsTimeStartup(static_cast<TimingMethod>(cvTimingMethod->GetInt()));
    ConsoleCommandRegister("timingInfo", CCommand_TimingInfo, DEBUG, nullptr);
    s_timeTestError = OsTimeGetTestError();
    if (s_timeTestError != cvTimingTestError->GetInt()) {
        char value[16];
        sprintf(value, "%d", s_timeTestError);
        cvTimingTestError->SetReadOnly(false);
        cvTimingTestError->Set(value, true, false, false, true);
        cvTimingTestError->Update();
        cvTimingTestError->SetReadOnly(true);
        ConsolePrintf("Timing test error: %d", s_timeTestError);
    }

#else

    OsTimeStartup(Timing_BestAvailable);

#endif

    g_Startup_StringsDB.Load(__FILE__, __LINE__);

    auto titleRecord = g_Startup_StringsDB.GetRecord(MSG_TITLE_WOW);
    auto title = titleRecord ? titleRecord->m_message : "World of Warcraft";
    char v15[260];
    SStrCopy(v15, title, 0x7FFFFFFF);

    ConsoleDeviceInitialize(v15);

    // OsIMEInitialize();

    // uint32_t v13 = OsGetAsyncTimeMs();
    // g_rndSeed.SetSeed(v13);

    Client::g_clientEventContext = EventCreateContextEx(
        1,
        &InitializeEngineCallback,
        &DestroyEngineCallback,
        0,
        0
    );

    return 1;
}

void DestroyGlobal() {
    // TODO

    OsTimeShutdown();
    EventDestroy();
    ConsoleDeviceDestroy();
    CVar::Destroy();

    // TODO
}

void CommonMain() {
    StormInitialize();

    // TODO:
    // SErrCatchUnhandledExceptions();
    // OsSystemInitialize("Blizzard Entertainment World of Warcraft", 0);
    int32_t option = 1;
    StormSetOption(10, &option, sizeof(option));
    StormSetOption(11, &option, sizeof(option));

    // QoL: enable debug logs
#if !defined(NDEBUG)
    option = 1;
    StormSetOption(5, &option, sizeof(option));
#endif

    OsSystemEnableCpuLog();

    // SetPaths() moved into InitializeGlobal()

    uint32_t sendErrorLogs = 1;
    if (!SRegLoadValue("World of Warcraft\\Client", "SendErrorLogs", 0, &sendErrorLogs)) {
        sendErrorLogs = 1;
        SRegSaveValue("World of Warcraft\\Client", "SendErrorLogs", 0, sendErrorLogs);
    }

    // SErrSetLogTitleString("World of WarCraft (build 12340)");
    // SErrSetLogTitleCallback(WowLogHeader);
    // if (sendErrorLogs) {
    //     SErrRegisterHandler(SendErrorLog);
    // }

    if (InitializeGlobal()) {
        EventDoMessageLoop();
        DestroyGlobal();
    }

    // TODO:
    // StormDestroy();
    // Misc Cleanup
}

void BlizzardAssertCallback(const char* a1, const char* a2, const char* a3, uint32_t a4) {
    if (*a2) {
        SErrDisplayError(0, a3, a4, a2, 0, 1, 0x11111111);
    } else {
        SErrDisplayError(0, a3, a4, a1, 0, 1, 0x11111111);
    }
}

void StormInitialize() {
    // TODO
    // SStrInitialize();
    // SErrInitialize();
    SLogInitialize();
    // SFile::Initialize();

    Blizzard::Debug::SetAssertHandler(BlizzardAssertCallback);
}

void WowClientInit() {
    // TODO
    // EventRegister(EVENT_ID_5, (int)sub_4020E0);
    // _cfltcvt_init_0();

    ClientMiscInitialize();

    ClientRegisterConsoleCommands();

    ClientDBInitialize();

    // LoadingScreenInitialize();

    FrameScript_Initialize(0);

    // TODO
    // SI2::Init(0);
    // sub_6F66B0();

    FrameXML_RegisterDefault();
    GlueScriptEventsInitialize();
    ScriptEventsInitialize();

    // TODO
    // sub_6F75E0();
    // sub_401FF0();

    ClientServices::Initialize();
    // TODO ClientServices::SetMessageHandler(SMSG_TUTORIAL_FLAGS, (int)sub_530920, 0);

    // TODO
    // v2 = CVar::Lookup("EnableVoiceChat");
    // if (v2 && *(_DWORD *)(v2 + 48)) {
    //     ComSatClient_Init();
    // }

    // TODO
    // DBCache_RegisterHandlers();
    // DBCache_Initialize(a1);

    // TODO
    // sub_78E400();

    CWorld::Initialize();

    // TODO
    // ShadowInit();
    // GxuLightInitialize();
    // GxuLightBucketSizeSet(16.665001);
    // InputControlInitialize();

    CGlueMgr::Initialize();

    // TODO
    // if (GetConsoleMessage()) {
    //     v3 = (const char *)GetConsoleMessage();
    //     CGlueMgr::AddChangedOptionWarning(v3);
    //     SetConsoleMessage(0);
    // }

    // TODO
    // if (sub_422140()) {
    //     sub_421630();
    // }

    if (s_expansionLevel != 1) {
        if (Client::g_movieVar->GetInt()) {
            Client::g_movieVar->Set("0", true, false, false, true);
            CGlueMgr::SetScreen("movie");
        } else {
            CGlueMgr::SetScreen("login");
        }
    } else {
        if (Client::g_expansionMovieVar->GetInt()) {
            Client::g_expansionMovieVar->Set("0", true, false, false, true);
            Client::g_movieVar->Set("0", true, false, false, true);
            CGlueMgr::SetScreen("movie");
        } else {
            CGlueMgr::SetScreen("login");
        }
    }

    // TODO
    // CGlueMgr::m_pendingTimerAlert = dword_B2F9D8;
    // sub_7FC5A0();

    EventRegister(EVENT_ID_POLL, &PollNet);
}

void ClientInitializeGame(int32_t continentID, const C3Vector& position) {
    // TODO
    CGGameUI::InitializeGame();

    ClientServices::SetMessageHandler(SMSG_NEW_WORLD, &NewWorldHandler, nullptr);
    ClientServices::SetMessageHandler(SMSG_LOGIN_VERIFY_WORLD, &LoginVerifyWorldHandler, nullptr);

    // TODO
}
