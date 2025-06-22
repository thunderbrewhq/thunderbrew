#include "CSimpleCamera.hpp"

#include <tempest/rect/CRect.hpp>

CSimpleCamera::CSimpleCamera()
    : m_position()
    , m_facing()
    , m_nearZ(0.11111111f)
    , m_farZ(277.77777f)
    , m_fov(1.5707964f)
    , m_aspect(1.0f) {
    this->SetFacing(0.0f, 0.0f, 0.0f);
}

CSimpleCamera::CSimpleCamera(float nearZ, float farZ, float fov)
    : m_position()
    , m_facing()
    , m_nearZ(nearZ)
    , m_farZ(farZ)
    , m_fov(fov)
    , m_aspect(1.0f) {
    this->SetFacing(0.0f, 0.0f, 0.0f);
}
CSimpleCamera::~CSimpleCamera() {
}

C3Vector CSimpleCamera::Forward() {
    return {
        this->m_facing.a0,
        this->m_facing.a1,
        this->m_facing.a2
    };
}

C3Vector CSimpleCamera::Right() {
    return {
        this->m_facing.b0,
        this->m_facing.b1,
        this->m_facing.b2
    };
}

C3Vector CSimpleCamera::Up() {
    return {
        this->m_facing.c0,
        this->m_facing.c1,
        this->m_facing.c2
    };
}

void CSimpleCamera::SetFacing(float yaw, float pitch, float roll) {
    // TODO
}

void CSimpleCamera::SetFacing(const C3Vector& forward, const C3Vector& up) {
    // TODO
}

void CSimpleCamera::SetFacing(const C3Vector& forward) {
    // TODO
}

void CSimpleCamera::SetGxProjectionAndView(const CRect& projectionRect) {
    // TODO
}
