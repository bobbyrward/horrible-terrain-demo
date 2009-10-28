#pragma once

namespace d3ddfw {

    template<typename IInterface>
    class comptr;

    template<typename IInterface>
    IInterface *queryInterface(IUnknown* pUnk) {
        HRESULT hr = 0;
        IInterface *pIface = NULL;

        if(!pUnk) {
            return NULL;
        }

        hr = pUnk->QueryInterface(__uuidof(IInterface), &pIface);

        if(!SUCCEEDED(hr)) {
            return NULL;
        }

        return pIface;
    }

    template<typename IInterface, typename IIncomingInterface>
    IInterface *queryInterface(comptr<IIncomingInterface> &pUnk) {
        HRESULT hr = 0;
        comptr<IInterface> iface;

        if(!pUnk) {
            return NULL;
        }

        hr = pUnk->QueryInterface(__uuidof(IInterface), &iface);

        if(!SUCCEEDED(hr)) {
            return NULL;
        }

        return iface;
    }


    template<typename IInterface>
    class comptr {
    public:
        comptr()
            : pi(NULL)
        { }

        comptr(comptr<IInterface> const& rhs)
            : pi(NULL)
        {
            *this = rhs;
        }

        explicit comptr(IUnknown *pUnk)
            : pi(NULL)
        {
            pi = queryInterface(pUnk);
            pUnk->Release();
        }

        virtual ~comptr() {
            clear();
        }

        ULONG AddRef() {
            if(pi) {
                return pi->AddRef();
            }
            return 0;
        }

        ULONG Release() {
            if(pi) {
                return pi->Release();
            }
            return 0;
        }

        ULONG clear() {
            ULONG count = 0;

            if(pi) {
                count = Release();
                pi = NULL;
            }

            return count;
        }

        void attach(IInterface *p) {
            clear();
            pi = p;
        }

        IInterface* detach() {
            IInterface p = pi;
            pi = NULL;
            return p;
        }

        operator bool() const {
            return pi != NULL;
        }

        operator IInterface*() {
            return pi;
        }

        IInterface* operator -> () {
            return pi;
        }

        IInterface* iface() {
            return pi;
        }

        IInterface** operator & () {
            return &pi;
        }

        comptr& operator = (comptr<IInterface> const& rhs) {
            attach(rhs.pi);
            AddRef();
            return *this;
        }

    private:
        IInterface *pi;

    };


#if(DIRECT3D_VERSION >= 0x0900)
    typedef comptr<IDirect3D9>                  IDirect3D9Ptr;
    typedef comptr<IDirect3DBaseTexture9>       IDirect3DBaseTexture9Ptr;
    typedef comptr<IDirect3DCubeTexture9>       IDirect3DCubeTexture9Ptr;
    typedef comptr<IDirect3DDevice9>            IDirect3DDevice9Ptr;
    typedef comptr<IDirect3DIndexBuffer9>       IDirect3DIndexBuffer9Ptr;
    typedef comptr<IDirect3DPixelShader9>       IDirect3DPixelShader9Ptr;
    typedef comptr<IDirect3DQuery9>             IDirect3DQuery9Ptr;
    typedef comptr<IDirect3DResource9>          IDirect3DResource9Ptr;
    typedef comptr<IDirect3DStateBlock9>        IDirect3DStateBlock9Ptr;
    typedef comptr<IDirect3DSurface9>           IDirect3DSurface9Ptr;
    typedef comptr<IDirect3DSwapChain9>         IDirect3DSwapChain9Ptr;
    typedef comptr<IDirect3DTexture9>           IDirect3DTexture9Ptr;
    typedef comptr<IDirect3DVertexBuffer9>      IDirect3DVertexBuffer9Ptr;
    typedef comptr<IDirect3DVertexDeclaration9> IDirect3DVertexDeclaration9Ptr;
    typedef comptr<IDirect3DVertexShader9>      IDirect3DVertexShader9Ptr;
    typedef comptr<IDirect3DVolume9>            IDirect3DVolume9Ptr;
    typedef comptr<IDirect3DVolumeTexture9>     IDirect3DVolumeTexture9Ptr;

#endif

#if(D3DX_VERSION >= 0x0900)
    typedef comptr<ID3DXBuffer>                 ID3DXBufferPtr;
    typedef comptr<ID3DXFont>                   ID3DXFontPtr;
    typedef comptr<ID3DXSprite>                 ID3DXSpritePtr;
    typedef comptr<ID3DXRenderToSurface>        ID3DXRenderToSurfacePtr;
    typedef comptr<ID3DXRenderToEnvMap>         ID3DXRenderToEnvMapPtr;
    typedef comptr<ID3DXLine>                   ID3DXLinePtr;
#endif

}

