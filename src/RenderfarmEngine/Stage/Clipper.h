#pragma once

#ifndef _CLIPPER_H_
#define _CLIPPER_H_

#include "../Resources.h"
#include "../Math/Vector3.h"

#include <vector>

namespace RFStage
{
    class DLL_API Clipper
    {
    public:
        Clipper();
        virtual ~Clipper();

        void BindBuffer(std::vector<RFMath::Vector3*>* pBuffer);
        std::vector<RFMath::Vector3*>* Clip();
    private:
        RFMath::Vector3 _CalculateIntersection(RFMath::Vector3* pFrom, RFMath::Vector3* pTo, RFMath::Vector3* pPlaneNormal);
        bool _IsFrontFacing(RFMath::Vector3* p1, RFMath::Vector3* p2, RFMath::Vector3* p3);

        std::vector<RFMath::Vector3*>* _pBuffer;
        std::vector<RFMath::Vector3*>* _pOutput;

        RFMath::Vector3 _planeNormals[6];
    };
}

#endif