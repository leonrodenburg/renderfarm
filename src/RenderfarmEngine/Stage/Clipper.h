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

        void BindBuffer(const std::vector<RFMath::Vector3*>& buffer);
    private:
        const std::vector<RFMath::Vector3*>* _pBuffer;
        std::vector<RFMath::Vector3*>* _pOutput;
    };
}

#endif