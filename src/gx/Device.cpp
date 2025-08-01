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
        SErrPrepareAppFatal(__FILE__, __LINE__); SErrDisplayAppFatal("GxDevCreate: failed to create graphics device %d", api);
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

void GxDevDestroy(CGxDevice* device) {
    // TODO
    // device->DeviceDestroy();
}

EGxApi GxDevApi() {
    return g_theGxDevicePtr->m_api;
}

bool GxDevExists() {
    return g_theGxDevicePtr != nullptr;
}

void* GxDevWindow() {
    return g_theGxDevicePtr->DeviceWindow();
}

int32_t GxMasterEnable(EGxMasterEnables state) {
    return g_theGxDevicePtr->MasterEnable(state);
}

void GxMasterEnableSet(EGxMasterEnables state, int32_t enable) {
    return g_theGxDevicePtr->MasterEnableSet(state, enable);
}

void GxDevOverride(EGxOverride override, uint32_t value) {
    // TODO
    // g_theGxDevicePtr->DeviceOverride(override, value);
}

EGxApi GxDefaultApi() {
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
    return (g_supportedApis & (1 << static_cast<uint32_t>(api))) != 0;
}

int32_t GxAdapterID(uint16_t& vendorID, uint16_t& deviceID, uint32_t& driverVersionHi, uint32_t& driverVersionLo) {
    return g_theGxDevicePtr->AdapterID(vendorID, deviceID, driverVersionHi, driverVersionLo);
}

int32_t GxAdapterInfer(uint16_t& deviceID) {
    return g_theGxDevicePtr->AdapterInfer(deviceID);
}

int32_t GxAdapterMonitorModes(TSGrowableArray<CGxMonitorMode>& modes) {
    return CGxDevice::AdapterMonitorModes(modes);
}

int32_t GxAdapterDesktopMode(CGxMonitorMode& mode) {
    return CGxDevice::AdapterDesktopMode(mode);
}

void GxLogOpen() {
    CGxDevice::LogOpen();
}

void GxLog(const char* format, ...) {
    va_list args;
    va_start(args, format);
    CGxDevice::VLog(format, args);
}

void GxLogClose() {
    CGxDevice::LogClose();
}

void GxAddStereoChangedCallback(CGxDevice::STEREO_CHANGED_CALLBACK callback) {
    // TODO
    // g_theGxDevicePtr->AddStereoChangedCallback(callback);
}

int32_t GxRemoveStereoChangedCallback(CGxDevice::STEREO_CHANGED_CALLBACK callback) {
    // TODO
    // return g_theGxDevicePtr->RemoveStereoChangedCallback(callback);
    return 1;
}

void GxStereoSetConvergence(float value) {
    // TODO
    // return g_theGxDevicePtr->StereoSetConvergence(value);
}

void GxStereoSetSeparation(float value) {
    // TODO
    // return g_theGxDevicePtr->StereoSetSeparation(value);
}

const CGxCaps& GxCaps() {
    return g_theGxDevicePtr->Caps();
}

bool GxCapsWindowHasFocus(int32_t a1) {
    // TODO
    return true;
}

void GxCapsWindowSize(CRect& rect) {
    g_theGxDevicePtr->CapsWindowSize(rect);
}
