#include <windows.h>
#include <string.h>
#include <tchar.h>
#include <iostream>
#include <vector>

#ifdef DEBUG
    //#include <vld.h> // Visual Leak Detector (http://vld.codeplex.com/)
#endif

#include "Core/Logger.h"
#include "Core/Kernel.h"
#include "Math/Vector3.h"
#include "Geometry/World.h"
#include "Geometry/Cube.h"
#include "Geometry/Pyramid.h"
#include "Math/Utility.h"

// Forward declarations
WNDCLASSEX CreateWindowClass(HINSTANCE hInstance);
HWND OpenWindow(HINSTANCE hInstance, WNDCLASSEX windowClass, unsigned int width, unsigned int height);
LRESULT CALLBACK WndProc(HWND handle, UINT message, WPARAM windowParameters, LPARAM userParameters);
void Initialize();
int Run();
void Paint(unsigned int* pBuffer);
void CreateBitmap();
void Cleanup();

// Globals
HWND khWnd;

unsigned int kWidth = 800;
int kHeight = 600;
float kNearView = 1.0f;
float kFarView = 500.0f;
float kFieldOfView = RFMathDegToRad(45.0f);

BITMAPINFO kBitmapInfo;
HBITMAP kBitmap = NULL;
HBITMAP kOldBitmap = NULL;
HDC kBitmapDC = NULL;

unsigned int * kpPixels;

RFCore::Kernel* kpKernel;
RFGeometry::World* kpWorld;
std::vector<RFGeometry::Geometry*>* kpGeometry;

/**
 * Initialize the world, geometry and kernel.
 */
void Initialize()
{
    // Initialize geometry and models
    RFGeometry::Cube* pCube = new RFGeometry::Cube(1.0f, RFMath::Vector3(0.9f, 1.0f, 3.0f));
    kpGeometry->push_back(pCube);

    RFGeometry::Pyramid* pPyramid = new RFGeometry::Pyramid(1.0f, 1.0f, RFMath::Vector3(-1.5f, 0.0f, 7.0f));
    kpGeometry->push_back(pPyramid);

    RFGeometry::Cube* pCube2 = new RFGeometry::Cube(1.0f, RFMath::Vector3(-3.0f, -2.0f, 10.0f));
    kpGeometry->push_back(pCube2);

    RFGeometry::Cube* pCube3 = new RFGeometry::Cube(1.0f, RFMath::Vector3(2.0f, -2.5f, 10.0f));
    kpGeometry->push_back(pCube3);

    RFGeometry::Cube* pCube4 = new RFGeometry::Cube(1.0f, RFMath::Vector3(1.7f, 1.7f, 15.0f));
    kpGeometry->push_back(pCube4);   
}

/**
 * Update the geometry in the world (called every frame, used for animation).
 */
void Update()
{
    // Enable to see rotation
    /*
    RFMath::Matrix rotation;
    rotation.RotateY(0.1f);

    for(unsigned int i = 0; i < kpGeometry->size(); ++i)
    {
        kpGeometry->at(i)->Transform(rotation, true);
    }
    */
}

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
#ifdef DEBUG
    std::cout << "DEBUG BUILD - BE PREPARED TO SEE OUTPUT!" << std::endl;
    RFCore::Logger::GetLogger()->Log("Fetching application handle...");
#else
    std::cout << "RELEASE BUILD - CONSOLE OUTPUT SUPPRESSED" << std::endl;
#endif

    HINSTANCE hInstance = GetModuleHandle(NULL);

    WNDCLASSEX windowClass = CreateWindowClass(hInstance);

#ifdef DEBUG
    RFCore::Logger::GetLogger()->Log("Created window class...");
    RFCore::Logger::GetLogger()->Log("Opening window...");
#endif
    
    khWnd = ::OpenWindow(hInstance, windowClass, kWidth, kHeight);

    // Initialize world
    kpWorld = new RFGeometry::World();
    kpGeometry = new std::vector<RFGeometry::Geometry*>();

    // Initialize kernel
    kpKernel = new RFCore::Kernel(kpWorld, kNearView, kFarView, kFieldOfView, kWidth, kHeight);

    // Initialize geometry
    ::Initialize();

    // Add geometry to the world
    for(unsigned int i = 0; i < kpGeometry->size(); ++i)
    {
        kpWorld->AddGeometry(kpGeometry->at(i));
    }

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
#ifdef DEBUG
    RFCore::Logger::GetLogger()->Log("Started message loop, time to render!");
#endif

    MSG msg;
    ZeroMemory(&msg, sizeof(msg));

    while(WM_QUIT != msg.message)
    {
        if(::PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
        }
        else
        {
            // Update scene
            ::Update();

            // Render
            unsigned int* pBuffer = kpKernel->Run();

            // Paint the buffer
            ::Paint(pBuffer);
        }
    }

    return msg.wParam;
}

/**
 * Paint the given buffer in the window. Pixel colors in the bitmap are 
 * expected in BGR format.
 *
 * @param pBuffer
 */
void Paint(unsigned int* pBuffer)
{
    for(int y = 0; y < kHeight; ++y)
    {
        for(unsigned int x = 0; x < kWidth; ++x)
        {
            kpPixels[y * kWidth + x] = RGB(
                pBuffer[y * (kWidth * 3) + (x * 3) + 2],    // blue
                pBuffer[y * (kWidth * 3) + (x * 3) + 1],    // green
                pBuffer[y * (kWidth * 3) + (x * 3) + 0]     // red
            );
        }
    }

    HDC currentDC = GetDC(khWnd);
    SetDIBits(kBitmapDC, kBitmap, 0, kHeight, (void **)&kpPixels, &kBitmapInfo, DIB_RGB_COLORS);
    BitBlt(currentDC, 0, 0, kWidth, kHeight, kBitmapDC, 0, 0, SRCCOPY);
    ReleaseDC(khWnd, currentDC);
}

/**
 * Create the bitmap and memory DC.
 */
void CreateBitmap()
{
#ifdef DEBUG
    RFCore::Logger::GetLogger()->Log("Gathering bitmap info...");
#endif

    ZeroMemory(&(kBitmapInfo.bmiHeader), sizeof(kBitmapInfo.bmiHeader));
    kBitmapInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    kBitmapInfo.bmiHeader.biWidth = kWidth;
    kBitmapInfo.bmiHeader.biHeight = -kHeight;
    kBitmapInfo.bmiHeader.biPlanes = 1;
    kBitmapInfo.bmiHeader.biBitCount = 32;
    kBitmapInfo.bmiHeader.biCompression = BI_RGB;
    kBitmapInfo.bmiHeader.biSizeImage = 0;

    kBitmapDC = CreateCompatibleDC(NULL);
    kBitmap = CreateDIBSection(kBitmapDC, &kBitmapInfo, DIB_RGB_COLORS, (void **)&kpPixels, NULL, NULL);

#ifdef DEBUG
    if(kBitmap == NULL || kpPixels == NULL)
    {
        RFCore::Logger::GetLogger()->Log(RFCore::Logger::FATAL_TYPE, "Failed to create bitmap!");
    }
    RFCore::Logger::GetLogger()->Log("Created DC and bitmap...");
#endif

    kOldBitmap = (HBITMAP)SelectObject(kBitmapDC, kBitmap);
}

/**
 * Clean up all resources.
 */
void Cleanup()
{
#ifdef DEBUG
    RFCore::Logger::GetLogger()->Log("SIGNAL: Window was closed");
    RFCore::Logger::GetLogger()->Log("Cleaning up bitmap...");
#endif

    kBitmap = (HBITMAP)SelectObject(kBitmapDC, kOldBitmap);
    DeleteObject(kOldBitmap);
    DeleteObject(kBitmap);
    DeleteDC(kBitmapDC);

#ifdef DEBUG
    RFCore::Logger::GetLogger()->Log("Cleaning up Renderfarm resources...");
#endif

    delete kpKernel;
    delete kpWorld;

    for(unsigned int i = 0; i < kpGeometry->size(); ++i)
    {
        delete kpGeometry->at(i);
    }
    delete kpGeometry;

#ifdef DEBUG
    RFCore::Logger::GetLogger()->Log("Resources cleaned up. Closing Renderfarm...");
#endif

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