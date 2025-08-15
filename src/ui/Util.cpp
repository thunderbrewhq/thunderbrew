#include "ui/Util.hpp"
#include <type_traits>
#include <storm/String.hpp>

const char* LanguageProcess(const char* string) {
    // TODO
    return string;
}

int32_t StringToBlendMode(const char* string, EGxBlend& blend) {
    struct BlendEntry {
        EGxBlend value;
        const char* string;
    };

    static BlendEntry blendMap[] = {
        { GxBlend_Opaque,   "DISABLE" },
        { GxBlend_Alpha,    "BLEND" },
        { GxBlend_AlphaKey, "ALPHAKEY" },
        { GxBlend_Add,      "ADD" },
        { GxBlend_Mod,      "MOD" }
    };

    for (int32_t i = 0; i < std::extent<decltype(blendMap)>::value; i++) {
        if (!SStrCmpI(blendMap[i].string, string, 0x7FFFFFFFu)) {
            blend = blendMap[i].value;
            return 1;
        }
    }

    return 0;
}

int32_t StringToFramePoint(const char* string, FRAMEPOINT& point) {
    struct FramePointEntry {
        FRAMEPOINT value;
        const char* string;
    };

    static FramePointEntry framePointMap[] = {
        { FRAMEPOINT_BOTTOM,        "BOTTOM" },
        { FRAMEPOINT_BOTTOMLEFT,    "BOTTOMLEFT" },
        { FRAMEPOINT_BOTTOMRIGHT,   "BOTTOMRIGHT" },
        { FRAMEPOINT_CENTER,        "CENTER" },
        { FRAMEPOINT_TOP,           "TOP" },
        { FRAMEPOINT_TOPRIGHT,      "TOPRIGHT" },
        { FRAMEPOINT_TOPLEFT,       "TOPLEFT" },
        { FRAMEPOINT_LEFT,          "LEFT" },
        { FRAMEPOINT_RIGHT,         "RIGHT" }
    };

    for (int32_t i = 0; i < std::extent<decltype(framePointMap)>::value; i++) {
        if (!SStrCmpI(framePointMap[i].string, string, 0x7FFFFFFFu)) {
            point = framePointMap[i].value;
            return 1;
        }
    }

    return 0;
}

int32_t StringToFrameStrata(const char* string, FRAME_STRATA& strata) {
    struct FrameStrataEntry {
        FRAME_STRATA value;
        const char* string;
    };

    // FRAME_STRATA_WORLD is hardcoded
    static FrameStrataEntry frameStrataMap[] = {
        { FRAME_STRATA_BACKGROUND,      "BACKGROUND" },
        { FRAME_STRATA_LOW,             "LOW" },
        { FRAME_STRATA_MEDIUM,          "MEDIUM" },
        { FRAME_STRATA_HIGH,            "HIGH" },
        { FRAME_STRATA_DIALOG,          "DIALOG" },
        { FRAME_STRATA_FULLSCREEN,      "FULLSCREEN" },
        { FRAME_STRATA_FULLSCREEN_DIALOG, "FULLSCREEN_DIALOG" },
        { FRAME_STRATA_TOOLTIP,         "TOOLTIP" }
    };

    for (int32_t i = 0; i < std::extent<decltype(frameStrataMap)>::value; i++) {
        if (!SStrCmpI(frameStrataMap[i].string, string, 0x7FFFFFFFu)) {
            strata = frameStrataMap[i].value;
            return 1;
        }
    }

    return 0;
}

const char* OrientationToString(uint32_t orientation) {
    switch (orientation) {
    case 0:
        return "HORIZONTAL";
    case 1:
        return "VERTICAL";
    default:
        return "UNKNOWN";
    }
}

const char* AnchorPointToString(int32_t point) {
    switch (point) {
    case 0:
        return "ANCHOR_LEFT";
    case 1:
        return "ANCHOR_RIGHT";
    case 2:
        return "ANCHOR_BOTTOMLEFT";
    case 3:
        return "ANCHOR_BOTTOM";
    case 4:
        return "ANCHOR_BOTTOMRIGHT";
    case 5:
        return "ANCHOR_TOPLEFT";
    case 6:
        return "ANCHOR_TOP";
    case 7:
        return "ANCHOR_TOPRIGHT";
    case 8:
        return "ANCHOR_CURSOR";
    case 10:
        return "ANCHOR_PRESERVE";
    case 11:
        return "ANCHOR_CURSOR_RIGHT";
    default:
        return "ANCHOR_NONE";
    }
}

const char* DrawLayerToString(int32_t layer) {
    switch (layer) {
    case 0:
        return "BACKGROUND";
    case 1:
        return "BORDER";
    case 2:
        return "ARTWORK";
    case 3:
        return "OVERLAY";
    case 4:
        return "HIGHLIGHT";
    default:
        return "UNKNOWN";
    }
}
