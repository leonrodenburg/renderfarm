#pragma once

#ifndef _RASTERIZER_H_
#define _RASTERIZER_H_

#include "../Resources.h"
#include "../Math/Vector3.h"
#include "../Geometry/Vertex.h"

#include <vector>

namespace RFStage
{
    class DLL_API Rasterizer
    {
    public:
        Rasterizer(unsigned int windowWidth, unsigned int windowHeight);
        virtual ~Rasterizer();

        void BindBuffer(std::vector<RFGeometry::Vertex*>* pBuffer);
        void SetClearColor(unsigned int red, unsigned int green, unsigned int blue);
        unsigned int* Rasterize();
    private:
        void _Clear();
        void _Interpolate(RFGeometry::Vertex* v1, RFGeometry::Vertex* v2, RFGeometry::Vertex* v3, float area, int xCurrent, int yCurrent, RFMath::Vector3* pPosOut, RFMath::Vector3* pColorOut);

        std::vector<RFGeometry::Vertex*>* _pBuffer;
   
        float* _pDepthBuffer;
        unsigned int* _pOutput;

        unsigned int _windowWidth;
        unsigned int _windowHeight;

        unsigned int _clearRed;
        unsigned int _clearGreen;
        unsigned int _clearBlue;
    };
}

#endif