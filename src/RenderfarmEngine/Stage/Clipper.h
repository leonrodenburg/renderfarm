#pragma once

#ifndef _CLIPPER_H_
#define _CLIPPER_H_

#include "../Resources.h"
#include "../Math/Vector3.h"
#include "../Geometry/Vertex.h"

#include <vector>

namespace RFStage
{
    class DLL_API Clipper
    {
    public:
        Clipper(float zNear, float zFar);
        virtual ~Clipper();

        void BindBuffer(std::vector<RFGeometry::Vertex*>* pBuffer);
        std::vector<RFGeometry::Vertex*>* Clip();
    private:
        RFMath::Vector3 _CalculateIntersection(RFMath::Vector3* pFrom, RFMath::Vector3* pTo, RFMath::Vector3* pPlaneNormal);
        bool _IsFrontFacing(RFMath::Vector3* p1, RFMath::Vector3* p2, RFMath::Vector3* p3);

        std::vector<RFGeometry::Vertex*>* _pBuffer;
        std::vector<RFGeometry::Vertex*>* _pTemp;
        std::vector<RFGeometry::Vertex*>* _pOutput;

        RFMath::Vector3 _planeNormals[6];

        float _zNear;
        float _zFar;
    };
}

#endif