#include "stdafx.h"
#include "camera.h"

using d3ddfw::Camera;
using d3ddfw::D3D9Device;

static inline float deg2rad(float a) { return a*0.01745329252f;};
static inline float rad2deg(float a) { return a*57.29577951f;};


Camera::Camera() 
    : pos_(0.f, 0.f, 0.f)
    , up_(0.f, 1.f, 0.f)
    , right_(1.f, 0.f, 0.f)
    , look_(0.f, 0.f, 1.f)
{
}

void Camera::adjustYaw(float angle) {
    D3DXMATRIX m;
    D3DXMatrixRotationY(&m, angle);

    D3DXVec3TransformCoord(&right_, &right_, &m);
    D3DXVec3TransformCoord(&look_, &look_, &m);
}

void Camera::adjustPitch(float angle) {
    D3DXMATRIX m;
    D3DXMatrixRotationAxis(&m, &right_, angle);

    D3DXVec3TransformCoord(&up_, &up_, &m);
    D3DXVec3TransformCoord(&look_, &look_, &m);
}

void Camera::forward(float units) {
    pos_ += look_ * units;
}

void Camera::strafe(float units) {
    pos_ += D3DXVECTOR3(right_.x, 0.f, right_.z) * units;
}

void Camera::rise(float units) {
    pos_ += up_ *= units;
}

void Camera::realize(D3D9Device &dev) {
    D3DXVec3Normalize(&look_, &look_);

    D3DXVec3Cross(&up_, &look_, &right_);
    D3DXVec3Normalize(&up_, &up_);

    D3DXVec3Cross(&right_, &up_, &look_);
    D3DXVec3Normalize(&right_, &right_);

    viewMatrix_(0, 0) = right_.x;
    viewMatrix_(0, 1) = up_.x;
    viewMatrix_(0, 2) = look_.x;
    viewMatrix_(0, 3) = 0.f;

    viewMatrix_(1, 0) = right_.y;
    viewMatrix_(1, 1) = up_.y;
    viewMatrix_(1, 2) = look_.y;
    viewMatrix_(1, 3) = 0.f;

    viewMatrix_(2, 0) = right_.z;
    viewMatrix_(2, 1) = up_.z;
    viewMatrix_(2, 2) = look_.z;
    viewMatrix_(2, 3) = 0.f;

    viewMatrix_(3, 0) = -D3DXVec3Dot(&right_, &pos_);
    viewMatrix_(3, 1) = -D3DXVec3Dot(&up_, &pos_);
    viewMatrix_(3, 2) = -D3DXVec3Dot(&look_, &pos_);
    viewMatrix_(3, 3) = 1.f;

    dev->SetTransform(D3DTS_VIEW, &viewMatrix_);
}


