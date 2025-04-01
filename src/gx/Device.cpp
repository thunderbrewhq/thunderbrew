#include "gx/Device.hpp"
#include "gx/CGxDevice.hpp"
#include "gx/Gx.hpp"
#include <cstdio>

CGxDevice* g_theGxDevicePtr = nullptr;

// NOTE: this is a backport from later versions
// bitmask listing supported gxapis
uint32_t g_supportedApis = 0
#if defined(WHOA_SYSTEM_WIN)
    | (1 << GxApi_D3d9)
#endif

#if defined(WHOA_SYSTEM_MAC)
    | (1 << GxApi_GLL)
#endif

#if defined(WHOA_BUILD_GLSDL)
    | (1 << GxApi_GLSDL)
#endif
;

CGxDevice* GxDevCreate(EGxApi api, int32_t (*windowProc)(void* window, uint32_t message, uintptr_t wparam, intptr_t lparam), const CGxFormat& format) {
    CGxDevice* device = nullptr;

    switch (api) {
    case GxApi_OpenGl:
        device = CGxDevice::NewOpenGl();
        break;

#if defined(WHOA_SYSTEM_WIN)
    case GxApi_D3d9:
        device = CGxDevice::NewD3d();
        break;
    case GxApi_D3d9Ex:
        device = CGxDevice::NewD3d9Ex();
        break;
    case GxApi_D3d10:
    case GxApi_D3d11:
        // Error
        break;
#endif

#if defined(WHOA_SYSTEM_MAC)
    case GxApi_GLL:
        device = CGxDevice::NewGLL();
        break;
#endif

#if defined(WHOA_BUILD_GLSDL)
    case GxApi_GLSDL:
        device = CGxDevice::NewGLSDL();
        break;
#endif

    default:
        break;
    }

    if (!device) {
        SErrPrepareAppFatal(__FILE__, __LINE__);
        SErrDisplayAppFatal("GxDevCreate: failed to create graphics device %d", api);
    }

    // STORM_ASSERT(device != nullptr);

    g_theGxDevicePtr = device;

    if (g_theGxDevicePtr->DeviceCreate(windowProc, format)) {
        return g_theGxDevicePtr;
    } else {
        if (g_theGxDevicePtr) {
            DEL(g_theGxDevicePtr);
        }

        return nullptr;
    }
}


int32_t GxDevExists() {
    return g_theGxDevicePtr != nullptr;
}

EGxApi GxDevApi() {
    return g_theGxDevicePtr->m_api;
}

void* GxDevWindow() {
    return g_theGxDevicePtr->DeviceWindow();
}

int32_t GxMasterEnable(EGxMasterEnables state) {
    return g_theGxDevicePtr->MasterEnable(state);
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

bool GxApiSupported(EGxApi api) {
    return (g_supportedApis & static_cast<uint32_t>(api)) != 0;
}

bool GxAdapterMonitorModes(TSGrowableArray<CGxMonitorMode>& modes) {
    return CGxDevice::AdapterMonitorModes(modes);
}

void GxLogOpen() {
    CGxDevice::LogOpen();
}
