#pragma once


namespace d3ddfw {

    class AABB 
    {
    public:
        AABB();
        AABB(D3DXVECTOR3 const& min, D3DXVECTOR3 const& max);

    public:
        bool pointInBox(D3DXVECTOR3 const& point) const;

    public:
        D3DXVECTOR3     min;
        D3DXVECTOR3     max;
    };
}
