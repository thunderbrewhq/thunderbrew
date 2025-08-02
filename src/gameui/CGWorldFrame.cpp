#include "gameui/CGWorldFrame.hpp"

#include "gx/Transform.hpp"
#include "gx/Draw.hpp"
#include "gx/Shader.hpp"
#include "gx/Device.hpp"
#include "gx/RenderState.hpp"
#include "world/CWorld.hpp"
#include "world/CWorldScene.hpp"
#include "gameui/camera/CGCamera.hpp"
#include "event/EvtKeyDown.hpp"

#include "model/Model2.hpp"

#include <bc/Memory.hpp>
#include <tempest/Matrix.hpp>
#include <common/Time.hpp>


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
    float astep = 0.1f;

    static float pitch = 0.0f;
    static float yaw = 0.0f;
    static float roll = 0.0f;

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

    case KEY_P:
        position.Set(0.0f, 0.0f, 0.0f);
        break;

    case KEY_R:
        pitch = 0.0f;
        yaw = 0.0f;
        roll = 0.0f;
        break;

    case KEY_Z:
        position.Set(0.0f, 0.0f, 0.0f);
        pitch = 0.0f;
        yaw = 0.0f;
        roll = 0.0f;
        break;

    case KEY_LEFT:
        roll -= astep;
        break;
    case KEY_RIGHT:
        roll += astep;
        break;

    case KEY_DOWN:
        pitch -= astep;
        break;
    case KEY_UP:
        pitch += astep;
        break;

    case KEY_PAGEUP:
        yaw += astep;
        break;
    case KEY_PAGEDOWN:
        yaw -= astep;
        break;


    default:
        break;
    }

    this->m_camera->SetFacing(yaw, pitch, roll);

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
    GxRsSet(GxRs_Multisample, 1);

    if (true) {
        CImVector clearColor = { 0x80, 0x80, 0x80, 0xFF };
        GxSceneClear(3, clearColor);
    }

    if (CWorld::GetEnables() & 0x20000000) {
        GxMasterEnableSet(GxMasterEnable_PolygonFill, 0);
    }

    C3Vector saveMin;
    C3Vector saveMax;

    GxXformViewport(saveMin.x, saveMax.x, saveMin.y, saveMax.y, saveMin.z, saveMax.z);

    // TODO

    // WORKAROUND:
    float maxZ = saveMax.z - (saveMax.z - saveMin.z) * 0.050000001;
    GxXformSetViewport(saveMin.x, saveMax.x, saveMin.y, saveMax.y, saveMin.z, maxZ);

    CShaderEffect::UpdateProjMatrix();

    static auto s_time = 0;

    float elapsed = static_cast<float>(OsGetAsyncTimeMs() - s_time) / 1000.0f;
    s_time = OsGetAsyncTimeMs();
    CWorld::Render(C3Vector(), elapsed);

    if (CWorldScene::s_m2Scene) {
        CWorldScene::s_m2Scene->Draw(M2PASS_0);
    }

    GxRsPop();
}

CGCamera* CGWorldFrame::GetActiveCamera() {
    STORM_ASSERT(CGWorldFrame::s_currentWorldFrame);
    STORM_ASSERT(CGWorldFrame::s_currentWorldFrame->m_camera);
    return CGWorldFrame::s_currentWorldFrame->m_camera;
}
