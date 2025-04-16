#ifndef CONSOLE_C_VAR_GX_HPP
#define CONSOLE_C_VAR_GX_HPP

#include "gx/CGxFormat.hpp"
#include "console/CVar.hpp"

extern CVar* s_cvGxStereoEnabled;
extern CVar* s_cvGxRefresh;
extern CVar* s_cvGxMaximize;
extern CVar* s_cvGxMultisample;
extern CVar* s_cvGxCursor;
extern CVar* s_cvGxStereoSeparation;
extern CVar* s_cvGxMultisampleQuality;
extern CVar* s_cvGxResolution;
extern CVar* s_cvHwDetect;
extern CVar* s_cvGxOverride;
extern CVar* s_cvGxFixLag;
extern CVar* s_cvMaxFPS;
extern CVar* s_cvGxVSync;
extern CVar* s_cvVideoOptionsVersion;
extern CVar* s_cvGxStereoConvergence;
extern CVar* s_cvMaxFPSBk;
extern CVar* s_cvGxTripleBuffer;
extern CVar* s_cvGxDepthBits;
extern CVar* s_cvGxColorBits;
extern CVar* s_cvGxApi;
extern CVar* s_cvGxAspect;
extern CVar* s_cvFixedFunction;
extern CVar* s_cvWidescreen;
extern CVar* s_cvGxWindow;
extern CVar* s_cvWindowResizeLock;

void RegisterGxCVars();

void UpdateGxCVars();

void SetGxCVars(const CGxFormat& format);

bool CVGxStereoConvergenceCallback(CVar* h, const char* oldValue, const char* newValue, void* arg);

bool CVGxStereoSeparationCallback(CVar* h, const char* oldValue, const char* newValue, void* arg);

#endif
