#ifndef GAME_UI_CGWORLDFRAME_HPP
#define GAME_UI_CGWORLDFRAME_HPP

#include "ui/CSimpleFrame.hpp"
#include "ui/CSimpleTop.hpp"

class CGWorldFrame : public CSimpleFrame {
    public:
    CGWorldFrame(CSimpleFrame* parent);

    virtual void OnFrameRender(CRenderBatch* batch, uint32_t layer);

    static CSimpleFrame* Create(CSimpleFrame* parent);
    static void RenderWorld(void* param);
    static void OnWorldUpdate();
    static void OnWorldRender();

    public:
    static CGWorldFrame* s_currentWorldFrame;
};

#endif // GAME_UI_CGWORLDFRAME_HPP
