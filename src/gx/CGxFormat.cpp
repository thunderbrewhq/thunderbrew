#include "gx/CGxFormat.hpp"

const char* CGxFormat::formatToColorBitsString[Formats_Last] = { "16", "24", "24", "30", "16", "24", "24", "32" };

CGxFormat::CGxFormat() {
    this->size.x = 0;
    this->size.y = 0;
    this->pos.x = 0;
    this->pos.y = 0;
    this->sampleQuality = 0.0;
    this->maximize = 0;
    this->stereoEnabled = false;
    this->sampleCount = 1;
    this->aspect = 1;
    this->unk1 = -1;
    this->unk2 = -1;
    this->unk3 = -1;
    this->unk4 = -1;
    this->unk5 = -1;
    this->unk6 = -1;
}

CGxFormat::CGxFormat(bool p_window, const C2iVector& p_size, Format p_colorFormat, Format p_depthFormat, uint32_t p_refreshRate, uint32_t p_vsync, bool p_hwTnl, bool p_fixLag, bool p_hwCursor, bool p_aspect, bool p_maximize) {
    this->size.x = 0;
    this->size.y = 0;
    this->pos.x = 0;
    this->pos.y = 0;
    this->hwTnL = p_hwTnl;
    this->hwCursor = p_hwCursor;
    this->fixLag = p_fixLag;
    this->window = p_window;
    this->depthFormat = p_depthFormat;
    this->size.x = p_size.x;
    this->size.y = p_size.y;
    this->sampleQuality = 0.0;
    this->colorFormat = p_colorFormat;
    this->refreshRate = p_refreshRate;
    this->vsync = p_vsync;
    this->aspect = p_aspect;
    this->stereoEnabled = 0;
    this->maximize = p_maximize;
    this->backbuffers = 1;
    this->sampleCount = 1;
    this->unk1 = -1;
    this->unk2 = -1;
    this->unk3 = -1;
    this->unk4 = -1;
    this->unk5 = -1;
    this->unk6 = -1;
}
