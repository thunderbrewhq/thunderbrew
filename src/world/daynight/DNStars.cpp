#include "world/daynight/DNStars.hpp"
#include "model/Model2.hpp"
#include <common/Time.hpp>

namespace DayNight {

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
    // TODO
}

void DNStars::Render() {
    if (this->m_color.a < 2) {
        //return;
    }

    this->m_model->SetAnimating(1);
    this->m_model->SetVisible(1);

    // TODO: this->m_model->SetSomething(1);

    uint32_t elapsed = OsGetAsyncTimeMs() - this->m_time;
    this->m_time += elapsed;
    this->m_scene->AdvanceTime(elapsed);
    this->m_scene->Animate(C3Vector());
    this->m_scene->Draw(M2PASS_0);
    this->m_scene->Draw(M2PASS_1);
}

} // namespace DayNight
