#ifndef GX_C_GX_FORMAT_HPP
#define GX_C_GX_FORMAT_HPP

#include <cstdint>
#include <tempest/Vector.hpp>

class CGxFormat {
    public:
        // Types
        enum Format {
            Fmt_Rgb565 = 0,
            Fmt_ArgbX888 = 1,
            Fmt_Argb8888 = 2,
            Fmt_Argb2101010 = 3,
            Fmt_Ds160 = 4,
            Fmt_Ds24X = 5,
            Fmt_Ds248 = 6,
            Fmt_Ds320 = 7,
            Formats_Last = 8
        };

        CGxFormat();
        CGxFormat(bool p_window, const C2iVector& p_size, Format p_colorFormat, Format p_depthFormat, uint32_t p_refreshRate, uint32_t p_vsync, bool p_hwTnl, bool p_fixLag, bool p_hwCursor, bool p_aspect, bool p_maximize);

        static const char* formatToColorBitsString[Formats_Last];

        // Member variables
        uint32_t apiSpecificModeID;
        bool hwTnL;
        bool hwCursor;
        bool fixLag;
        int8_t window;
        int8_t aspect;
        int32_t maximize;
        Format depthFormat;
        C2iVector size;
        uint32_t backbuffers;
        uint32_t sampleCount;
        float sampleQuality;
        Format colorFormat;
        uint32_t refreshRate;
        uint32_t vsync;
        bool stereoEnabled;
        uint32_t unk1;
        uint32_t unk2;
        uint32_t unk3;
        uint32_t unk4;
        uint32_t unk5;
        uint32_t unk6;
        C2iVector pos;
};

#endif
