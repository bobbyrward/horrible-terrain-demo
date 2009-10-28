#pragma once

namespace d3ddfw {

	template< typename TBase >
	class Window 
	{
	public:
		enum {
			DefaultWindowStyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | 
								   WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_VISIBLE,

		};
	public:
		Window()
			: hWnd_(NULL)
			, windowClassName_()
		{
		}

		virtual ~Window() {
			UnregisterClass(windowClassName_.c_str(), GetModuleHandle(NULL));
		}

	public:

		bool create(std::wstring const& title, std::wstring const& wndclass, 
				unsigned width = 400, unsigned height = 400,
				DWORD windowStyle = DefaultWindowStyle
			) 
		{
			WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, _Window_WndProc, 0L, 0L,
				GetModuleHandle(NULL), 
                NULL, 
                LoadCursor( NULL, IDC_ARROW ),
                (HBRUSH)GetStockObject(WHITE_BRUSH),
                NULL, wndclass.c_str(), NULL };

			windowClassName_ = wndclass;

			RegisterClassEx(&wc);

			RECT rc;
			SetRect(&rc, 0, 0, width, height);
			AdjustWindowRect(&rc, windowStyle, true);

			hWnd_ = CreateWindow(wndclass.c_str(), title.c_str(), windowStyle, 
				CW_USEDEFAULT, CW_USEDEFAULT, rc.right-rc.left, rc.bottom-rc.top, 0,
				NULL, wc.hInstance, NULL);

			SetWindowLongPtr(hWnd_, GWL_USERDATA, reinterpret_cast<INT_PTR>(this));

			return true;
  		}

		HWND windowHandle() const {
			return hWnd_;
		}

	private:
		HWND			hWnd_;
		std::wstring	windowClassName_;

        UINT            currentMSG_;
        WPARAM          currentWPARAM_;
        LPARAM          currentLPARAM_;

		friend LRESULT CALLBACK _Window_WndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )	{
			TBase *pBase = reinterpret_cast<TBase *>(GetWindowLongPtr(hWnd, GWL_USERDATA));
            if(pBase) {
                return pBase->_D3DDFW_WindowProc(hWnd, uMsg, wParam, lParam);
            } else {
                return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
            }
		}
	public:
        LRESULT DefWindowProc() {
            return ::DefWindowProc(hWnd_, currentMSG_, currentWPARAM_, currentLPARAM_);
        }

        LRESULT DefWindowProc(UINT msg, WPARAM wparam, LPARAM lparam) {
            return ::DefWindowProc(hWnd_, msg, wparam, lparam);
        }

		BOOL ShowWindow(int nCmdShow=SW_SHOWDEFAULT) {
			return ::ShowWindow(hWnd_, nCmdShow);
		}

		BOOL UpdateWindow() {
			return ::UpdateWindow(hWnd_);
		}

        HWND SetCapture() {
            return ::SetCapture(hWnd_);
        }

        BOOL ScreenToClient( LPPOINT ptCursor ) {
            return ::ScreenToClient(hWnd_, ptCursor);
        }

        BOOL DestroyWindow() {
            return ::DestroyWindow(hWnd_);
        }

        BOOL CloseWindow() {
            return ::CloseWindow(hWnd_);
        }
	};
}


#define BEGIN_EVENT_MAP(classname) \
LRESULT _D3DDFW_WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )	{ 


#define END_EVENT_MAP() \
	return DefWindowProc(uMsg, wParam, lParam); \
}

#define EVENT_CHAIN(classname) \
	return classname::_D3DDFW_WindowProc(hWnd,uMsg,wParam,lParam);

#define EVENT_WM_DESTROY(func) \
	if(uMsg==WM_DESTROY) { \
		return func(); \
	}

#define EVENT_WM_KEYDOWN(func) \
    if(uMsg==WM_KEYDOWN) { \
        return func(wParam);\
    }

#define EVENT_WM_KEYUP(func) \
    if(uMsg==WM_KEYUP) { \
        return func(wParam);\
    }

#define EVENT_WM_LBUTTONDOWN(func) \
    if(uMsg==WM_LBUTTONDOWN) { \
        return func(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)); \
    }

#define EVENT_WM_LBUTTONUP(func) \
    if(uMsg==WM_LBUTTONUP) { \
        return func(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)); \
    }

#define EVENT_WM_RBUTTONDOWN(func) \
    if(uMsg==WM_RBUTTONDOWN) { \
        return func(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)); \
    }

#define EVENT_WM_RBUTTONUP(func) \
    if(uMsg==WM_RBUTTONUP) { \
        return func(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)); \
    }

#define EVENT_WM_MBUTTONDOWN(func) \
    if(uMsg==WM_MBUTTONDOWN) { \
        return func(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)); \
    }

#define EVENT_WM_MBUTTONUP(func) \
    if(uMsg==WM_MBUTTONUP) { \
        return func(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)); \
    }

#define EVENT_WM_MOUSEMOVE(func) \
    if(uMsg==WM_MOUSEMOVE) { \
        return func(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)); \
    }













