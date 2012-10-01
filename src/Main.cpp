#include <windows.h>
#include <string.h>
#include <tchar.h>
#include <iostream>

#include <vld.h> // Visual Leak Detector (http://vld.codeplex.com/)

// Forward declarations
WNDCLASSEX CreateWindowClass(HINSTANCE hInstance);
void OpenWindow(HINSTANCE hInstance, WNDCLASSEX windowClass, unsigned int width, unsigned int height);
LRESULT CALLBACK WndProc(HWND handle, UINT message, WPARAM windowParameters, LPARAM userParameters);
int Start();

/**
 * Main entry point of application.
 *
 * @param argc
 * @param argv
 */
int main(int argc, char** argv)
{
    std::cout << "Renderfarm 0.1a - by Leon Rodenburg" << std::endl;
    std::cout << "Fetching application handle..." << std::endl;
    HINSTANCE hInstance = GetModuleHandle(NULL);

    std::cout << "Creating window class..." << std::endl;
    WNDCLASSEX windowClass = CreateWindowClass(hInstance);

    std::cout << "Opening window..." << std::endl;
    OpenWindow(hInstance, windowClass, 1024, 768);
    return Start();
}

/**
 * Start the message loop (and rendering).
 *
 * @return ID of last received message.
 */
int Start()
{
    std::cout << "Started message loop, time to render!" << std::endl;

    MSG msg;
    ZeroMemory(&msg, sizeof(msg));
    static float lastTime = (float)timeGetTime();

    while(WM_QUIT != msg.message)
    {
        if(::PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
        }
        else
        {
            float currentTime = (float)timeGetTime();
            float timeDelta = (currentTime - lastTime) / 1000.0f;

            // Render (and pass timeDelta)!

            lastTime = currentTime;
        }
    }

    return msg.wParam;
}

/**
 * Handle incoming window messages.
 *
 * @param hWnd
 * @param message
 * @param wParam
 * @param lParam
 *
 * @return Whether or not the message was handled
 */
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_PAINT:
        
        break;
    case WM_DESTROY:
        std::cout << "Window closed, cleaning up..." << std::endl;

        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
        break;
    }

    return 0;
}

/**
 * Create a window class.
 *
 * @param hInstance
 *
 * @return Registered window class
 */
WNDCLASSEX CreateWindowClass(HINSTANCE hInstance)
{
    WNDCLASSEX windowClass;
    windowClass.cbSize = sizeof(WNDCLASSEX);
    windowClass.style = CS_HREDRAW | CS_VREDRAW;	
    windowClass.lpfnWndProc = WndProc;
    windowClass.cbClsExtra = 0;
    windowClass.cbWndExtra = 0;
    windowClass.hInstance = hInstance;
    windowClass.hIcon = ::LoadIcon(hInstance, (LPCTSTR)IDI_APPLICATION);
    windowClass.hCursor = ::LoadCursor(hInstance, (LPCTSTR)IDC_ARROW);
    windowClass.hbrBackground = NULL;
    windowClass.lpszMenuName = NULL;
    windowClass.lpszClassName = _T("Renderfarm 0.1a - by Leon Rodenburg");
    windowClass.hIconSm = NULL;

    ::RegisterClassEx(&windowClass);

    return windowClass;
}

/**
 * Open the window.
 *
 * @param hInstance
 * @param windowClass
 * @param width
 * @param height
 */
void OpenWindow(HINSTANCE hInstance, WNDCLASSEX windowClass, unsigned int width, unsigned int height)
{
    RECT clientRect;

    clientRect.top = 0;
    clientRect.left = 0;
    clientRect.right = width;
    clientRect.bottom = height;

    AdjustWindowRect(
        &clientRect, 
        WS_OVERLAPPEDWINDOW,
        FALSE
    );

    HWND handle = ::CreateWindow(
        windowClass.lpszClassName,					/* window class name */
        _T("Renderfarm 0.1a - by Leon Rodenburg"),	/* window name */
        WS_OVERLAPPEDWINDOW,						/* window type */
        CW_USEDEFAULT,								/* x-position */
        CW_USEDEFAULT,								/* y-position */
        clientRect.right - clientRect.left,			/* width */
        clientRect.bottom - clientRect.top,			/* height */
        NULL,										/* parent window */
        NULL,										/* menu name */
        hInstance,									/* application handle */
        NULL                                        /* user-defined parameters */
    );	

    ::ShowWindow(handle, SW_SHOWDEFAULT);
    ::UpdateWindow(handle);
}




