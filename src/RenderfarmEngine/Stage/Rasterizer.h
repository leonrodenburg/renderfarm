#pragma once

#ifndef _RASTERIZER_H_
#define _RASTERIZER_H_

#include "../Resources.h"
#include "../Math/Vector3.h"

#include <vector>

#ifdef DLL_EXPORT
#define DLL_API __declspec(dllexport)
#else
#define DLL_API __declspec(dllimport)
#endif

namespace RFStage
{
    class DLL_API Rasterizer
    {
    public:
        Rasterizer(unsigned int windowWidth, unsigned int windowHeight);
        virtual ~Rasterizer();

        void BindBuffer(std::vector<RFMath::Vector3*>* pBuffer);
        void SetClearColor(unsigned int red, unsigned int green, unsigned int blue);
        unsigned int* Rasterize();
    private:
        void _Clear();

        std::vector<RFMath::Vector3*>* _pBuffer;
        unsigned int* _pOutput;

        unsigned int _windowWidth;
        unsigned int _windowHeight;

        unsigned int _clearRed;
        unsigned int _clearGreen;
        unsigned int _clearBlue;
    };
}

#endif