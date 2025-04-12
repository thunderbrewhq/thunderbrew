#include "console/Screen.hpp"
#include "console/Console.hpp"
#include "console/Command.hpp"
#include "console/Handlers.hpp"
#include "console/Highlight.hpp"
#include "console/Line.hpp"
#include "console/Text.hpp"
#include "console/Types.hpp"
#include "gx/Buffer.hpp"
#include "gx/Coordinate.hpp"
#include "gx/Device.hpp"
#include "gx/Draw.hpp"
#include "gx/Font.hpp"
#include "gx/Gx.hpp"
#include "gx/RenderState.hpp"
#include "gx/Screen.hpp"
#include <bc/Debug.hpp>
#include <storm/String.hpp>
#include <tempest/Rect.hpp>
#include <algorithm>

static HLAYER s_layerBackground;
static HLAYER s_layerText;
static RECTF s_rect = { 0.0f, 1.0f, 1.0f, 1.0f };

float s_consoleLines = 10.0f;
float s_consoleHeight = s_consoleLines * s_fontHeight;
CONSOLERESIZESTATE s_consoleResizeState = CS_NONE;

CImVector s_colorArray[NUM_COLORTYPES] = {
    { 0xFF, 0xFF, 0xFF, 0xFF }, // DEFAULT_COLOR
    { 0xFF, 0xFF, 0xFF, 0xFF }, // INPUT_COLOR
    { 0x80, 0x80, 0x80, 0xFF }, // ECHO_COLOR
    { 0x00, 0x00, 0xFF, 0xFF }, // ERROR_COLOR
    { 0x00, 0xFF, 0xFF, 0xFF }, // WARNING_COLOR
    { 0xFF, 0xFF, 0xFF, 0xFF }, // GLOBAL_COLOR
    { 0xFF, 0xFF, 0xFF, 0xFF }, // ADMIN_COLOR
    { 0xFF, 0xFF, 0xFF, 0x80 }, // HIGHLIGHT_COLOR
    { 0x00, 0x00, 0x00, 0xC0 }, // BACKGROUND_COLOR
};

void DrawBackground() {
    uint16_t indices[] = {
        0, 1, 2, 3
    };

    C3Vector position[] = {
        { s_rect.left,  s_rect.bottom,  0.0f },
        { s_rect.right, s_rect.bottom,  0.0f },
        { s_rect.left,  s_rect.top,     0.0f },
        { s_rect.right, s_rect.top,     0.0f }
    };

    GxRsPush();

    GxRsSet(GxRs_Lighting, 0);
    GxRsSet(GxRs_Fog, 0);
    GxRsSet(GxRs_DepthTest, 0);
    GxRsSet(GxRs_DepthWrite, 0);
    GxRsSet(GxRs_Culling, 0);
    GxRsSet(GxRs_PolygonOffset, 0.0f);
    GxRsSet(GxRs_BlendingMode, GxBlend_Alpha);
    GxRsSet(GxRs_AlphaRef, CGxDevice::s_alphaRef[GxBlend_Alpha]);

    GxPrimLockVertexPtrs(4, position, sizeof(C3Vector), nullptr, 0, &s_colorArray[BACKGROUND_COLOR], 0, nullptr, 0, nullptr, 0, nullptr, 0);
    GxDrawLockedElements(GxPrim_TriangleStrip, 4, indices);
    GxPrimUnlockVertexPtrs();

    GxRsPop();
}

void DrawHighLight() {
    uint16_t indices[] = {
        0, 1, 2, 3
    };

    C3Vector position[] = {
        { s_hRect.left,  s_hRect.bottom,  0.0f },
        { s_hRect.right, s_hRect.bottom,  0.0f },
        { s_hRect.left,  s_hRect.top,     0.0f },
        { s_hRect.right, s_hRect.top,     0.0f }
    };

    GxRsPush();

    GxRsSet(GxRs_Lighting, 0);
    GxRsSet(GxRs_BlendingMode, GxBlend_Alpha);
    GxRsSet(GxRs_AlphaRef, CGxDevice::s_alphaRef[GxBlend_Alpha]);

    GxPrimLockVertexPtrs(4, position, sizeof(C3Vector), nullptr, 0, &s_colorArray[HIGHLIGHT_COLOR], 0, nullptr, 0, nullptr, 0, nullptr, 0);
    GxDrawLockedElements(GxPrim_TriangleStrip, 4, indices);
    GxPrimUnlockVertexPtrs();

    GxRsPop();
}

void DrawCaret(C3Vector& caretpos) {
    uint16_t indices[] = {
        0, 1, 2, 3
    };

    float minX = caretpos.x;
    float minY = caretpos.y;

    float maxX = caretpos.x + (s_caretpixwidth * 2);
    float maxY = caretpos.y + s_fontHeight;

    C3Vector position[] = {
        { minX, minY, 0.0f },
        { maxX, minY, 0.0f },
        { minX, maxY, 0.0f },
        { maxX, maxY, 0.0f }
    };

    GxRsPush();

    GxRsSet(GxRs_Lighting, 0);
    GxRsSet(GxRs_Fog, 0);
    GxRsSet(GxRs_DepthTest, 0);
    GxRsSet(GxRs_DepthWrite, 0);
    GxRsSet(GxRs_Culling, 0);
    GxRsSet(GxRs_PolygonOffset, 0.0f);
    GxRsSet(GxRs_BlendingMode, GxBlend_Alpha);
    GxRsSet(GxRs_AlphaRef, CGxDevice::s_alphaRef[GxBlend_Alpha]);

    GxPrimLockVertexPtrs(4, position, sizeof(C3Vector), nullptr, 0, &s_colorArray[INPUT_COLOR], 0, nullptr, 0, nullptr, 0, nullptr, 0);
    GxDrawLockedElements(GxPrim_TriangleStrip, 4, indices);
    GxPrimUnlockVertexPtrs();

    GxRsPop();
}

void PaintBackground(void* param, const RECTF* rect, const RECTF* visible, float elapsedSec) {
    if (s_rect.bottom < 1.0f) {
        DrawBackground();

        if (s_highlightState) {
            DrawHighLight();
        }
    }
}

void PaintText(void* param, const RECTF* rect, const RECTF* visible, float elapsedSec) {
    if (s_rect.bottom >= 1.0f) {
        return;
    }

    static float carettime = 0.0f;
    static C3Vector caretpos = { 0.0f, 0.0f, 0.0f };

    //
    carettime += elapsedSec;
    if ((!s_caret && carettime > 0.2) || (carettime > 0.3)) {
        s_caret = !s_caret;
        carettime = 0;
    }

    auto line = GetInputLine();

    C3Vector pos = {
        s_rect.left,
        (s_fontHeight * 0.75f) + s_rect.bottom,
        1.0f
    };

    GxuFontClearBatch(s_batch);

    if (s_inputString) {
        GxuFontSetStringPosition(s_inputString, pos);
        GxuFontAddToBatch(s_batch, s_inputString);
    }

    auto font = TextBlockGetFontPtr(s_textFont);

    if (line->inputpos) {
        caretpos = pos;

        GxuFontGetTextExtent(font, line->buffer, line->inputpos, s_fontHeight, &caretpos.x, 0.0f, 1.0f, s_charSpacing, s_baseTextFlags);

        DrawCaret(caretpos);
    }

    pos.y += s_fontHeight;

    for (auto lineptr = s_currlineptr; (lineptr && pos.y < 1.0); lineptr = lineptr->Next()) {
        if (lineptr != line) {
            if (lineptr->fontPointer == nullptr) {
                GenerateNodeString(lineptr);
            }

            GxuFontSetStringPosition(lineptr->fontPointer, pos);
            GxuFontAddToBatch(s_batch, lineptr->fontPointer);
            pos.y += s_fontHeight;
        }
    }

    GxuFontRenderBatch(s_batch);
}

void ConsoleScreenAnimate(float elapsedSec) {
    auto finalPos = ConsoleGetActive() ? std::min(1.0f - s_consoleHeight, 1.0f) : 1.0f;
    finalPos = std::max(finalPos, 0.0f);

    if (s_rect.bottom == finalPos) {
        return;
    }

    auto currentPos = finalPos;

    if (s_consoleResizeState == CS_NONE) {
        auto direction = s_rect.bottom <= finalPos ? 1.0f : -1.0f;

        currentPos = s_rect.bottom + direction * elapsedSec * 5.0f;
        currentPos = ConsoleGetActive() ? std::max(currentPos, finalPos) : std::min(currentPos, finalPos);
    }

    s_rect.bottom = currentPos;

    ScrnLayerSetRect(s_layerBackground, &s_rect);
    ScrnLayerSetRect(s_layerText, &s_rect);
}

void ConsoleScreenInitialize(const char* title) {
    CRect windowSize;
    GxCapsWindowSize(windowSize);

    auto width = windowSize.maxX - windowSize.minX;
    auto height = windowSize.maxY - windowSize.minY;
    s_caretpixwidth = width == 0.0f ? 1.0f : 1.0f / width;
    s_caretpixheight = height == 0.0f ? 1.0f : 1.0f / height;

    SStrCopy(s_fontName, "Fonts\\ARIALN.ttf", sizeof(s_fontName));
    s_textFont = TextBlockGenerateFont(s_fontName, 0, NDCToDDCHeight(s_fontHeight));

    ScrnLayerCreate(&s_rect, 6.0f, 0x1 | 0x2, nullptr, PaintBackground, &s_layerBackground);
    ScrnLayerCreate(&s_rect, 7.0f, 0x1 | 0x2, nullptr, PaintText, &s_layerText);

    RegisterHandlers();

    // TODO register commands
    ConsoleInitializeScreenCommand();

    // TODO EventSetConfirmCloseCallback(EventCloseCallback, 0);

    ConsoleCommandExecute("ver", 1);

    s_batch = GxuFontCreateBatch(false, false);
}
