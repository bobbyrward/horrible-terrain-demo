#pragma once

#include "device.h"

namespace d3ddfw {

    class Terrain
    {
    public:
        struct Vertex {
            D3DXVECTOR3     pos;
            D3DXVECTOR2     tex;
        };

        struct Triangle {
            unsigned long   v0;
            unsigned long   v1;
            unsigned long   v2;

            Triangle();
            Triangle(unsigned long a, unsigned long b, unsigned long c);
        };

        static D3DVERTEXELEMENT9 vertexElements[3];

    public:
        Terrain();

        bool loadHeightmap(std::string const& rawFilename, unsigned width, unsigned height, 
                float cellSpacing, float heightScale);

        void clear();

    public:
        unsigned char getRawHeightAt(unsigned x, unsigned y) const;
        float getScaledHeightAt(unsigned x, unsigned y) const;

        float getHeightAt(float x, float z) const;

        D3DXVECTOR3 const& getTerrainSize() const ;
        void getTerrainBB(D3DXVECTOR3 *pMin, D3DXVECTOR3 *pMax) const;

        bool restoreUnmanagedResources(D3D9Device &dev);
        void destroyUnmanagedResources(D3D9Device &dev);

        void render(D3D9Device &dev);

    private:
        void buildVertices();
        void buildTriangles();
        bool genTexture(D3D9Device &dev, D3DXVECTOR3 const& lightDir);
        float computeShade(int x, int y, D3DXVECTOR3 const& lightDir);

    private:
        unsigned                        width_;
        unsigned                        height_;
        float                           cellSpacing_;
        float                           heightScale_;
        unsigned                        triangleCount_;
        D3DXVECTOR3                     size_;
        D3DXVECTOR3                     bbMin_;
        D3DXVECTOR3                     bbMax_;
        std::vector<unsigned char>      heights_;
        std::vector<Vertex>             vertices_;
        std::vector<Triangle>           triangles_;
        D3D9VertexBuffer                vertexBuffer_;
        D3D9IndexBuffer                 indexBuffer_;
        IDirect3DTexture9Ptr            texture_;
        IDirect3DVertexDeclaration9Ptr  vertexDecl_;

    };
}
