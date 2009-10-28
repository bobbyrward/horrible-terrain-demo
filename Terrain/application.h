#pragma once

#include "logging.h"
#include "comptr.h"
#include "window.h"
#include "displayenum.h"
#include "device.h"
#include "timer.h"

namespace d3ddfw {

#define CALL_DERIVED(func) \
	static_cast<TBase*>(this)->func

	template<typename TBase>
	class Application 
		: public d3ddfw::Window<TBase>
	{
	public:
		BEGIN_EVENT_MAP(TestWindow)
			EVENT_WM_DESTROY(onDestroy)
            EVENT_WM_MOUSEMOVE(onMouseMove)
		END_EVENT_MAP()

	public:
		Application(std::wstring const& name) 
			: name_(name)
            , deviceLost_(true)
            , managedResourcesInited_(false)
            , unmanagedResourcesInited_(false)
            , fps_()
            , frames_()
		{
		}

		virtual ~Application() {
			device_.reset();
			d3d_.clear();
		}

		void shutdown() {
            CALL_DERIVED(destroyUnmanagedResources)();
            CALL_DERIVED(destroyManagedResources)();

            ULONG outstandingObjectCount = device_->clear();
			if(outstandingObjectCount > 0) {
                Logging::outputMessage("ERROR: %d objects were not released\n", outstandingObjectCount);
            } else {
                Logging::outputMessage("All objects destroyed properly.\n");
            }

            device_.reset();

			d3d_.clear();
		}

		bool initialize() {
			if(windowHandle()) {
				return true;
			}

			CALL_DERIVED(createWindow)();
			ShowWindow();
			UpdateWindow();

			// Create the D3D object.

			//d3d_.attach(Direct3DCreate9(D3D9b_SDK_VERSION));
			d3d_.attach(Direct3DCreate9(D3D_SDK_VERSION));

			if(!d3d_) {
				return false;
			}

            d3ddfw::DisplayFormat format = {0};

            if(!CALL_DERIVED(getDisplayFormat)(format)) {
                return false;
            }

			D3DPRESENT_PARAMETERS pp = {0};
            pp.BackBufferWidth = format.mode.Width;
            pp.BackBufferHeight = format.mode.Height;
			pp.BackBufferFormat = format.backBufferFormat;
            pp.BackBufferCount = 0;
            pp.MultiSampleType = D3DMULTISAMPLE_NONE;
            pp.MultiSampleQuality = 0;
            pp.SwapEffect = D3DSWAPEFFECT_DISCARD;
            pp.hDeviceWindow = windowHandle();
            pp.Windowed = !format.fullscreen;
            pp.EnableAutoDepthStencil = true;
            pp.AutoDepthStencilFormat = format.depthStencilFormat;
            pp.Flags = D3DPRESENTFLAG_DISCARD_DEPTHSTENCIL;
            pp.FullScreen_RefreshRateInHz = format.fullscreen ? format.mode.RefreshRate: 0;
            pp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

            presentParams_ = pp;

            device_ = D3D9Device(new _D3D9Device());


			// Create the D3DDevice
			if( FAILED( d3d_->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, windowHandle(),
											  D3DCREATE_HARDWARE_VERTEXPROCESSING|D3DCREATE_PUREDEVICE,
											  &pp, &(*device_) ) ) )
			{
				return false;
			}

            deviceLost_ = false;

            managedResourcesInited_ = true;

            if(!CALL_DERIVED(initManagedResources)()) {
                CALL_DERIVED(destroyManagedResources)();
                return false;
            }

            unmanagedResourcesInited_ = true;

            if(!CALL_DERIVED(restoredUnmanagedResources)()) {
                CALL_DERIVED(destroyUnmanagedResources)();
                CALL_DERIVED(destroyManagedResources)();
                return false;
            }

            appTimer_.elapsedTime();

			return true;
		}

		void run() {
			if(!CALL_DERIVED(initialize)()) {
				return;
			}

			// Enter the message loop
			MSG msg;
			ZeroMemory( &msg, sizeof(msg) );
			while( msg.message!=WM_QUIT )
			{
				if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )
				{
					TranslateMessage( &msg );
					DispatchMessage( &msg );
				} else {
                    CALL_DERIVED(update)(appTimer_.elapsedTime());
					present();
				}
			}
		}

        void present() {
            HRESULT hr;

            if(deviceLost_) {
                hr = device_->TestCooperativeLevel();

                if(FAILED(hr)) {
                    if(hr == D3DERR_DEVICELOST) {
                        return;
                    }

                    if(hr == D3DERR_DEVICENOTRESET) {
                        if(!resetDevice()) {
                            return;
                        }
                    }
                }

                deviceLost_ = false;
            }

            CALL_DERIVED(render)();

            hr = device_->Present(NULL, NULL, NULL, NULL);
            if(hr == D3DERR_DEVICELOST) {
                deviceLost_ = true;
            }

            updateStats();
        }

        void updateStats() {
            static float lastFPSTick = 0.f;
            float absoluteTime = appTimer_.absoluteTime();

            if(lastFPSTick == 0.f) {
                frames_ = 1;
                lastFPSTick = absoluteTime;
            } else if(absoluteTime - lastFPSTick > 1.f) {
                fps_ = frames_ / (absoluteTime - lastFPSTick);
                frames_ = 0;
                lastFPSTick = absoluteTime;
            } else {
                ++frames_;
            }


            static boost::wformat statsFormatter(L"FPS: %0.2f\nTriangles: %d");

            statsString_ = boost::str(boost::wformat(statsFormatter) % fps_ % device_->primitiveCount());
        }

        bool resetDevice() {
            if(unmanagedResourcesInited_) {
                CALL_DERIVED(destroyUnmanagedResources)();
                unmanagedResourcesInited_ = false;
            }

            if(FAILED(device_->Reset(&presentParams_))) {
                return false;
            }

            unmanagedResourcesInited_ = true;
            
            if(!CALL_DERIVED(restoredUnmanagedResources)()) {
                return false;
            }

            return true;
        }

        void update(float elapsedTime) {
        }

        bool initManagedResources() {
            D3DXFONT_DESC font;
            font.Height = 18;
            font.Width = 0;
            font.Weight = FW_NORMAL;
			font.MipLevels = D3DX_DEFAULT;
            font.Italic = false;
			font.CharSet = DEFAULT_CHARSET;
            font.OutputPrecision = OUT_DEFAULT_PRECIS;
            font.Quality = DEFAULT_QUALITY;
            font.PitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;
            wcsncpy(font.FaceName, L"Arial", LF_FACESIZE);

            if(!(font_ = device_->D3DXCreateFontIndirect(&font))) {
                return false;
            }

            return true;
        }

        bool restoreUnmanagedResources() {
            font_->OnResetDevice();
            return true;
        }

        void destroyUnmanagedResources() {
            font_->OnLostDevice();
        }

        void destroyManagedResources() {
            font_.clear();
        }

		void createWindow() {
			d3ddfw::Window<TBase>::create(name_, L"D3DDFW_WINDOW", 800, 600);
		}

        bool getDisplayFormat(d3ddfw::DisplayFormat &format) {
		    return d3ddfw::findAdapterMode(d3d_, format, false, 0, 0, 5, 0, 15, 0);
        }

	public:
		LRESULT onDestroy() {
			shutdown();
			PostQuitMessage(0);
			return 0;
		}

        LRESULT onMouseMove(UINT x, UINT y) {
            if(device_) {
                POINT ptCursor;
                GetCursorPos(&ptCursor);

                if(!presentParams_.Windowed)  {
                    ScreenToClient(&ptCursor);
                }

                device_->SetCursorPosition(ptCursor.x, ptCursor.y, 0);
            }

            return DefWindowProc();
        }

	protected:
		std::wstring		    name_;
        bool                    deviceLost_;
		IDirect3D9Ptr		    d3d_;
		D3D9Device              device_;
        D3DPRESENT_PARAMETERS   presentParams_;
        bool                    managedResourcesInited_;
        bool                    unmanagedResourcesInited_;
        std::wstring            statsString_;
        float                   fps_;
        unsigned                frames_;
        Timer                   appTimer_;
        D3DXFont                font_;
	};

}
