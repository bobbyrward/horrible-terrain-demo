#pragma once

#include "comptr.h"

namespace d3ddfw {

	struct DisplayFormat {
		UINT			adapterOrdinal;
        bool			fullscreen;
		D3DFORMAT		displayFormat;
		D3DFORMAT		backBufferFormat;
		D3DFORMAT		depthStencilFormat;
		D3DDISPLAYMODE	mode;
	};


	bool findAdapterMode(IDirect3D9* d3d,
		DisplayFormat& format, bool fullscreen, 
		unsigned minFullscreenWidth, unsigned minFullscreenHeight,
		unsigned minColorChannelBits, unsigned minAlphaBits,
		unsigned minDepthBits, unsigned minStencilBits);
}
