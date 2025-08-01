#ifndef GX_DEVICE_HPP
#define GX_DEVICE_HPP

#include "gx/CGxDevice.hpp"
#include "gx/Types.hpp"
#include <cstdint>

class CGxFormat;

extern CGxDevice* g_theGxDevicePtr;


bool GxApiSupported(EGxApi api);

EGxApi GxDefaultApi();

CGxDevice* GxDevCreate(EGxApi api, int32_t (*windowProc)(void* window, uint32_t message, uintptr_t wparam, intptr_t lparam), const CGxFormat& format);

void GxDevDestroy(CGxDevice* device);

EGxApi GxDevApi(void);

bool GxDevExists();

void* GxDevWindow();

int32_t GxMasterEnable(EGxMasterEnables state);

void GxMasterEnableSet(EGxMasterEnables state, int32_t enable);

void GxDevOverride(EGxOverride override, uint32_t value);

int32_t GxAdapterDesktopMode(CGxMonitorMode& mode);

int32_t GxAdapterMonitorModes(TSGrowableArray<CGxMonitorMode>& modes);

int32_t GxAdapterID(uint16_t& vendorID, uint16_t& deviceID, uint32_t& driverVersionHi, uint32_t& driverVersionLow);

int32_t GxAdapterInfer(uint16_t& deviceID);

void GxLogOpen();

void GxLog(const char* format, ...);

void GxLogClose();

void GxAddStereoChangedCallback(CGxDevice::STEREO_CHANGED_CALLBACK callback);

int32_t GxRemoveStereoChangedCallback(CGxDevice::STEREO_CHANGED_CALLBACK callback);

void GxStereoSetConvergence(float value);

void GxStereoSetSeparation(float value);

const CGxCaps& GxCaps();

bool GxCapsWindowHasFocus(int32_t);

void GxCapsWindowSize(CRect&);

#endif
