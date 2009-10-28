#pragma once

#include <vector>
#include <string>

class HeightGenerator {
public:
	virtual ~HeightGenerator() { }
	virtual unsigned int getWidth() const = 0;
	virtual unsigned int getHeight() const = 0;
	virtual float getValueAt(unsigned int x, unsigned int y) const = 0;
};


class StaticHeightGenerator :
	public HeightGenerator
{
public:
	StaticHeightGenerator(void) { }
	virtual ~StaticHeightGenerator(void) { }

public:
	virtual unsigned int getWidth() const { return 256; }

	virtual unsigned int getHeight() const { return 256; }

	virtual float getValueAt(unsigned int x, unsigned int y) const {
		return (x * y) / 2.f;
	}
};



class RawHeightSource 
	: public HeightGenerator 
{
public:
	RawHeightSource(std::string const& filename, int width, int height) 
		: width_(width)
		, height_(height)
		, buffer_(new unsigned char[width * height])
	{
		FILE* file = fopen(filename.c_str(), "rb");
		fread(buffer_, 1, width * height, file);
		fclose(file);
	}

	virtual ~RawHeightSource() {
		delete buffer_;
	}

	virtual unsigned int getWidth() const {
		return width_;
	}

	virtual unsigned int getHeight() const {
		return height_;
	}

	virtual float getValueAt(unsigned int x, unsigned int y) const {
		return buffer_[y * height_ + x] / 255.f;
	}
private:
	unsigned char *buffer_;
	unsigned height_;
	unsigned width_;

};


template<
	typename TVertex
>
class HeightMap
{
public:
	typedef std::vector<TVertex> VertexVector;
public:
	HeightMap(float cellSpacing = 1.f)
		: cellSpacing_(cellSpacing)
	{}
	virtual ~HeightMap() {}

	void normalize() {
		float min = 0, max = 0;

		VertexVector::const_iterator citer = vertices_.begin();

		min = max = (*citer).getHeight();

		for(++citer; citer != vertices_.end(); ++citer) {
			float h = (*citer).getHeight();

			if(h < min) {
				min = h;
			}

			if(h > max) {
				max = h;
			}
		}

		float range = max - min;

		VertexVector::iterator iter = vertices_.begin();

		for(; iter != vertices_.end(); ++iter) {
			(*iter).setHeight(((*iter).getHeight() - min) / range);
		}
	}

	void scale(float s) {
		VertexVector::iterator iter = vertices_.begin();

		for(; iter != vertices_.end(); ++iter) {
			(*iter).setHeight((*iter).getHeight() * s);
		}
	}

	void setCellSpacing(float cellSpacing) {
		cellSpacing_ = cellSpacing:
	}

	void setSource(HeightGenerator const& generator) {
		width_ = generator.getWidth();
		height_ = generator.getHeight();

		vertices_.resize(width_ * height_);

		for(unsigned y = 0; y < height_; ++y) {
			for(unsigned x = 0; x < width_; ++x) {
				vertices_[y * height_ + x].setPos(x * cellSpacing_, y * cellSpacing_);
				vertices_[y * height_ + x].setHeight(generator.getValueAt(x, y));
			}
		}
	}

	float shadeCell(int x, int y, D3DXVECTOR3 const& lightDirection) {
		float hA = getHeight(x, y);
		float hB = getHeight(x, y+1);
		float hC = getHeight(x+1, y);

		D3DXVECTOR3 u(cellSpacing_, hB - hA, 0.f);
		D3DXVECTOR3 v(0.f, hC - hA, -cellSpacing_);

		D3DXVECTOR3 n;
		D3DXVec3Cross(&n, &u, &v);
		D3DXVec3Normalize(&n, &n);

		float cosine = -1 * D3DXVec3Dot(&n, &lightDirection);

		if(cosine < 0.f) {
			cosine = 0.f;
		}

		return cosine;
	}

	void slopeLight(D3DXVECTOR3 const& lightDirection) {
		float shade;

		for(unsigned y = 0; y < height_; ++y) {
			for(unsigned x = 0; x < width_; ++x) {
				if(x < height_ - 1 && y < width_ - 1) {
					shade = shadeCell(x, y, lightDirection);
				} else {
					shade = 1.f;
				}
				getVertex(x, y).setColor(D3DXCOLOR(shade, shade, shade, 1.f));
			}
		}
	}

	void genTexture(IDirect3DDevice9 *pDev) {
		HRESULT hr = 0;
	}

	float getHeight(unsigned int x, unsigned int y) {
		return vertices_[y * height_ + x].getHeight();
	}

	TVertex& getVertex(unsigned int x, unsigned int y) {
		return vertices_[y * height_ + x];
	}

	TVertex* getVertices() {
		return &vertices_[0];
	}

	unsigned size() const {
		return width_ * height_;
	}

	unsigned getHeight() const { return height_; }
	unsigned getWidth() const { return width_; }

private:
	VertexVector vertices_;
	unsigned width_;
	unsigned height_;
	float	 cellSpacing_;
};

