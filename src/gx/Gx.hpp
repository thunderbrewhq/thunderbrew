#ifndef GX_GX_HPP
#define GX_GX_HPP

#include "gx/CGxCaps.hpp"
#include "gx/CGxFormat.hpp"
#include "gx/Types.hpp"
#include <cstdint>

class CRect;

extern const char** g_gxShaderProfileNames[GxShTargets_Last];

const CGxCaps& GxCaps();

bool GxCapsWindowHasFocus(int32_t);

void GxCapsWindowSize(CRect&);

void GxFormatColor(CImVector&);

void GxLogOpen();

void GxLogClose();

void GxLog(const char* format, ...);

void GxSetMaxFPS(uint32_t maxFPS);

void GxSetMaxFPSBk(uint32_t maxFPSBk);

uint32_t GxGetMaxFPS();

uint32_t GxGetMaxFPSBk();

#endif
