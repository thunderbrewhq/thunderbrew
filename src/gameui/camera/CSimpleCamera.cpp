#include "CSimpleCamera.hpp"

#include <tempest/rect/CRect.hpp>
#include <tempest/Math.hpp>
#include <tempest/matrix/C44Matrix.hpp>

#include "gx/Transform.hpp"


static void FaceDirection(const C3Vector& direction, C3Vector* xprime, C3Vector* yprime, C3Vector* zprime) {
    STORM_ASSERT(!CMath::fequal(direction.SquaredMag(), 0.0));

    *xprime = direction;

    yprime->x = -xprime->y;
    yprime->y = xprime->x;
    yprime->z = 0.0f;

    if (yprime->x == 0.0 && yprime->y == 0.0) {
        yprime->y = 1.1920929e-7f;
    }

    CMath::normalize(yprime->x, yprime->y);

    zprime->x = -xprime->z * yprime->y;
    zprime->y = xprime->z * yprime->x;
    zprime->z = xprime->x * yprime->y - xprime->y * yprime->x;
}

static void FaceDirectionWithRoll(const C3Vector& direction, const C3Vector& up, C3Vector* xprime, C3Vector* yprime, C3Vector* zprime) {
    STORM_ASSERT(!CMath::fequal(direction.SquaredMag(), 0.0));

    *xprime = direction;

    float dot = CMath::fabs(C3Vector::Dot(up, *xprime));
    if (CMath::fequal(dot, 1.0)) {
        yprime->x = 1.0f;
        yprime->y = 0.0f;
        yprime->z = 0.0f;
    } else {
        *yprime = C3Vector::Cross(up, *xprime);
        yprime->Normalize();
    }

    *zprime = C3Vector::Cross(*xprime, *yprime);
}

static void BuildBillboardMatrix(const C3Vector& direction, C33Matrix* rotation) {
    C3Vector xprime;
    C3Vector yprime;
    C3Vector zprime;
    FaceDirection(direction, &xprime, &yprime, &zprime);

    rotation->a0 = xprime.x;
    rotation->a1 = xprime.y;
    rotation->a2 = xprime.z;

    rotation->b0 = yprime.x;
    rotation->b1 = yprime.y;
    rotation->b2 = yprime.z;

    rotation->c0 = zprime.x;
    rotation->c1 = zprime.y;
    rotation->c2 = zprime.z;
}

static void BuildBillboardMatrixWithRoll(const C3Vector& direction, const C3Vector& up, C33Matrix* rotation) {
    C3Vector xprime;
    C3Vector yprime;
    C3Vector zprime;
    FaceDirectionWithRoll(direction, up, &xprime, &yprime, &zprime);

    rotation->a0 = xprime.x;
    rotation->a1 = xprime.y;
    rotation->a2 = xprime.z;

    rotation->b0 = yprime.x;
    rotation->b1 = yprime.y;
    rotation->b2 = yprime.z;

    rotation->c0 = zprime.x;
    rotation->c1 = zprime.y;
    rotation->c2 = zprime.z;
}

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
    this->m_facing.FromEulerAnglesZYX(yaw, pitch, roll);
}

void CSimpleCamera::SetFacing(const C3Vector& forward, const C3Vector& up) {
    BuildBillboardMatrixWithRoll(forward, up, &this->m_facing);
}

void CSimpleCamera::SetFacing(const C3Vector& forward) {
    BuildBillboardMatrix(forward, &this->m_facing);
}

void CSimpleCamera::SetGxProjectionAndView(const CRect& projectionRect) {
    this->m_aspect = (projectionRect.maxX - projectionRect.minX) / (projectionRect.maxY - projectionRect.minY);

    C44Matrix mProj;
    GxuXformCreateProjection_SG(this->m_fov, this->m_aspect, this->m_nearZ, this->m_farZ, mProj);
    GxXformSetProjection(mProj);

    C44Matrix mView;
    GxuXformCreateLookAtSgCompat(C3Vector(), Forward(), Up(), mView);
    GxXformSetView(mView);
}
