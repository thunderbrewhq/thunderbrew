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
HTEXTURE CWorldScene::s_defaultTexture;
HTEXTURE CWorldScene::s_defaultBlendTexture;

CM2Model* g_models[10] = {};

void CWorldSceneLightingCallback(CM2Model* model, CM2Lighting* lighting, void* userArg) {
    lighting->AddAmbient({ 1.0f, 1.0f, 1.0f });
    lighting->AddDiffuse({ 1.0f, 1.0f, 1.0f }, { 1.0f, 0.0f, 0.0f });
    lighting->AddSpecular({ 0.0f, 0.0f, 0.0f });
}

void CWorldScene::Initialize() {
    // TODO
    CWorldScene::s_m2Scene = M2CreateScene();
    g_models[0] = CWorldScene::s_m2Scene->CreateModel(R"(World\LORDAERON\Arathi\PassiveDoodads\Trees\ArathiStump01.m2)", 0);
    g_models[0]->SetWorldTransform(C3Vector(1.0f, 0.0f, 0.0f), 0.0f, 0.1f);

    g_models[1] = CWorldScene::s_m2Scene->CreateModel(R"(World\NoDXT\Detail\ApkBus01.m2)", 0);
    g_models[1]->SetWorldTransform(C3Vector(1.5f), 0.0f, 1.0f);

    g_models[2] = CWorldScene::s_m2Scene->CreateModel(R"(Creature\BloodElfGuard\BloodElfMale_Guard.m2)", 0);
    g_models[2]->SetWorldTransform(C3Vector(0.0f), 0.0f, 1.0f);

    for (size_t i = 0; i < 10; ++i) {
        if (!g_models[i])
            continue;

        g_models[i]->SetBoneSequence(0xFFFFFFFF, 0, 0xFFFFFFFF, 0, 1.0f, 1, 1);
        g_models[i]->SetLightingCallback(&CWorldSceneLightingCallback, nullptr);
    }

    CWorldScene::s_defaultTexture = TextureCreateSolid({ 0x80, 0x80, 0x80, 0xFF });
    CWorldScene::s_defaultBlendTexture = TextureCreateSolid({ 0, 0, 0, 0xFF });
}

void CWorldScene::Render(const C3Vector& cameraPos, float time) {
    // TODO
    GxRsPush();
    GxXformPush(GxXform_World);
    CRect rect;
    CGWorldFrame::s_currentWorldFrame->GetRect(&rect);
    CGWorldFrame::GetActiveCamera()->SetGxProjectionAndView(rect);


    if (CWorldScene::s_m2Scene) {
        for (size_t i = 0; i < 10; ++i) {
            if (!g_models[i])
                continue;
            g_models[i]->SetAnimating(1);
            g_models[i]->SetVisible(1);
        }

        CWorldScene::s_m2Scene->m_flags |= 1u;
        CWorldScene::s_m2Scene->AdvanceTime(static_cast<uint32_t>(time * 1000.0f));
        CWorldScene::s_m2Scene->Animate(cameraPos);
        CWorldScene::s_m2Scene->m_flags &= ~1u;
    }

    // sub_6FDA20();
    // sub_7BB570();

    CShaderEffect::UpdateProjMatrix();
    // CWorldScene::RenderSetFog();

    DayNight::Update();
    DayNight::RenderSky();

    GxXformPop(GxXform_World);
    GxRsPop();

    CursorResetCursor();

    if (CWorld::GetEnables() & 0x200000) {
        // TODO
    }
}
