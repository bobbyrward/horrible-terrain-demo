#pragma once

#include "comptr.h"

namespace d3ddfw {

    class D3DXFont 
        : public ID3DXFontPtr
    {
    public:
        INT DrawTextW(std::wstring const& wstr, UINT x, UINT y, DWORD Format, D3DCOLOR Color) {
            RECT rc={x, y, 0, 0};
            return (*this)->DrawText(NULL, wstr.c_str(), wstr.size(), &rc, Format, Color);
        }

        INT DrawTextW(std::wstring const& wstr, LPRECT pRect, DWORD Format, D3DCOLOR Color) {
            return (*this)->DrawText(NULL, wstr.c_str(), wstr.size(), pRect, Format, Color);
        }

    };
}
