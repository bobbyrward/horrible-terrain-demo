#include "stdafx.h"
#include "vertexbuffer.h"
#include "device.h"
#include "terrain.h"
#include "logging.h"

#pragma warning(disable: 4996)

const D3DXCOLOR     BEACH_SAND         (D3DCOLOR_XRGB(255, 249, 157));
const D3DXCOLOR     LIGHT_YELLOW_GREEN (D3DCOLOR_XRGB(124, 197, 118));
const D3DXCOLOR     PUREGREEN          (D3DCOLOR_XRGB(  0, 166,  81));
const D3DXCOLOR     DARK_YELLOW_GREEN  (D3DCOLOR_XRGB( 25, 123,  48));
const D3DXCOLOR     DARKBROWN          (D3DCOLOR_XRGB(115, 100,  87));
const D3DXCOLOR     WHITE              (D3DCOLOR_XRGB(255, 255, 255));

using d3ddfw::Terrain;
using d3ddfw::D3D9Device;
using d3ddfw::Logging;

D3DVERTEXELEMENT9 Terrain::vertexElements[3] = {
    { 0,  0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
    { 0, 12, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
    D3DDECL_END()
};

Terrain::Triangle::Triangle() 
    : v0()
    , v1()
    , v2()
{
}

Terrain::Triangle::Triangle(unsigned long a, unsigned long b, unsigned long c) 
    : v0(a)
    , v1(b)
    , v2(c)
{

}

Terrain::Terrain()
{
}

bool Terrain::loadHeightmap(std::string const& rawFilename, unsigned width, unsigned height, 
        float cellSpacing, float heightScale) 
{
    clear();

    FILE *file = fopen(rawFilename.c_str(), "rb");

    if(!file) {
        return false;
    }

    width_ = width;
    height_ = height;
    cellSpacing_ = cellSpacing;
    heightScale_ = heightScale;
    size_ = D3DXVECTOR3(
                cellSpacing * (width - 1), 
                0.f, /* still unknown */
                cellSpacing * (height - 1)
            );


    bbMin_ = size_ * -0.5f;
    bbMax_ = size_ * 0.5f;

    triangles_.resize((width-1) * (height-1) * 2);
    heights_.resize(width * height);
    vertices_.resize(width * height);

    size_t read = fread(&heights_[0], 1, heights_.size(), file);

    if(read != heights_.size()) {
        clear();
        return false;
    }

    fclose(file);

    buildVertices();
    buildTriangles();

    return true;
}

void Terrain::buildVertices() {
    D3DXVECTOR3 start = size_ * -0.5f;
    D3DXVECTOR2 uvCoordSize(1.f / (width_ - 1), 1.f / (height_ - 1));

    float maxHeight = -1.f;
    float minHeight = -1.f;

    for(unsigned heightY = 0; heightY < height_; ++heightY) {
        for(unsigned heightX = 0; heightX < width_; ++ heightX) {
            unsigned index = heightY * width_ + heightX;
            Vertex&  v     = vertices_[index];

            v.pos.x = start.x + (cellSpacing_ * heightX);
            v.pos.z = start.z + (cellSpacing_ * heightY);
            v.pos.y = heights_[index] * heightScale_;
            
            if(maxHeight == -1.f) {
                maxHeight = v.pos.y;
                minHeight = v.pos.y;
            } 
            
            if(maxHeight < v.pos.y) {
                maxHeight = v.pos.y;
            }

            if(minHeight > v.pos.y) {
                minHeight = v.pos.y;
            }

            v.tex.x = uvCoordSize.x * heightX;
            v.tex.y = uvCoordSize.y * heightY;
        }
    }

    bbMin_.y = minHeight;
    bbMax_.y = maxHeight;
}

void Terrain::buildTriangles() {
    unsigned idx = 0;

    for(unsigned z = 0; z < height_ - 1; ++z) {
        for(unsigned x = 0; x < width_ -1; ++x, idx += 2) {
            triangles_[idx + 0] = Triangle( (z+0) * width_ + (x+0)
                                          , (z+0) * width_ + (x+1)
                                          , (z+1) * width_ + (x+0)
                                          );

            triangles_[idx + 1] = Triangle( (z+1) * width_ + (x+0)
                                          , (z+0) * width_ + (x+1)
                                          , (z+1) * width_ + (x+1)
                                          );

        }
    }
}

unsigned char Terrain::getRawHeightAt(unsigned x, unsigned y) const {
    return heights_[y * width_ + x];
}

float Terrain::getScaledHeightAt(unsigned x, unsigned y) const {
    return heights_[y * width_ + x] * heightScale_;
}


inline float lerp1d(float a, float b, float delta) {
    return a - (a*delta) + (b*delta);
}

void Terrain::getTerrainBB(D3DXVECTOR3 *pMin, D3DXVECTOR3 *pMax) const {
    *pMin = bbMin_;
    *pMax = bbMax_;
}

D3DXVECTOR3 const& Terrain::getTerrainSize() const {
    return size_;
}

float Terrain::getHeightAt(float x, float z) const {
    x = (size_.x / 2.f + x) / cellSpacing_;
    z = (size_.z / 2.f + z) / cellSpacing_;

    float col = floorf(x);
    float row = floorf(z);

#pragma warning(push)
#pragma warning(disable: 4244)
    float hA = getScaledHeightAt(col,   row);
    float hB = getScaledHeightAt(col+1, row);
    float hC = getScaledHeightAt(col,   row+1);
    float hD = getScaledHeightAt(col+1, row+1);
#pragma warning(pop)

    float dx = x - col;
    float dz = z - row;

    if(dz < 1.f - dx) {
        float uy = hB - hA;
        float vy = hC - hA;

        return hA + lerp1d(0.f, uy, dx) + lerp1d(0.f, vy, dz);
    } else {
        float uy = hC - hD;
        float vy = hB - hD;

        return hD + lerp1d(0.f, uy, 1.f - dx) + lerp1d(0.f, vy, 1.f - dz);
    }
}

void Terrain::clear() {
    heights_.clear();
    vertices_.clear();
}

bool Terrain::restoreUnmanagedResources(D3D9Device &dev) {
    vertexDecl_ = dev->CreateVertexDeclaration(vertexElements);

    vertexBuffer_ = dev->CreateVertexBuffer(
            vertices_.size() * sizeof(Vertex),
            D3DUSAGE_WRITEONLY,
            0,
            D3DPOOL_DEFAULT);

    indexBuffer_ = dev->CreateIndexBuffer(
            triangles_.size() * 3 * sizeof(unsigned long),
            D3DUSAGE_WRITEONLY,
            D3DFMT_INDEX32,
            D3DPOOL_DEFAULT);

    if(!vertexDecl_ || !vertexBuffer_ || !indexBuffer_) {
        return false;
    }

    Vertex *pv = vertexBuffer_.Lock<Vertex>(0, 0, 0);
    if(!pv) {
        return false;
    }

    std::vector<Vertex>::const_iterator vertexIter = vertices_.begin();
    for(; vertexIter != vertices_.end(); ++vertexIter) {
        (*pv++) = (*vertexIter);
    }

    vertexBuffer_->Unlock();

    Triangle *pt = indexBuffer_.Lock<Triangle>(0, 0, 0);
    if(!pt) {
        return false;
    }

    std::vector<Triangle>::const_iterator triangleIter = triangles_.begin();
    for(; triangleIter != triangles_.end(); ++triangleIter) {
        (*pt++) = (*triangleIter);
    }

    indexBuffer_->Unlock();

    if(!genTexture(dev, D3DXVECTOR3(0.f, 1.f, 0.f))) {
        return false;
    }

    return true;
}

void Terrain::destroyUnmanagedResources(D3D9Device &dev) {
    vertexBuffer_.clear();
    indexBuffer_.clear();
    vertexDecl_.clear();
    texture_.clear();
}

bool Terrain::genTexture(D3D9Device &dev, D3DXVECTOR3 const& lightDir) {
    unsigned texWidth = width_ - 1;
    unsigned texHeight = height_ - 1;

    HRESULT hr = D3DXCreateTexture(dev->iface(), texWidth, texHeight,
            0, 0, D3DFMT_X8R8G8B8, D3DPOOL_MANAGED, &texture_);

    if(FAILED(hr)) {
        return false;
    }

    D3DSURFACE_DESC texDesc;
    texture_->GetLevelDesc(0, &texDesc);

    if(texDesc.Format != D3DFMT_X8R8G8B8) {
        return false;
    }

    D3DLOCKED_RECT lr = {};

    hr = texture_->LockRect(0, &lr, 0, 0);
    if(FAILED(hr)) {
        return false;
    }

    unsigned long *bits = reinterpret_cast<unsigned long *>(lr.pBits);

    for(unsigned y = 0; y < texHeight; ++y) {
        for(unsigned x = 0; x < texWidth; ++x) {
            D3DXCOLOR c;

            float height = getScaledHeightAt(x, y);

            if(height < 42.5f)          c = BEACH_SAND;
            else if(height < 85.0f)     c = LIGHT_YELLOW_GREEN;
            else if(height < 127.5f)    c = PUREGREEN;
            else if(height < 170.0f)    c = DARK_YELLOW_GREEN;
            else if(height < 212.5f)    c = DARKBROWN;
            else                        c = WHITE;

			c *= computeShade(x, y, lightDir);

            bits[(y *  lr.Pitch / 4) + x] = c;

        }
    }

    texture_->UnlockRect(0);

	hr = D3DXFilterTexture(texture_, 0, 0, D3DX_DEFAULT);
	if(FAILED(hr)) {
		return false;
	}

	return true;

}

float Terrain::computeShade(int x, int y, D3DXVECTOR3 const& lightDir) {
	float hA = getRawHeightAt(x, y);
	float hB = getRawHeightAt(x+1, y);
	float hC = getRawHeightAt(x, y+1);

    D3DXVECTOR3 u(cellSpacing_, hB - hA, 0.f);
    D3DXVECTOR3 v(0.f,          hC - hA, -cellSpacing_);

	D3DXVECTOR3 n;
	D3DXVec3Cross(&n, &u, &v);
	D3DXVec3Normalize(&n, &n);

	float cosine = D3DXVec3Dot(&n, &lightDir);

	if(cosine < 0.0f)
		cosine = 0.0f;

	return cosine;
}

void Terrain::render(D3D9Device &dev) {
    dev->SetVertexDeclaration(vertexDecl_);
    dev->SetStreamSource(0, vertexBuffer_, 0, sizeof(Vertex));
    dev->SetIndices(indexBuffer_);
    dev->SetTexture(0, texture_);

    dev->SetRenderState(D3DRS_LIGHTING, false);

    HRESULT hr;

    hr = dev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 
            vertices_.size(), 0, triangles_.size());

    if(FAILED(hr)) {
        Logging::outputMessage("ERROR: Terrain DrawIndPrim call failed\n");
    }

    dev->SetRenderState(D3DRS_LIGHTING, true);
    /*
    dev->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

    hr = dev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 
            vertices_.size(), 0, triangles_.size());

    if(FAILED(hr)) {
        Logging::outputMessage("ERROR: Second Terrain DrawIndPrim call failed\n");
        return;
    }

    dev->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
    */
}

