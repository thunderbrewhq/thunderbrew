#ifndef GX_GX_HPP
#define GX_GX_HPP

#include "gx/CGxCaps.hpp"
#include "gx/CGxFormat.hpp"
#include "gx/Types.hpp"
#include <cstdint>

class CRect;

extern const char** g_gxShaderProfileNames[GxShTargets_Last];

void GxFormatColor(CImVector&);

void GxSetMaxFPS(uint32_t maxFPS);

void GxSetMaxFPSBk(uint32_t maxFPSBk);

uint32_t GxGetMaxFPS();

uint32_t GxGetMaxFPSBk();

#endif
