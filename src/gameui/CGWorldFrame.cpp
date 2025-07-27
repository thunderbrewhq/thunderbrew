#include "gameui/CGWorldFrame.hpp"

#include "gx/Transform.hpp"
#include "gx/Draw.hpp"
#include "gx/Shader.hpp"
#include "gx/Device.hpp"
#include "gx/RenderState.hpp"
#include "world/CWorld.hpp"
#include "gameui/camera/CGCamera.hpp"
#include "event/EvtKeyDown.hpp"

#include <bc/Memory.hpp>
#include <tempest/Matrix.hpp>


CGWorldFrame* CGWorldFrame::s_currentWorldFrame = nullptr;


CGWorldFrame::CGWorldFrame(CSimpleFrame* parent) : CSimpleFrame(parent) {
    // TODO

    this->m_camera = NEW(CGCamera);

    s_currentWorldFrame = this;

    this->EnableEvent(SIMPLE_EVENT_KEY, -1);
    this->EnableEvent(SIMPLE_EVENT_MOUSE, -1);
    this->EnableEvent(SIMPLE_EVENT_MOUSEWHEEL, -1);
}

void CGWorldFrame::OnFrameRender(CRenderBatch* batch, uint32_t layer) {
    CSimpleFrame::OnFrameRender(batch, layer);
    if (!layer) {
        batch->QueueCallback(&CGWorldFrame::RenderWorld, this);
    }
}

int32_t CGWorldFrame::OnLayerKeyDown(const CKeyEvent& evt) {
    if (CSimpleFrame::OnLayerKeyDown(evt)) {
        return 1;
    }

    // WORKAROUND: Camera testing
    C3Vector& position = this->m_camera->m_position;

    float step = 0.1f;

    switch (evt.key) {
    case KEY_W:
        position.z -= step;
        break;
    case KEY_A:
        position.y -= step;
        break;
    case KEY_S:
        position.z += step;
        break;
    case KEY_D:
        position.y += step;
        break;
    case KEY_PLUS:
        position.x += step;
        break;
    case KEY_MINUS:
        position.x -= step;
        break;
    default:
        break;
    }

    return 0;
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

CGCamera* CGWorldFrame::GetActiveCamera() {
    STORM_ASSERT(CGWorldFrame::s_currentWorldFrame);
    STORM_ASSERT(CGWorldFrame::s_currentWorldFrame->m_camera);
    return CGWorldFrame::s_currentWorldFrame->m_camera;
}
