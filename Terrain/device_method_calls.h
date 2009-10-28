/*************************************************/
/*    This file is autogenerated by midlout2h.   */
/*                 DO NOT EDIT                   */
/*************************************************/

		HRESULT TestCooperativeLevel() {
			return (*this)->TestCooperativeLevel();
		}

		UINT GetAvailableTextureMem() {
			return (*this)->GetAvailableTextureMem();
		}

		HRESULT EvictManagedResources() {
			return (*this)->EvictManagedResources();
		}

		HRESULT GetDirect3D(IDirect3D9** ppD3D9) {
			return (*this)->GetDirect3D(ppD3D9);
		}

		HRESULT GetDeviceCaps(D3DCAPS9* pCaps) {
			return (*this)->GetDeviceCaps(pCaps);
		}

		HRESULT GetDisplayMode(UINT iSwapChain,D3DDISPLAYMODE* pMode) {
			return (*this)->GetDisplayMode(iSwapChain, pMode);
		}

		HRESULT GetCreationParameters(D3DDEVICE_CREATION_PARAMETERS *pParameters) {
			return (*this)->GetCreationParameters(pParameters);
		}

		HRESULT SetCursorProperties(UINT XHotSpot,UINT YHotSpot,IDirect3DSurface9* pCursorBitmap) {
			return (*this)->SetCursorProperties(XHotSpot, YHotSpot, pCursorBitmap);
		}

		void SetCursorPosition(int X,int Y,DWORD Flags) {
			return (*this)->SetCursorPosition(X, Y, Flags);
		}

		BOOL ShowCursor(BOOL bShow) {
			return (*this)->ShowCursor(bShow);
		}

		HRESULT CreateAdditionalSwapChain(D3DPRESENT_PARAMETERS* pPresentationParameters,IDirect3DSwapChain9** pSwapChain) {
			return (*this)->CreateAdditionalSwapChain(pPresentationParameters, pSwapChain);
		}

		HRESULT GetSwapChain(UINT iSwapChain,IDirect3DSwapChain9** pSwapChain) {
			return (*this)->GetSwapChain(iSwapChain, pSwapChain);
		}

		UINT GetNumberOfSwapChains() {
			return (*this)->GetNumberOfSwapChains();
		}

		HRESULT Reset(D3DPRESENT_PARAMETERS* pPresentationParameters) {
			return (*this)->Reset(pPresentationParameters);
		}

		HRESULT Present(CONST RECT* pSourceRect,CONST RECT* pDestRect,HWND hDestWindowOverride,CONST RGNDATA* pDirtyRegion) {
			return (*this)->Present(pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
		}

		HRESULT GetBackBuffer(UINT iSwapChain,UINT iBackBuffer,D3DBACKBUFFER_TYPE Type,IDirect3DSurface9** ppBackBuffer) {
			return (*this)->GetBackBuffer(iSwapChain, iBackBuffer, Type, ppBackBuffer);
		}

		HRESULT GetRasterStatus(UINT iSwapChain,D3DRASTER_STATUS* pRasterStatus) {
			return (*this)->GetRasterStatus(iSwapChain, pRasterStatus);
		}

		HRESULT SetDialogBoxMode(BOOL bEnableDialogs) {
			return (*this)->SetDialogBoxMode(bEnableDialogs);
		}

		void SetGammaRamp(UINT iSwapChain,DWORD Flags,CONST D3DGAMMARAMP* pRamp) {
			return (*this)->SetGammaRamp(iSwapChain, Flags, pRamp);
		}

		void GetGammaRamp(UINT iSwapChain,D3DGAMMARAMP* pRamp) {
			return (*this)->GetGammaRamp(iSwapChain, pRamp);
		}

		HRESULT CreateTexture(UINT Width,UINT Height,UINT Levels,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DTexture9** ppTexture,HANDLE* pSharedHandle) {
			return (*this)->CreateTexture(Width, Height, Levels, Usage, Format, Pool, ppTexture, pSharedHandle);
		}

		HRESULT CreateVolumeTexture(UINT Width,UINT Height,UINT Depth,UINT Levels,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DVolumeTexture9** ppVolumeTexture,HANDLE* pSharedHandle) {
			return (*this)->CreateVolumeTexture(Width, Height, Depth, Levels, Usage, Format, Pool, ppVolumeTexture, pSharedHandle);
		}

		HRESULT CreateCubeTexture(UINT EdgeLength,UINT Levels,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DCubeTexture9** ppCubeTexture,HANDLE* pSharedHandle) {
			return (*this)->CreateCubeTexture(EdgeLength, Levels, Usage, Format, Pool, ppCubeTexture, pSharedHandle);
		}

		HRESULT CreateRenderTarget(UINT Width,UINT Height,D3DFORMAT Format,D3DMULTISAMPLE_TYPE MultiSample,DWORD MultisampleQuality,BOOL Lockable,IDirect3DSurface9** ppSurface,HANDLE* pSharedHandle) {
			return (*this)->CreateRenderTarget(Width, Height, Format, MultiSample, MultisampleQuality, Lockable, ppSurface, pSharedHandle);
		}

		HRESULT CreateDepthStencilSurface(UINT Width,UINT Height,D3DFORMAT Format,D3DMULTISAMPLE_TYPE MultiSample,DWORD MultisampleQuality,BOOL Discard,IDirect3DSurface9** ppSurface,HANDLE* pSharedHandle) {
			return (*this)->CreateDepthStencilSurface(Width, Height, Format, MultiSample, MultisampleQuality, Discard, ppSurface, pSharedHandle);
		}

		HRESULT UpdateSurface(IDirect3DSurface9* pSourceSurface,CONST RECT* pSourceRect,IDirect3DSurface9* pDestinationSurface,CONST POINT* pDestPoint) {
			return (*this)->UpdateSurface(pSourceSurface, pSourceRect, pDestinationSurface, pDestPoint);
		}

		HRESULT UpdateTexture(IDirect3DBaseTexture9* pSourceTexture,IDirect3DBaseTexture9* pDestinationTexture) {
			return (*this)->UpdateTexture(pSourceTexture, pDestinationTexture);
		}

		HRESULT GetRenderTargetData(IDirect3DSurface9* pRenderTarget,IDirect3DSurface9* pDestSurface) {
			return (*this)->GetRenderTargetData(pRenderTarget, pDestSurface);
		}

		HRESULT GetFrontBufferData(UINT iSwapChain,IDirect3DSurface9* pDestSurface) {
			return (*this)->GetFrontBufferData(iSwapChain, pDestSurface);
		}

		HRESULT StretchRect(IDirect3DSurface9* pSourceSurface,CONST RECT* pSourceRect,IDirect3DSurface9* pDestSurface,CONST RECT* pDestRect,D3DTEXTUREFILTERTYPE Filter) {
			return (*this)->StretchRect(pSourceSurface, pSourceRect, pDestSurface, pDestRect, Filter);
		}

		HRESULT ColorFill(IDirect3DSurface9* pSurface,CONST RECT* pRect,D3DCOLOR color) {
			return (*this)->ColorFill(pSurface, pRect, color);
		}

		HRESULT CreateOffscreenPlainSurface(UINT Width,UINT Height,D3DFORMAT Format,D3DPOOL Pool,IDirect3DSurface9** ppSurface,HANDLE* pSharedHandle) {
			return (*this)->CreateOffscreenPlainSurface(Width, Height, Format, Pool, ppSurface, pSharedHandle);
		}

		HRESULT SetRenderTarget(DWORD RenderTargetIndex,IDirect3DSurface9* pRenderTarget) {
			return (*this)->SetRenderTarget(RenderTargetIndex, pRenderTarget);
		}

		HRESULT GetRenderTarget(DWORD RenderTargetIndex,IDirect3DSurface9** ppRenderTarget) {
			return (*this)->GetRenderTarget(RenderTargetIndex, ppRenderTarget);
		}

		HRESULT SetDepthStencilSurface(IDirect3DSurface9* pNewZStencil) {
			return (*this)->SetDepthStencilSurface(pNewZStencil);
		}

		HRESULT GetDepthStencilSurface(IDirect3DSurface9** ppZStencilSurface) {
			return (*this)->GetDepthStencilSurface(ppZStencilSurface);
		}

		HRESULT Clear(DWORD Count,CONST D3DRECT* pRects,DWORD Flags,D3DCOLOR Color,float Z,DWORD Stencil) {
			return (*this)->Clear(Count, pRects, Flags, Color, Z, Stencil);
		}

		HRESULT SetTransform(D3DTRANSFORMSTATETYPE State,CONST D3DMATRIX* pMatrix) {
			return (*this)->SetTransform(State, pMatrix);
		}

		HRESULT GetTransform(D3DTRANSFORMSTATETYPE State,D3DMATRIX* pMatrix) {
			return (*this)->GetTransform(State, pMatrix);
		}

		HRESULT MultiplyTransform(D3DTRANSFORMSTATETYPE State,CONST D3DMATRIX* pMatrix) {
			return (*this)->MultiplyTransform(State, pMatrix);
		}

		HRESULT SetViewport(CONST D3DVIEWPORT9* pViewport) {
			return (*this)->SetViewport(pViewport);
		}

		HRESULT GetViewport(D3DVIEWPORT9* pViewport) {
			return (*this)->GetViewport(pViewport);
		}

		HRESULT SetMaterial(CONST D3DMATERIAL9* pMaterial) {
			return (*this)->SetMaterial(pMaterial);
		}

		HRESULT GetMaterial(D3DMATERIAL9* pMaterial) {
			return (*this)->GetMaterial(pMaterial);
		}

		HRESULT SetLight(DWORD Index,CONST D3DLIGHT9* pLight) {
			return (*this)->SetLight(Index, pLight);
		}

		HRESULT GetLight(DWORD Index,D3DLIGHT9* pLight) {
			return (*this)->GetLight(Index, pLight);
		}

		HRESULT LightEnable(DWORD Index,BOOL Enable) {
			return (*this)->LightEnable(Index, Enable);
		}

		HRESULT GetLightEnable(DWORD Index,BOOL* pEnable) {
			return (*this)->GetLightEnable(Index, pEnable);
		}

		HRESULT SetClipPlane(DWORD Index,CONST float* pPlane) {
			return (*this)->SetClipPlane(Index, pPlane);
		}

		HRESULT GetClipPlane(DWORD Index,float* pPlane) {
			return (*this)->GetClipPlane(Index, pPlane);
		}

		HRESULT SetRenderState(D3DRENDERSTATETYPE State,DWORD Value) {
			return (*this)->SetRenderState(State, Value);
		}

		HRESULT GetRenderState(D3DRENDERSTATETYPE State,DWORD* pValue) {
			return (*this)->GetRenderState(State, pValue);
		}

		HRESULT CreateStateBlock(D3DSTATEBLOCKTYPE Type,IDirect3DStateBlock9** ppSB) {
			return (*this)->CreateStateBlock(Type, ppSB);
		}

		HRESULT BeginStateBlock() {
			return (*this)->BeginStateBlock();
		}

		HRESULT EndStateBlock(IDirect3DStateBlock9** ppSB) {
			return (*this)->EndStateBlock(ppSB);
		}

		HRESULT SetClipStatus(CONST D3DCLIPSTATUS9* pClipStatus) {
			return (*this)->SetClipStatus(pClipStatus);
		}

		HRESULT GetClipStatus(D3DCLIPSTATUS9* pClipStatus) {
			return (*this)->GetClipStatus(pClipStatus);
		}

		HRESULT GetTexture(DWORD Stage,IDirect3DBaseTexture9** ppTexture) {
			return (*this)->GetTexture(Stage, ppTexture);
		}

		HRESULT SetTexture(DWORD Stage,IDirect3DBaseTexture9* pTexture) {
			return (*this)->SetTexture(Stage, pTexture);
		}

		HRESULT GetTextureStageState(DWORD Stage,D3DTEXTURESTAGESTATETYPE Type,DWORD* pValue) {
			return (*this)->GetTextureStageState(Stage, Type, pValue);
		}

		HRESULT SetTextureStageState(DWORD Stage,D3DTEXTURESTAGESTATETYPE Type,DWORD Value) {
			return (*this)->SetTextureStageState(Stage, Type, Value);
		}

		HRESULT GetSamplerState(DWORD Sampler,D3DSAMPLERSTATETYPE Type,DWORD* pValue) {
			return (*this)->GetSamplerState(Sampler, Type, pValue);
		}

		HRESULT SetSamplerState(DWORD Sampler,D3DSAMPLERSTATETYPE Type,DWORD Value) {
			return (*this)->SetSamplerState(Sampler, Type, Value);
		}

		HRESULT ValidateDevice(DWORD* pNumPasses) {
			return (*this)->ValidateDevice(pNumPasses);
		}

		HRESULT SetPaletteEntries(UINT PaletteNumber,CONST PALETTEENTRY* pEntries) {
			return (*this)->SetPaletteEntries(PaletteNumber, pEntries);
		}

		HRESULT GetPaletteEntries(UINT PaletteNumber,PALETTEENTRY* pEntries) {
			return (*this)->GetPaletteEntries(PaletteNumber, pEntries);
		}

		HRESULT SetCurrentTexturePalette(UINT PaletteNumber) {
			return (*this)->SetCurrentTexturePalette(PaletteNumber);
		}

		HRESULT GetCurrentTexturePalette(UINT *PaletteNumber) {
			return (*this)->GetCurrentTexturePalette(PaletteNumber);
		}

		HRESULT SetScissorRect(CONST RECT* pRect) {
			return (*this)->SetScissorRect(pRect);
		}

		HRESULT GetScissorRect(RECT* pRect) {
			return (*this)->GetScissorRect(pRect);
		}

		HRESULT SetSoftwareVertexProcessing(BOOL bSoftware) {
			return (*this)->SetSoftwareVertexProcessing(bSoftware);
		}

		BOOL GetSoftwareVertexProcessing() {
			return (*this)->GetSoftwareVertexProcessing();
		}

		HRESULT SetNPatchMode(float nSegments) {
			return (*this)->SetNPatchMode(nSegments);
		}

		float GetNPatchMode() {
			return (*this)->GetNPatchMode();
		}

		HRESULT ProcessVertices(UINT SrcStartIndex,UINT DestIndex,UINT VertexCount,IDirect3DVertexBuffer9* pDestBuffer,IDirect3DVertexDeclaration9* pVertexDecl,DWORD Flags) {
			return (*this)->ProcessVertices(SrcStartIndex, DestIndex, VertexCount, pDestBuffer, pVertexDecl, Flags);
		}

		HRESULT SetVertexDeclaration(IDirect3DVertexDeclaration9* pDecl) {
			return (*this)->SetVertexDeclaration(pDecl);
		}

		HRESULT GetVertexDeclaration(IDirect3DVertexDeclaration9** ppDecl) {
			return (*this)->GetVertexDeclaration(ppDecl);
		}

		HRESULT SetFVF(DWORD FVF) {
			return (*this)->SetFVF(FVF);
		}

		HRESULT GetFVF(DWORD* pFVF) {
			return (*this)->GetFVF(pFVF);
		}

		HRESULT CreateVertexShader(CONST DWORD* pFunction,IDirect3DVertexShader9** ppShader) {
			return (*this)->CreateVertexShader(pFunction, ppShader);
		}

		HRESULT SetVertexShader(IDirect3DVertexShader9* pShader) {
			return (*this)->SetVertexShader(pShader);
		}

		HRESULT GetVertexShader(IDirect3DVertexShader9** ppShader) {
			return (*this)->GetVertexShader(ppShader);
		}

		HRESULT SetVertexShaderConstantF(UINT StartRegister,CONST float* pConstantData,UINT Vector4fCount) {
			return (*this)->SetVertexShaderConstantF(StartRegister, pConstantData, Vector4fCount);
		}

		HRESULT GetVertexShaderConstantF(UINT StartRegister,float* pConstantData,UINT Vector4fCount) {
			return (*this)->GetVertexShaderConstantF(StartRegister, pConstantData, Vector4fCount);
		}

		HRESULT SetVertexShaderConstantI(UINT StartRegister,CONST int* pConstantData,UINT Vector4iCount) {
			return (*this)->SetVertexShaderConstantI(StartRegister, pConstantData, Vector4iCount);
		}

		HRESULT GetVertexShaderConstantI(UINT StartRegister,int* pConstantData,UINT Vector4iCount) {
			return (*this)->GetVertexShaderConstantI(StartRegister, pConstantData, Vector4iCount);
		}

		HRESULT SetVertexShaderConstantB(UINT StartRegister,CONST BOOL* pConstantData,UINT  BoolCount) {
			return (*this)->SetVertexShaderConstantB(StartRegister, pConstantData, BoolCount);
		}

		HRESULT GetVertexShaderConstantB(UINT StartRegister,BOOL* pConstantData,UINT BoolCount) {
			return (*this)->GetVertexShaderConstantB(StartRegister, pConstantData, BoolCount);
		}

		HRESULT SetStreamSource(UINT StreamNumber,IDirect3DVertexBuffer9* pStreamData,UINT OffsetInBytes,UINT Stride) {
			return (*this)->SetStreamSource(StreamNumber, pStreamData, OffsetInBytes, Stride);
		}

		HRESULT GetStreamSource(UINT StreamNumber,IDirect3DVertexBuffer9** ppStreamData,UINT* OffsetInBytes,UINT* pStride) {
			return (*this)->GetStreamSource(StreamNumber, ppStreamData, OffsetInBytes, pStride);
		}

		HRESULT SetStreamSourceFreq(UINT StreamNumber,UINT Divider) {
			return (*this)->SetStreamSourceFreq(StreamNumber, Divider);
		}

		HRESULT GetStreamSourceFreq(UINT StreamNumber,UINT* Divider) {
			return (*this)->GetStreamSourceFreq(StreamNumber, Divider);
		}

		HRESULT SetIndices(IDirect3DIndexBuffer9* pIndexData) {
			return (*this)->SetIndices(pIndexData);
		}

		HRESULT GetIndices(IDirect3DIndexBuffer9** ppIndexData) {
			return (*this)->GetIndices(ppIndexData);
		}

		HRESULT CreatePixelShader(CONST DWORD* pFunction,IDirect3DPixelShader9** ppShader) {
			return (*this)->CreatePixelShader(pFunction, ppShader);
		}

		HRESULT SetPixelShader(IDirect3DPixelShader9* pShader) {
			return (*this)->SetPixelShader(pShader);
		}

		HRESULT GetPixelShader(IDirect3DPixelShader9** ppShader) {
			return (*this)->GetPixelShader(ppShader);
		}

		HRESULT SetPixelShaderConstantF(UINT StartRegister,CONST float* pConstantData,UINT Vector4fCount) {
			return (*this)->SetPixelShaderConstantF(StartRegister, pConstantData, Vector4fCount);
		}

		HRESULT GetPixelShaderConstantF(UINT StartRegister,float* pConstantData,UINT Vector4fCount) {
			return (*this)->GetPixelShaderConstantF(StartRegister, pConstantData, Vector4fCount);
		}

		HRESULT SetPixelShaderConstantI(UINT StartRegister,CONST int* pConstantData,UINT Vector4iCount) {
			return (*this)->SetPixelShaderConstantI(StartRegister, pConstantData, Vector4iCount);
		}

		HRESULT GetPixelShaderConstantI(UINT StartRegister,int* pConstantData,UINT Vector4iCount) {
			return (*this)->GetPixelShaderConstantI(StartRegister, pConstantData, Vector4iCount);
		}

		HRESULT SetPixelShaderConstantB(UINT StartRegister,CONST BOOL* pConstantData,UINT  BoolCount) {
			return (*this)->SetPixelShaderConstantB(StartRegister, pConstantData, BoolCount);
		}

		HRESULT GetPixelShaderConstantB(UINT StartRegister,BOOL* pConstantData,UINT BoolCount) {
			return (*this)->GetPixelShaderConstantB(StartRegister, pConstantData, BoolCount);
		}

		HRESULT DrawRectPatch(UINT Handle,CONST float* pNumSegs,CONST D3DRECTPATCH_INFO* pRectPatchInfo) {
			return (*this)->DrawRectPatch(Handle, pNumSegs, pRectPatchInfo);
		}

		HRESULT DrawTriPatch(UINT Handle,CONST float* pNumSegs,CONST D3DTRIPATCH_INFO* pTriPatchInfo) {
			return (*this)->DrawTriPatch(Handle, pNumSegs, pTriPatchInfo);
		}

		HRESULT DeletePatch(UINT Handle) {
			return (*this)->DeletePatch(Handle);
		}

		HRESULT CreateQuery(D3DQUERYTYPE Type,IDirect3DQuery9** ppQuery) {
			return (*this)->CreateQuery(Type, ppQuery);
		}
