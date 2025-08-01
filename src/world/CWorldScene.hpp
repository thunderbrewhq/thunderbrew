#ifndef WORLD_C_WORLDSCENE_HPP
#define WORLD_C_WORLDSCENE_HPP

#include <cstdint>
#include <tempest/Vector.hpp>

class CM2Scene;

class CWorldScene {
    public:
    static CM2Scene* s_m2Scene;

    static void Initialize();
    static void Render(const C3Vector& cameraPos, float time);
};

#endif // WORLD_C_WORLDSCENE_HPP
