#ifndef GAME_UI_CGWORLDFRAME_HPP
#define GAME_UI_CGWORLDFRAME_HPP

#include "ui/CSimpleFrame.hpp"
#include "ui/CSimpleTop.hpp"

class CGCamera;

class CGWorldFrame : public CSimpleFrame {
    public:
    CGWorldFrame(CSimpleFrame* parent);

    virtual void OnFrameRender(CRenderBatch* batch, uint32_t layer);
    virtual int32_t OnLayerKeyDown(const CKeyEvent& evt);

    static CSimpleFrame* Create(CSimpleFrame* parent);
    static void RenderWorld(void* param);
    static void OnWorldUpdate();
    static void OnWorldRender();
    static CGCamera* GetActiveCamera();

    CGCamera* m_camera = nullptr;

    public:
    static CGWorldFrame* s_currentWorldFrame;
};

#endif // GAME_UI_CGWORLDFRAME_HPP
