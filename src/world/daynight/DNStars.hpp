#ifndef WORLD_DAY_NIGHT_STARS_HPP
#define WORLD_DAY_NIGHT_STARS_HPP


#include <cstdint>
#include <tempest/Vector.hpp>


class CM2Scene;
class CM2Model;


namespace DayNight {

class DNStars {
    public:
    void Initialize();
    void Destroy();
    void Update();
    void Render();

    CM2Scene* m_scene = nullptr;
    CM2Model* m_model = nullptr;
    CImVector m_color { 0 };
    C3Vector m_pos;
    uint32_t m_time = 0;
};

} // namespace DayNight


#endif
