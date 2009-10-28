#include "stdafx.h"
#include "application.h"
#include "camera.h"
#include "logging.h"
#include "terrain.h"

#include "limits.h"

class TestApp
	: public d3ddfw::Application<TestApp>
{
public:
    typedef d3ddfw::Application<TestApp> Base;
public:
	BEGIN_EVENT_MAP(TestApp)
        EVENT_WM_LBUTTONDOWN(onLeftMouseDown)
        EVENT_WM_LBUTTONUP(onLeftMouseUp)
        EVENT_WM_MOUSEMOVE(onMouseMove)
        EVENT_WM_KEYUP(onKeyDown)
		EVENT_CHAIN(Base)
	END_EVENT_MAP()

public:
	TestApp()
		: Base(L"Test D3DDFW")
        , trackingMouse_(false)
        , lastMouseX_(0)
        , lastMouseY_(0)
        , mouseDeltaX_(0)
        , mouseDeltaY_(0)
	{
	}

    bool getDisplayFormat(d3ddfw::DisplayFormat &format) {
        // Look for a windowed format(width=0, height=0 since not fullscreen) 
        // with atleast 5 bits per color channel, no alpha nessecary
        // with atleast 15 bit depth with no stencil nessecary
        //return d3ddfw::findAdapterMode(d3d_, format, false, 0, 0, 5, 0, 15, 0);


        // Go fullscreen.  Use current resolution 
        return d3ddfw::findAdapterMode(d3d_, format, true, 0, 0, 5, 0, 15, 0);
    }
    
    bool initialize() { 
        //if(!terrain_.loadHeightmap("Terrain-512x512.raw", 512, 512, 1.f, 0.1f)) {
        if(!terrain_.loadHeightmap("output.raw", 512, 512, 5.f, 0.75f)) {
            return false;
        }

		D3DXVECTOR3 bbMin, bbMax;
		terrain_.getTerrainBB(&bbMin, &bbMax);
		
		camera_.pos_.x = bbMin.x + (bbMax.x - bbMin.x) / 2.f;
		camera_.pos_.z = bbMin.z + (bbMax.z - bbMin.z) / 2.f;
        camera_.pos_.y = 5.f + terrain_.getHeightAt(camera_.pos_.x, camera_.pos_.z);

        if(!Base::initialize()) {
            return false;
        }

        return true;
    }

    void update(float elapsedTime) {
        camera_.adjustPitch(mouseDeltaY_ * -0.01f);
        camera_.adjustYaw(mouseDeltaX_ * -0.01f);

        mouseDeltaX_ = 0;
        mouseDeltaY_ = 0;

        float movementNudge = 100.f;
        if(GetAsyncKeyState('W'))       camera_.forward( movementNudge * elapsedTime);
        if(GetAsyncKeyState('S'))       camera_.forward(-movementNudge * elapsedTime);
        if(GetAsyncKeyState('A'))       camera_.strafe(-movementNudge * elapsedTime);
        if(GetAsyncKeyState('D'))       camera_.strafe( movementNudge * elapsedTime);
        if(GetAsyncKeyState('R'))       camera_.rise( movementNudge * elapsedTime);
        if(GetAsyncKeyState('F'))       camera_.rise(-movementNudge * elapsedTime);

        if(GetAsyncKeyState(VK_TAB))    device_->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

        D3DXVECTOR3 const& tSize = terrain_.getTerrainSize();
		D3DXVECTOR3 bbMin, bbMax;
		terrain_.getTerrainBB(&bbMin, &bbMax);

		if(camera_.pos_.x > bbMax.x) {
            camera_.pos_.x = bbMax.x;
        }

		if(camera_.pos_.x < bbMin.x) {
            camera_.pos_.x = bbMin.x;
        }

		if(camera_.pos_.z > bbMax.z) {
            camera_.pos_.z = bbMax.z;
        }

		if(camera_.pos_.z < bbMin.z) {
            camera_.pos_.z = bbMin.z;
        }

        camera_.pos_.y = 5.f + terrain_.getHeightAt(camera_.pos_.x, camera_.pos_.z);

        static boost::wformat statsFormatter(
                L"\nPos: (%0.2f, %0.2f, %0.2f)"
                L"\nLook: (%0.2f, %0.2f, %0.2f)"
                L"\nUp: (%0.2f, %0.2f, %0.2f)"
                L"\nRight: (%0.2f, %0.2f, %0.2f)"
                );

        cameraString_ = boost::str(boost::wformat(statsFormatter) 
                % camera_.pos_.x   % camera_.pos_.y   % camera_.pos_.z
                % camera_.look_.x  % camera_.look_.y  % camera_.look_.z
                % camera_.up_.x    % camera_.up_.y    % camera_.up_.z
                % camera_.right_.x % camera_.right_.y % camera_.right_.z
                );

    }

	void render() {
		device_->Clear( 0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0,0,255), 1.0f, 0 );
		if(SUCCEEDED(device_->BeginScene())) {
            camera_.realize(device_);

            terrain_.render(device_);

//            font_->Begin();
            statsString_ += cameraString_;
            font_.DrawText(statsString_, 5, 5, DT_NOCLIP, D3DCOLOR_XRGB(0,0,0));
//            font_->End();

			device_->EndScene();
		}
	}

    bool restoredUnmanagedResources() {
        D3DXMATRIX mView;
        D3DXMATRIX mProj;

        RECT rc={0};
        GetClientRect(windowHandle(), &rc);
        D3DXMatrixPerspectiveFovLH( &mProj, D3DX_PI/4, rc.right/(float)rc.bottom, 1.0f, 1000.0f );
        device_->SetTransform( D3DTS_PROJECTION, &mProj );

        // Turn off culling, so we see the front and back of the triangle
        device_->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );

        if(!terrain_.restoreUnmanagedResources(device_)) {
            return false;
        }

        D3DXMATRIX m;
        D3DXMatrixIdentity(&m);
        device_->SetTransform(D3DTS_WORLD, &m);

        return Base::restoreUnmanagedResources();
    }

    void destroyUnmanagedResources() {
        terrain_.destroyUnmanagedResources(device_);
        Base::destroyUnmanagedResources();
    }

    LRESULT onLeftMouseDown(UINT x, UINT y) {
        SetCapture();
        trackingMouse_ = true;
        mouseDeltaX_ = 0;
        mouseDeltaY_ = 0;
        lastMouseX_ = x;
        lastMouseY_ = y;
        return 0;
    }

    LRESULT onLeftMouseUp(UINT x, UINT y) {
        trackingMouse_ = false;
        mouseDeltaX_ = 0;
        mouseDeltaY_ = 0;
        ReleaseCapture();
        return 0;
    }

    LRESULT onMouseMove(UINT x, UINT y) {
        if(trackingMouse_) {
            mouseDeltaX_ = (int)x - lastMouseX_;
            mouseDeltaY_ = (int)y - lastMouseY_;
            lastMouseX_ = x;
            lastMouseY_ = y;
        }

        return Base::onMouseMove(x, y);
    }

    LRESULT onKeyDown(WPARAM vkey) {
        switch(vkey) {
            case VK_ESCAPE:
                DestroyWindow();
                break;
        }

        return DefWindowProc();
    }

private:
    d3ddfw::Camera                          camera_;
    bool                                    trackingMouse_;
    UINT                                    lastMouseX_;
    UINT                                    lastMouseY_;
    int                                     mouseDeltaX_;
    int                                     mouseDeltaY_;
    d3ddfw::Terrain                         terrain_;
    std::wstring                            cameraString_;
};



INT WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, INT) {
	TestApp test;

	test.run();

	return 0;
}
