#pragma once

#ifndef _PROJECTOR_H_
#define _PROJECTOR_H_

#include "../Resources.h"
#include "../Math/Matrix.h"
#include "../Math/Vector3.h"

#include <vector>

namespace RFStage
{
    class DLL_API Projector
    {
    public:
        Projector(float nearView, float farView, float fieldOfView, unsigned int windowWidth, unsigned int windowHeight);
        virtual ~Projector();

        void BindBuffer(std::vector<RFMath::Vector3*>* pBuffer);
        std::vector<RFMath::Vector3*>* Project();
        std::vector<RFMath::Vector3*>* Map();
    private:
        std::vector<RFMath::Vector3*>* _pBuffer;
        std::vector<RFMath::Vector3*>* _pOutput;
        std::vector<RFMath::Vector3*>* _pOutputMap;

        RFMath::Matrix _projectionTransform;
        RFMath::Matrix _mapTransform;

        float _nearView;
        float _farView;
        float _fieldOfView;
    };
}

#endif