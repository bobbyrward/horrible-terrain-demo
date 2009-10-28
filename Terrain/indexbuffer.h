#pragma once

#include "comptr.h"

namespace d3ddfw {
    class D3D9IndexBuffer
        : public IDirect3DIndexBuffer9Ptr
    {
    public:
        template<typename T>
        T* Lock(UINT OffsetToLock, UINT SizeToLock, DWORD Flags) {
            T* p;
            HRESULT hr = (*this)->Lock(OffsetToLock, SizeToLock, reinterpret_cast<void**>(&p), Flags);
            if(FAILED(hr)) {
                return NULL;
            }
            return p;
        }

        void Unlock() {
            (*this)->Unlock();
        }

    };
}


