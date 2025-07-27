#include "world/daynight/DNStars.hpp"
#include "world/daynight/DayNight.hpp"
#include "world/daynight/DNInfo.hpp"
#include "model/Model2.hpp"
#include <common/Time.hpp>

namespace DayNight {

C2Vector DNStars::m_fadeTable[4] = {
    { 0.1250f, 1.0f },
    { 0.1875f, 0.0f },
    { 0.9375f, 0.0f },
    { 1.0000f, 1.0f }
};

void DNStars::Initialize() {
    this->m_scene = M2CreateScene();
    this->m_model = this->m_scene->CreateModel("Environments\\Stars\\stars.mdl", 0);
    this->m_time = OsGetAsyncTimeMs();
}

void DNStars::Destroy() {
    if (this->m_model) {
        this->m_model->Release();
        this->m_model = nullptr;
    }

    if (this->m_scene) {
        // TODO: this->m_scene->Release();
        this->m_scene = nullptr;
    }
}

void DNStars::Update() {
    auto info = DayNight::GetInfo();

    this->m_pos = info->cameraPos;

    auto fade = DayNight::InterpTable(DNStars::m_fadeTable, 4, info->dayProgression);
    this->m_color.a = static_cast<uint8_t>(fade * 254.0 + 1.0);
}

void DNStars::Render() {
    if (this->m_color.a < 2) {
        return;
    }

    this->m_model->SetAnimating(1);
    this->m_model->SetVisible(1);

    // TODO: this->m_model->SetSomething(1);

    float alpha = static_cast<float>(this->m_color.a);
    // TODO: this->m_model->SetAlpha(alpha * 0.0039215689f)

    uint32_t elapsed = OsGetAsyncTimeMs() - this->m_time;
    this->m_time += elapsed;
    this->m_scene->AdvanceTime(elapsed);
    this->m_scene->Animate(C3Vector());
    this->m_scene->Draw(M2PASS_0);
    this->m_scene->Draw(M2PASS_1);
}

} // namespace DayNight
