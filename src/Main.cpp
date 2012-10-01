#include <windows.h>
#include <string.h>
#include <tchar.h>
#include <iostream>

//#include <vld.h> // Visual Leak Detector (http://vld.codeplex.com/)

#include "Core/Logger.h"
#include "Core/Kernel.h"

// Forward declarations
WNDCLASSEX CreateWindowClass(HINSTANCE hInstance);
HWND OpenWindow(HINSTANCE hInstance, WNDCLASSEX windowClass, unsigned int width, unsigned int height);
LRESULT CALLBACK WndProc(HWND handle, UINT message, WPARAM windowParameters, LPARAM userParameters);
int Run();
void Paint(unsigned int* pBuffer);
void CreateBitmap();
void Cleanup();

// Globals
HWND khWnd;

unsigned int kWidth = 800;
unsigned int kHeight = 600;

BITMAPINFO kBitmapInfo;
HBITMAP kBitmap = NULL;
HBITMAP kOldBitmap = NULL;
HDC kBitmapDC = NULL;

unsigned int * kpPixels;

RFCore::Kernel* kpKernel;

/**
 * Main entry point of application.
 *
 * @param argc
 * @param argv
 */
int main(int argc, char** argv)
{
    std::cout << "Renderfarm 0.1a - by Leon Rodenburg" << std::endl;

    // Initialize window
    RFCore::Logger::GetLogger()->Log("Fetching application handle...");
    HINSTANCE hInstance = GetModuleHandle(NULL);

    RFCore::Logger::GetLogger()->Log("Creating window class...");
    WNDCLASSEX windowClass = CreateWindowClass(hInstance);

    RFCore::Logger::GetLogger()->Log("Opening window...");
    khWnd = ::OpenWindow(hInstance, windowClass, kWidth, kHeight);

    // Initialize world
    RFGeometry::World world;
    kpKernel = new RFCore::Kernel(&world, kWidth, kHeight);

    // Start rendering!
    return ::Run();
}

/**
 * Start the message loop (and rendering).
 *
 * @return ID of last received message.
 */
int Run()
{
    RFCore::Logger::GetLogger()->Log("Started message loop, time to render!");

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
            //float currentTime = (float)timeGetTime();
            //float timeDelta = (currentTime - lastTime) / 1000.0f;

            // Render!
            unsigned int* pBuffer = kpKernel->Run();

            // Paint the buffer!
            ::Paint(pBuffer);

            //lastTime = currentTime;
        }
    }

    return msg.wParam;
}

/**
 * Paint the given buffer in the window.
 *
 * @param pBuffer
 */
void Paint(unsigned int* pBuffer)
{
    for(unsigned int y = 0; y < kHeight; ++y)
    {
        for(unsigned int x = 0; x < kWidth; x++)
        {
            kpPixels[y * kWidth + x] = RGB(
                pBuffer[y * (kWidth * 3) + (x * 3)],        // red
                pBuffer[y * (kWidth * 3) + (x * 3) + 1],    // green
                pBuffer[y * (kWidth * 3) + (x * 3) + 2]     // blue
            );
        }
    }

    HDC currentDC = GetDC(khWnd);
    SetDIBits(kBitmapDC, kBitmap, 0, kHeight, (void **)&kpPixels, &kBitmapInfo, DIB_RGB_COLORS);
    BitBlt(currentDC, 0, 0, kWidth, kHeight, kBitmapDC, 0, 0, SRCCOPY);
}

/**
 * Create the bitmap and memory DC.
 */
void CreateBitmap()
{
    RFCore::Logger::GetLogger()->Log("Gathering bitmap info...");

    ZeroMemory(&(kBitmapInfo.bmiHeader), sizeof(kBitmapInfo.bmiHeader));
    kBitmapInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    kBitmapInfo.bmiHeader.biWidth = kWidth;
    kBitmapInfo.bmiHeader.biHeight = kHeight;
    kBitmapInfo.bmiHeader.biPlanes = 1;
    kBitmapInfo.bmiHeader.biBitCount = 32;
    kBitmapInfo.bmiHeader.biCompression = BI_RGB;
    kBitmapInfo.bmiHeader.biSizeImage = 0;

    RFCore::Logger::GetLogger()->Log("Creating DC and bitmap...");
    kBitmapDC = CreateCompatibleDC(NULL);
    kBitmap = CreateDIBSection(kBitmapDC, &kBitmapInfo, DIB_RGB_COLORS, (void **)&kpPixels, NULL, NULL);
    if(kBitmap == NULL || kpPixels == NULL)
    {
        RFCore::Logger::GetLogger()->Log(RFCore::Logger::FATAL, "Failed to create bitmap!");
    }

    kOldBitmap = (HBITMAP)SelectObject(kBitmapDC, kBitmap);
}

/**
 * Clean up all resources.
 */
void Cleanup()
{
    RFCore::Logger::GetLogger()->Log("SIGNAL: Window was closed");
    RFCore::Logger::GetLogger()->Log("Cleaning up bitmap...");

    kBitmap = (HBITMAP)SelectObject(kBitmapDC, kOldBitmap);
    DeleteObject(kOldBitmap);
    DeleteObject(kBitmap);
    DeleteDC(kBitmapDC);

    RFCore::Logger::GetLogger()->Log("Cleaning up Renderfarm resources...");
    delete kpKernel;

    RFCore::Logger::GetLogger()->Log("Resources cleaned up. Closing Renderfarm...");

    PostQuitMessage(0);
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
    HDC hDC;
    PAINTSTRUCT ps;

    switch (message)
    {
    case WM_CREATE:
        ::CreateBitmap();
        break;
    case WM_PAINT:
        hDC = BeginPaint(hWnd, &ps);
   
        BitBlt(hDC, 0, 0, kWidth, kHeight, kBitmapDC, 0, 0, SRCCOPY);

        EndPaint(hWnd, &ps);
        return 1;
        break;
    case WM_DESTROY:
        ::Cleanup();
        break;
    case WM_KEYDOWN:
        if(wParam == VK_ESCAPE)
        {
            DestroyWindow(hWnd);
        }
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
 *
 * @return Window handle
 */
HWND OpenWindow(HINSTANCE hInstance, WNDCLASSEX windowClass, unsigned int width, unsigned int height)
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
        windowClass.lpszClassName,                  /* window class name */
        _T("Renderfarm 0.1a - by Leon Rodenburg"),  /* window name */
        WS_OVERLAPPEDWINDOW,                        /* window type */
        CW_USEDEFAULT,                              /* x-position */
        CW_USEDEFAULT,                              /* y-position */
        clientRect.right - clientRect.left,         /* width */
        clientRect.bottom - clientRect.top,         /* height */
        NULL,                                       /* parent window */
        NULL,                                       /* menu name */
        hInstance,                                  /* application handle */
        NULL                                        /* user-defined parameters */
    );

    ::ShowWindow(handle, SW_SHOWDEFAULT);
    ::UpdateWindow(handle);

    return handle;
}