#pragma once

#ifndef _KERNEL_H_
#define _KERNEL_H_

#include "../Resources.h"
#include "../Stage/Clipper.h"
#include "../Geometry/World.h"

#include <vector>

#ifdef DLL_EXPORTS
#define DLL_API __declspec(dllexport)
#else
#define DLL_API __declspec(dllimport)
#endif

namespace RFCore
{
    class DLL_API Kernel
    {
    public:
        Kernel(RFGeometry::World* pWorld);
        virtual ~Kernel();

        void Run();
    private:
        RFStage::Clipper* _pClipper;
        RFGeometry::World* _pWorld;
    };
}

#endif