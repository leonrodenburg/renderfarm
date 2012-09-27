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
        Clipper(const RFMath::Vector3* pMin, const RFMath::Vector3* pMax);
        virtual ~Clipper();

        void BindBuffer(const std::vector<RFMath::Vector3*>* pBuffer);
        std::vector<RFMath::Vector3*>* Clip();
    protected:
        RFMath::Vector3* _pMin;
        RFMath::Vector3* _pMax;
    private:
        void _Construct(const RFMath::Vector3* pMin, const RFMath::Vector3* pMax);

        const std::vector<RFMath::Vector3*>* _pBuffer;
        std::vector<RFMath::Vector3*>* _pOutput;
    };
}

#endif