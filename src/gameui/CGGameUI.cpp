#include "gameui/CGGameUI.hpp"

#include <common/MD5.hpp>
#include <storm/Log.hpp>

#include "client/Client.hpp"
#include "gameui/CGWorldFrame.hpp"
#include "gx/Coordinate.hpp"
#include "gx/Device.hpp"
#include "ui/FrameScript.hpp"
#include "ui/FrameXML.hpp"
#include "glue/CGlueMgr.hpp"
#include "util/CStatus.hpp"
#include "util/SysMessage.hpp"
#include "util/SFile.hpp"


bool CGGameUI::m_reloadUI = 0;
CSimpleTop* CGGameUI::m_simpleTop = nullptr;
CSimpleFrame* CGGameUI::m_UISimpleParent = nullptr;
int32_t CGGameUI::m_hasControl = 0;
int32_t CGGameUI::m_screenWidth = 0;
int32_t CGGameUI::m_screenHeight = 0;
float CGGameUI::m_aspect = 0.0;


void CGGameUI::InitializeGame() {
    // TODO

    CGGameUI::m_hasControl = 1;
    CGGameUI::Initialize();
}

void CGGameUI::Initialize() {
    // TODO:
    // sub_4CFB80();
    // s_taintLogCVar =
    // s_scriptProfileCVar =

    //CGGameUI::s_loggingIn = 1;
    //CGGameUI::m_reloadUIRequested = 0;
    //CGGameUI::m_repopTime = 0;
    //CGGameUI::m_deadNoRepopTimer = 0;
    //CGGameUI::m_corpseReclaimDelay = 0;
    //CGGameUI::m_instanceBootTime = 0;
    //CGGameUI::m_instanceLockTime = 0;
    //CGGameUI::m_instanceLockComletedMask = 0;
    //CGGameUI::m_instanceLockExtending = 0;
    //CGGameUI::m_summonConfirmTime = 0;

    CRect screenRect;
    g_theGxDevicePtr->CapsWindowSizeInScreenCoords(screenRect);

    CGGameUI::m_screenWidth = 0;
    CGGameUI::m_screenHeight = 0;

    CGGameUI::m_aspect = CalculateAspectRatio();
    CoordinateSetAspectRatio(CGGameUI::m_aspect);

    auto m = SMemAlloc(sizeof(CSimpleTop), __FILE__, __LINE__, 0x0);
    CGGameUI::m_simpleTop = new (m) CSimpleTop();
    //CGGameUI::m_simpleTop->m_mouseButtonCallback = CGGameUI::FilterMouseButton;
    //CGGameUI::m_simpleTop->m_mouseMoveCallback = CGGameUI::FilterMouseMotion;
    CGGameUI::m_simpleTop->m_displaySizeCallback = &CGGameUI::HandleDisplaySizeChanged;
    //CGGameUI::m_simpleTop->dword1244 = (uint32_t)CGGameUI::HandleFocusChanged;
    //CGGameUI::m_simpleTop->dword124C = 1;
    //CGGameUI::m_simpleTop->dword1254 = (uint32_t)CGGameUI::ShowBlockedFrameFeedback;

    //CursorInitialize();
    //auto activeInputControl = CGInputControl::GetActive();
    //STORM_ASSERT(activeInputControl);
    //CGInputControl::UpdateMouseMode((int)Active, 1);
    
    FrameScript_Flush();
    //LoadScriptFunctions();
    FrameScript_CreateEvents(g_scriptEvents, 722);
    //CGGameUI::RegisterGameCVars();
    //CGUIBindings::Initialize();

    CGGameUI::RegisterFrameFactories();

    // STORM_ASSERT(GetDataInterfaceVersion() == GetCodeInterfaceVersion())

    CWOWClientStatus status;

    // OsCreateDirectory("Logs", 0);
    if (!SLogCreate("Logs\\FrameXML.log", 0, &status.m_logFile)) {
        SysMsgPrintf(SYSMSG_WARNING, "Cannot create WOWClient log file \"%s\"!", "Logs\\FrameXML.log");
    }

    //LoadAddOnEnableState(ClientServices::GetCharacterName());

    MD5_CTX md5;
    MD5Init(&md5);

    unsigned char digest1[16];

    switch (FrameXML_CheckSignature("Interface\\FrameXML\\FrameXML.toc", "Interface\\FrameXML\\Bindings.xml", nullptr, digest1)) {
    case 0:
        status.Add(STATUS_WARNING, "FrameXML missing signature");
        ClientPostClose(10);
        break;
    case 1:
        status.Add(STATUS_WARNING, "FrameXML has corrupt signature");
        ClientPostClose(10);
        break;
    case 2:
        status.Add(STATUS_WARNING, "FrameXML is modified or corrupt");
        ClientPostClose(10);
        break;

    case 3:
        break;

    default:
        ClientPostClose(10);
        break;
    }

    int32_t numFiles = 0;
    char* data = nullptr;
    if (SFile::Load(nullptr, "Interface\\FrameXML\\FrameXML.toc", (void**)&data, nullptr, 1, 1, nullptr)) {
        numFiles = FrameXML_GuessNumFiles(data);
        SMemFree(data);
    }

    //numFiles += LoadAddOnFileCount();

    //FrameXML_RegisterLoadProgressCallback(&LoadingScreenXMLCallback, 0, numFiles);
    FrameXML_FreeHashNodes();
    FrameXML_CreateFrames("Interface\\FrameXML\\FrameXML.toc", 0, &md5, &status);

    //if (SFile__FileExistsEx((void*)"Interface\\FrameXML\\Bindings.xml", 1))
    //    CGUIBindings::Load("Interface\\FrameXML\\Bindings.xml", &md5, &status);

    unsigned char digest2[16];
    MD5Final(digest2, &md5);
    if (memcmp(digest1, digest2, 16)) {
        // DO NOTHING FOR NOW
        //ClientPostClose(10);
    }

    int32_t objectType = CSimpleFrame::GetObjectType();
    CGGameUI::m_UISimpleParent = (CSimpleFrame*) CScriptObject::GetScriptObjectByName("UIParent", objectType);
    STORM_ASSERT(CGGameUI::m_UISimpleParent);

    // TODO: CGGameUI::m_gameTooltip = ...

    //LoadAddOns((int)v23);
    //FrameXML_RegisterLoadProgressCallback(0, 0, 0);
    //CGGameUI::RegisterUIScaleCVars();
    //CGGameUI::SomeSavedAccountVariables((int)v23);
    //LoadAccountData(6, (int(__cdecl*)(int, int, int))sub_5183A0, 0);
    //CGGameUI::UpdateInitCounter();
    //CGUIBindings::LoadBindings();
    //CGUIMacros::Initialize();
    //CGUIMacros::LoadMacros();
    //CGChat::LoadChatSettings();
    //CSimpleScriptManager::Create();

    CSizeEvent sizeEvent;
    sizeEvent.w = screenRect.maxX - screenRect.minX;
    sizeEvent.h = screenRect.maxY - screenRect.minY;

    CGGameUI::HandleDisplaySizeChanged(sizeEvent);
    //CGGameUI::m_initialized = 1;
    //EventRegister((LPCGUID)6, (PENABLECALLBACK)CGGameUI::Idle, v11, v12);

    //TODO: GxDeviceCallbacks

    //if (ClntObjMgrGetActivePlayer()) {
    //    CGGameUI::EnterWorld();
    //}
    //sub_4CFB90();
    //CGGameUI::m_currentlyReloadingUI = 0;
}

void CGGameUI::RegisterFrameFactories() {
    FrameXML_RegisterFactory("WorldFrame", CGWorldFrame::Create, 1);
    //FrameXML_RegisterFactory("GameTooltip", (int)CGTooltip::Create, 0);
    //FrameXML_RegisterFactory("Cooldown", (int)sub_51A380, 0);
    //FrameXML_RegisterFactory("Minimap", (int)CGMinimapFrame::Create, 0);
    //FrameXML_RegisterFactory("PlayerModel", (int)CGCharacterModelBase::Create, 0);
    //FrameXML_RegisterFactory("DressUpModel", (int)sub_514300, 0);
    //FrameXML_RegisterFactory("TabardModel", (int)CGTabardModelFrame::Create, 0);
    //FrameXML_RegisterFactory("QuestPOIFrame", (int)sub_514260, 0);
}

int32_t CGGameUI::HandleDisplaySizeChanged(const CSizeEvent& event) {
    return 0;
}
