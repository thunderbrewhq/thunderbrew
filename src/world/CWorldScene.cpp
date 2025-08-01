#include "world/CWorldScene.hpp"
#include "world/CWorld.hpp"
#include "world/map/CMap.hpp"
#include "world/daynight/DayNight.hpp"

#include "gx/Device.hpp"
#include "gx/Shader.hpp"
#include "gx/RenderState.hpp"
#include "gx/Transform.hpp"

#include "model/Model2.hpp"

#include "gameui/camera/CGCamera.hpp"
#include "gameui/CGWorldFrame.hpp"

#include "cursor/Cursor.hpp"


CM2Scene* CWorldScene::s_m2Scene;


void CWorldScene::Initialize() {
    // TODO
    CWorldScene::s_m2Scene = M2CreateScene();
    auto model = CWorldScene::s_m2Scene->CreateModel("Spells\\ErrorCube.mdx", 0);
    model->SetAnimating(1);
    model->SetVisible(1);
}

void CWorldScene::Render(const C3Vector& cameraPos, float time) {
    // TODO
    GxRsPush();
    GxXformPush(GxXform_World);
    CRect rect;
    CGWorldFrame::s_currentWorldFrame->GetRect(&rect);
    CGWorldFrame::GetActiveCamera()->SetGxProjectionAndView(rect);


    if (CWorldScene::s_m2Scene) {
        CWorldScene::s_m2Scene->m_flags |= 1u;
        CWorldScene::s_m2Scene->AdvanceTime(static_cast<uint32_t>(time * 1000.0f));
        CWorldScene::s_m2Scene->Animate(cameraPos);
        CWorldScene::s_m2Scene->m_flags &= ~1u;
    }

    DayNight::Update();
    DayNight::RenderSky();

    GxXformPop(GxXform_World);
    GxRsPop();

    CursorResetCursor();

    if (CWorld::GetEnables() & 0x200000) {
        // TODO
    }
}
