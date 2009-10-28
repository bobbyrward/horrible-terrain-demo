#pragma once

#include "device.h"

namespace d3ddfw {
    class Camera
    {
    public:
        Camera();

        void adjustYaw(float angle);
        void adjustPitch(float angle);

        void forward(float units);
        void strafe(float units);
        void rise(float units);

        void realize(D3D9Device &dev);

    public:
        D3DXMATRIX      viewMatrix_;
        D3DXVECTOR3     pos_;
        D3DXVECTOR3     up_;
        D3DXVECTOR3     right_;
        D3DXVECTOR3     look_;
    };
}

