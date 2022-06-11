#ifdef _WIN32

#define IDR_MAINFRAME 0

#include <cstdlib>
#include <gdiplus.h>
#include <vector>
#include <string>
#include <iterator>
#include <windows.h>
#include <winuser.h>

using namespace Gdiplus;
using namespace std;

class Window {
    private:
        BOOL OnCreate(HWND hWnd, LPCREATESTRUCT pCreateStruct) { return TRUE; }

        void OnPaint(HWND hWnd) {
            PAINTSTRUCT paintStruct;
            HDC hDC = BeginPaint(hWnd, &paintStruct);
            RECT clientRect;
            GetClientRect(hWnd, &clientRect);

            Graphics graphics(hDC);
            PointF point;
            point.Y = static_cast<REAL>(clientRect.top + 4);
            point.X = static_cast<REAL>(clientRect.left + 8);

            Font font(L"Verdana", 10, FontStyleRegular, UnitPoint, NULL);
            REAL fontHeight = font.GetHeight(graphics.GetDpiY());
            RectF boundRect;
            graphics.MeasureString(L"THE QUICK BROWN FOX JUMPS OVER THE LAZY DOG",
                                   43, &font, RectF(0, 0, 600, fontHeight),
                                   &boundRect);

            REAL tabValue = 4 * boundRect.Width / 43;
            StringFormat stringFormat;
            stringFormat.SetTabStops(0.0f, 1, &tabValue);

            SolidBrush brush(Color(128, 0, 128));

            EndPaint(hWnd, &paintStruct);
        }

        LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam) {
            switch (uMessage) {
                case WM_CREATE:
                    return OnCreate(hWnd, reinterpret_cast<LPCREATESTRUCT>(lParam));

                case WM_PAINT:
                    OnPaint(hWnd);
                    break;

                case WM_DESTROY:
                    PostQuitMessage(0);
                    break;

                default:
                    return DefWindowProc(hWnd, uMessage, wParam, lParam);
            }

            return 0;
        }

        static LRESULT CALLBACK StaticProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam) {
            if (uMessage == WM_NCCREATE) {
                LPCREATESTRUCT pCreatestruct = reinterpret_cast<LPCREATESTRUCT>(lParam);
                ::SetWindowLongPtr(hWnd, GWLP_USERDATA, PtrToUlong(pCreatestruct -> lpCreateParams));
            }

            Window *pWindow = (Window *)::GetWindowLongPtr(hWnd, GWLP_USERDATA);

            if (pWindow != nullptr) {
                return pWindow -> WindowProc(hWnd, uMessage, wParam, lParam);
            } else {
                return DefWindowProc(hWnd, uMessage, wParam, lParam);
            }
        }

    public:
        Window() {}
    
        ~Window() {}
    
        HRESULT Create(HINSTANCE hInstance) {
            WNDCLASSEX wndClassEx;
            HWND hWnd;
    
            wndClassEx.cbSize = sizeof wndClassEx;
            wndClassEx.style = CS_HREDRAW | CS_VREDRAW;
            wndClassEx.lpfnWndProc = StaticProc;
            wndClassEx.cbClsExtra = 0;
            wndClassEx.cbWndExtra = 0;
            wndClassEx.hInstance = hInstance;
            wndClassEx.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDR_MAINFRAME));
            wndClassEx.hCursor = LoadCursor(NULL, IDC_ARROW);
            wndClassEx.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
            wndClassEx.lpszMenuName = MAKEINTRESOURCE(IDR_MAINFRAME);
            wndClassEx.lpszClassName = TEXT("Win32App1");
            wndClassEx.hIconSm = NULL;
    
            if (RegisterClassEx(&wndClassEx)) {
                hWnd = CreateWindowEx(WS_EX_CLIENTEDGE, wndClassEx.lpszClassName,
                                      wndClassEx.lpszClassName, WS_OVERLAPPEDWINDOW,
                                      CW_USEDEFAULT, 0, 600, 350, NULL, NULL,
                                      hInstance, this);
            }
    
            HRESULT hr = hWnd ? S_OK : E_FAIL;
            
            if (SUCCEEDED(hr)) {
                ShowWindow(hWnd, SW_SHOWNORMAL);
                UpdateWindow(hWnd);
            }
    
            return hr;
        }
};

#endif

#ifdef __linux__

class Window {};

#endif
