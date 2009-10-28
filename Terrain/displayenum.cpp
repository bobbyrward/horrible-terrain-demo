#include "stdafx.h"
#include "displayenum.h"

unsigned FormatColorBits(D3DFORMAT fmt) {
	switch(fmt) {
		case D3DFMT_X8R8G8B8:
			return 8;
		case D3DFMT_A8R8G8B8:
			return 8;
		case D3DFMT_A2R10G10B10:
			return 10;
		case D3DFMT_X1R5G5B5:
			return 5;
		case D3DFMT_A1R5G5B5:
			return 5;
		case D3DFMT_R5G6B5:
			return 5;
		default:
			return 0;
	}	
}

unsigned FormatAlphaBits(D3DFORMAT fmt) {
	switch(fmt) {
		case D3DFMT_A8R8G8B8:
			return 8;
		case D3DFMT_A2R10G10B10:
			return 2;
		case D3DFMT_A1R5G5B5:
			return 1;
		default:
			return 0;
	}	
}

unsigned FormatDepthBits(D3DFORMAT fmt) {
	switch(fmt) {
		case D3DFMT_D16_LOCKABLE:
			return 16;
		case D3DFMT_D16:
			return 16;
		case D3DFMT_D32:
			return 32;
		case D3DFMT_D32F_LOCKABLE:
			return 32;
		case D3DFMT_D15S1:
			return 15;
		case D3DFMT_D24S8:
			return 24;
		case D3DFMT_D24X8:
			return 24;
		case D3DFMT_D24X4S4:
			return 24;
		case D3DFMT_D24FS8:
			return 24;
		default:
			return 0;
	}	
}

unsigned FormatStencilBits(D3DFORMAT fmt) {
	switch(fmt) {
		case D3DFMT_D15S1:
			return 1;
		case D3DFMT_D24S8:
			return 8;
		case D3DFMT_D24X4S4:
			return 4;
		case D3DFMT_D24FS8:
			return 8;
		default:
			return 0;
	}	
}

static D3DFORMAT backBufferFormats[] = {
        D3DFMT_A2R10G10B10,
        D3DFMT_A8R8G8B8,
        D3DFMT_X8R8G8B8,
        D3DFMT_A1R5G5B5,
        D3DFMT_X1R5G5B5,
        D3DFMT_R5G6B5,
};

static D3DFORMAT displayFormats[] = {
        D3DFMT_A2R10G10B10,
        D3DFMT_X8R8G8B8,
        D3DFMT_X1R5G5B5,
        D3DFMT_R5G6B5,
};

static D3DFORMAT depthStencilFormats[] = {
		//D3DFMT_D16_LOCKABLE,
		D3DFMT_D16,
		D3DFMT_D32,
		//D3DFMT_D32F_LOCKABLE,
		D3DFMT_D15S1,
		D3DFMT_D24S8,
		D3DFMT_D24X8,
		D3DFMT_D24X4S4,
		D3DFMT_D24FS8,
		D3DFMT_D15S1,
		D3DFMT_D24S8,
		D3DFMT_D24X4S4,
		D3DFMT_D24FS8,
};

#define LEN(x) (sizeof(x) / sizeof(x[0]))

typedef std::vector<D3DFORMAT> FormatVector;

static void findDisplayFormats(FormatVector &dFormats, unsigned minColorChannelBits) {
    for(unsigned i=0; i < LEN(displayFormats); ++i) {
        if(FormatColorBits(displayFormats[i]) >= minColorChannelBits) {
            dFormats.push_back(displayFormats[i]);
        }
    }
}

static void findBackBufferFormats(FormatVector &bbFormats, unsigned minColorChannelBits, unsigned minAlphaBits) {
    for(unsigned i=0; i < LEN(backBufferFormats); ++i) {
        if(FormatColorBits(backBufferFormats[i]) >= minColorChannelBits) {
            if(FormatAlphaBits(backBufferFormats[i]) >= minAlphaBits) {
                bbFormats.push_back(backBufferFormats[i]);
            }
        }
    }
}


static void findDepthStencilFormats(FormatVector &dsFormats, unsigned minDepthBits, unsigned minStencilBits) {
    for(unsigned i=0; i < LEN(depthStencilFormats); ++i) {
        if(FormatDepthBits(depthStencilFormats[i]) >= minDepthBits) {
            if(FormatStencilBits(depthStencilFormats[i]) >= minStencilBits) {
                dsFormats.push_back(depthStencilFormats[i]);
            }
        }
    }

}

struct CompareDisplayFormats {
    bool operator()(D3DFORMAT a, D3DFORMAT b) {
        return FormatColorBits(a) > FormatColorBits(b);
    }
};

struct CompareBBFormats {
    bool needsAlpha_;

    CompareBBFormats(bool needsAlpha) 
        : needsAlpha_(needsAlpha)
    {
    }

    bool operator()(D3DFORMAT a, D3DFORMAT b) {
        unsigned colorA = FormatColorBits(a);
        unsigned colorB = FormatColorBits(b);
        unsigned alphaA = FormatAlphaBits(a);
        unsigned alphaB = FormatAlphaBits(b);

        if(!needsAlpha_) {
            if(!alphaA || !alphaB) {
                if(alphaB) {
                    return true;
                }

                if(alphaA) {
                    return false;
                }
            }
        }

        if(colorA == colorB) {
            return alphaA > alphaB;
        }

        return colorA > colorB;
    }
};

struct CompareDSFormats {
    bool needsStencil_;

    CompareDSFormats(bool needsStencil) 
        : needsStencil_(needsStencil)
    {
    }

    bool operator()(D3DFORMAT a, D3DFORMAT b) {
        unsigned depthA = FormatDepthBits(a);
        unsigned depthB = FormatDepthBits(b);
        unsigned stencilA = FormatStencilBits(a);
        unsigned stencilB = FormatStencilBits(b);

        if(!needsStencil_) {
            if(!stencilA || !stencilB) {
                if(stencilB) {
                    return true;
                }

                if(stencilA) {
                    return false;
                }
            }
        }

        if(depthA == depthB) {
            return stencilA > stencilB;
        }

        return depthA > depthB;
    }
};



bool d3ddfw::findAdapterMode(IDirect3D9* d3d, 
		d3ddfw::DisplayFormat& format, bool fullscreen, 
		unsigned minFullscreenWidth, unsigned minFullscreenHeight,
		unsigned minColorChannelBits, unsigned minAlphaBits,
		unsigned minDepthBits, unsigned minStencilBits)
{
    FormatVector allowedDisplayFormats;
    FormatVector allowedBackBufferFormats;
    FormatVector allowedDepthStencilFormats;

    findDisplayFormats(allowedDisplayFormats, minColorChannelBits);
    findBackBufferFormats(allowedBackBufferFormats, minColorChannelBits, minAlphaBits);
    findDepthStencilFormats(allowedDepthStencilFormats, minDepthBits, minStencilBits);

    std::sort(allowedDisplayFormats.begin(), allowedDisplayFormats.end(),
            CompareDisplayFormats());

    std::sort(allowedBackBufferFormats.begin(), allowedBackBufferFormats.end(),
            CompareBBFormats(minAlphaBits > 0));

    std::sort(allowedDepthStencilFormats.begin(), allowedDepthStencilFormats.end(),
            CompareDSFormats(minStencilBits > 0));


    if(!fullscreen) {
        // Don't worry about mode enumeration


        FormatVector::const_iterator dIter;
        FormatVector::const_iterator bbIter;
        FormatVector::const_iterator dsIter;

        for(dIter = allowedDisplayFormats.begin(); dIter != allowedDisplayFormats.end(); ++dIter) {
            for(bbIter = allowedBackBufferFormats.begin(); bbIter != allowedBackBufferFormats.end(); ++bbIter) {
                if(SUCCEEDED(d3d->CheckDeviceType(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, *dIter, *bbIter, fullscreen))) {
                    for(dsIter = allowedDepthStencilFormats.begin(); dsIter != allowedDepthStencilFormats.end(); ++dsIter) {
                        if(SUCCEEDED(d3d->CheckDepthStencilMatch(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, *dIter, *bbIter, *dsIter))) {

                            format.adapterOrdinal = D3DADAPTER_DEFAULT;
                            format.displayFormat = *dIter;
                            format.backBufferFormat = *bbIter;
                            format.depthStencilFormat = *dsIter;
                            format.fullscreen = false;
                            return true;
                        }
                    }
                }
            }
        }

        return false;
    }

    // Cheat a bit.  Just assume they want the resolution the same as they're running now
    d3d->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &format.mode);

    FormatVector::const_iterator dIter;
    FormatVector::const_iterator bbIter;
    FormatVector::const_iterator dsIter;

    for(dIter = allowedDisplayFormats.begin(); dIter != allowedDisplayFormats.end(); ++dIter) {
        for(bbIter = allowedBackBufferFormats.begin(); bbIter != allowedBackBufferFormats.end(); ++bbIter) {
            if(SUCCEEDED(d3d->CheckDeviceType(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, *dIter, *bbIter, fullscreen))) {
                for(dsIter = allowedDepthStencilFormats.begin(); dsIter != allowedDepthStencilFormats.end(); ++dsIter) {
                    if(SUCCEEDED(d3d->CheckDepthStencilMatch(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, *dIter, *bbIter, *dsIter))) {

                        format.adapterOrdinal = D3DADAPTER_DEFAULT;
                        format.displayFormat = *dIter;
                        format.backBufferFormat = *bbIter;
                        format.depthStencilFormat = *dsIter;
                        format.fullscreen = fullscreen;
                        return true;
                    }
                }
            }
        }
    }

    return false;
}
