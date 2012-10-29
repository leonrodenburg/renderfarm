//
//  Main.cpp
//  renderfarm-osx
//
//  Created by Léon Rodenburg on 10/11/12.
//  Copyright (c) 2012 Léon Rodenburg. All rights reserved.
//

#include "World.h"
#include "Kernel.h"

unsigned int kWidth = 800;
int kHeight = 600;
float kNearView = 1.0f;
float kFarView = 500.0f;
float kFieldOfView = RFMathDegToRad(45.0f);

RFGeometry::World* kpWorld;
RFCore::Kernel* kpKernel;

void Run();
void Update();
void Paint(unsigned int* pBuffer);
void OpenWindow();

int main(int argc, const char * argv[])
{
    // Initialize world and kernel
    kpWorld = new RFGeometry::World();
    kpKernel = new RFCore::Kernel(kpWorld, kNearView, kFarView, kFieldOfView, kWidth, kHeight);
    
    std::cout << "Renderfarm 0.1a - by Leon Rodenburg" << std::endl;
    
#ifdef DEBUG
    std::cout << "DEBUG BUILD - BE PREPARED TO SEE OUTPUT!" << std::endl;
#else
    std::cout << "RELEASE BUILD - CONSOLE OUTPUT SUPPRESSED" << std::endl;
#endif
    
    // Run!
    ::Run();
    
    delete kpKernel;
    delete kpWorld;
}

/**
 * Start the message loop and start rendering.
 */
void Run()
{
    while(true)
    {
        // Update the scene, render and paint
        ::Update();
        unsigned int* pBuffer = kpKernel->Run();
        ::Paint(pBuffer);
    }
}

/**
 * Update the scene.
 */
void Update()
{
    
}

/**
 * Paint the buffer in the window.
 */
void Paint(unsigned int* pBuffer)
{
    
}

/**
 * Open a window.
 */
void OpenWindow()
{
    
}

