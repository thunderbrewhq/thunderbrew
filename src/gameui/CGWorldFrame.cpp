#include "gameui/CGWorldFrame.hpp"

#include "gx/Transform.hpp"
#include "gx/Draw.hpp"
#include "gx/Shader.hpp"
#include "gx/Device.hpp"
#include "gx/RenderState.hpp"
#include "world/CWorld.hpp"
#include "gameui/camera/CSimpleCamera.hpp"

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

}

void CGWorldFrame::OnWorldRender() {
    CRect windowSize;
    GxCapsWindowSize(windowSize);
    if (windowSize.maxY - windowSize.minY == 0.0f || windowSize.maxX - windowSize.minX == 0.0f) {
        return;
    }

    // TODO

    GxRsPush();

    C3Vector saveMin;
    C3Vector saveMax;

    GxXformViewport(saveMin.x, saveMax.x, saveMin.y, saveMax.y, saveMin.z, saveMax.z);

    // TODO

    // WORKAROUND:
    float maxZ = saveMax.z - (saveMax.z - saveMin.z) * 0.050000001;
    GxXformSetViewport(saveMin.x, saveMax.x, saveMin.y, saveMax.y, saveMin.z, maxZ);

    CShaderEffect::UpdateProjMatrix();

    CWorld::Render();

    GxRsPop();
}
