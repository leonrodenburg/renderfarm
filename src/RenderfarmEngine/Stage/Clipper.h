#pragma once

#ifndef _CLIPPER_H_
#define _CLIPPER_H_

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
    class DLL_API Clipper
    {
    public:
        Clipper();
        virtual ~Clipper();

        void BindBuffer(std::vector<RFMath::Vector3*>* pBuffer);
        std::vector<RFMath::Vector3*>* Clip();
    private:
        RFMath::Vector3 _CalculateIntersection(RFMath::Vector3* pFrom, RFMath::Vector3* pTo, RFMath::Vector3* pPlaneNormal);

        std::vector<RFMath::Vector3*>* _pBuffer;
        std::vector<RFMath::Vector3*>* _pOutput;

        RFMath::Vector3 _planeNormals[6];
    };
}

#endif