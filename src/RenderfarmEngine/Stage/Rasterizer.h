#pragma once

#ifndef _RASTERIZER_H_
#define _RASTERIZER_H_

#include "../Resources.h"
#include "../Math/Vector3.h"

#include <vector>

#ifdef DLL_EXPORTS
#define DLL_API __declspec(dllexport)
#else
#define DLL_API __declspec(dllimport)
#endif

namespace RFStage
{
    class Rasterizer
    {
    public:
        Rasterizer();
        virtual ~Rasterizer();
    };
}

#endif