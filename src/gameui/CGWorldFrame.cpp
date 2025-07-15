#include "gameui/CGWorldFrame.hpp"

#include "gx/Transform.hpp"
#include "gx/Draw.hpp"
#include "gx/Shader.hpp"
#include "world/CWorld.hpp"

#include <bc/Memory.hpp>
#include <tempest/Matrix.hpp>


CGWorldFrame* CGWorldFrame::s_currentWorldFrame = nullptr;


CGWorldFrame::CGWorldFrame(CSimpleFrame* parent) : CSimpleFrame(parent) {
    // TODO
    s_currentWorldFrame = this;
}

void CGWorldFrame::OnFrameRender(CRenderBatch* batch, uint32_t layer) {
    CSimpleFrame::OnFrameRender(batch, layer);
    if (!layer) {
        batch->QueueCallback(&CGWorldFrame::RenderWorld, this);
    }
}

CSimpleFrame* CGWorldFrame::Create(CSimpleFrame* parent) {
    // TODO:  Data = CDataAllocator__GetData(0, ".?AVCGWorldFrame@@", -2);

    auto m = SMemAlloc(sizeof(CGWorldFrame), __FILE__, __LINE__, 0);
    return m ? (new (m) CGWorldFrame(parent)) : nullptr;
}

void CGWorldFrame::RenderWorld(void* param) {
    C44Matrix saved_proj;
    GxXformProjection(saved_proj);

    C44Matrix saved_view;
    GxXformView(saved_view);

    CGWorldFrame::OnWorldUpdate();

    // TODO: PlayerNameUpdateWorldText();

    CGWorldFrame::OnWorldRender();

    // TODO: PlayerNameRenderWorldText();

    GxXformSetProjection(saved_proj);
    GxXformSetView(saved_view);

    CShaderEffect::UpdateProjMatrix();
}

void CGWorldFrame::OnWorldUpdate() {
    GxXformSetViewport(0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f);
    CImVector clearColor = { 0x00, 0x00, 0x00, 0xFF };
    GxSceneClear(3, clearColor);
    C44Matrix matrix;
    GxuXformCreateOrtho(0.0, 1.0, -0.5, 0.5, 0.0, 500.0, matrix);
    GxXformSetView(C44Matrix());
    GxXformSetProjection(matrix);
}

void CGWorldFrame::OnWorldRender() {
    CWorld::Render();
}
