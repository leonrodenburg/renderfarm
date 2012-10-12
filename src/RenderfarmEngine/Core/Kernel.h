#pragma once

#ifndef _KERNEL_H_
#define _KERNEL_H_

#include "../Resources.h"
#include "../Stage/Clipper.h"
#include "../Stage/Rasterizer.h"
#include "../Stage/Projector.h"
#include "../Geometry/World.h"

#include <vector>

namespace RFCore
{
    class DLL_API Kernel
    {
    public:
        Kernel(RFGeometry::World* pWorld, float nearView, float farView, float fieldOfView, unsigned int windowWidth, unsigned int windowHeight);
        virtual ~Kernel();

        unsigned int* GetFrontBuffer();
        RFStage::Projector* GetProjector();
        RFStage::Clipper* GetClipper();
        RFStage::Rasterizer* GetRasterizer();
        unsigned int* Run();
    private:
        RFStage::Projector* _pProjector;
        RFStage::Clipper* _pClipper;
        RFStage::Rasterizer* _pRasterizer;
        RFGeometry::World* _pWorld;

        unsigned int* _pFrontBuffer;
        unsigned int* _pBackBuffer;
    };
}

#endif