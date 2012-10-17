#pragma once

#ifndef _PROJECTOR_H_
#define _PROJECTOR_H_

#include "../Resources.h"
#include "../Math/Matrix.h"
#include "../Math/Vector3.h"
#include "../Geometry/Vertex.h"

#include <vector>

namespace RFStage
{
    class DLL_API Projector
    {
    public:
        Projector(float nearView, float farView, float fieldOfView, unsigned int windowWidth, unsigned int windowHeight);
        virtual ~Projector();

        void BindBuffer(std::vector<RFGeometry::Vertex*>* pBuffer);
        std::vector<RFGeometry::Vertex*>* Project();
        std::vector<RFGeometry::Vertex*>* Map();
    private:
        std::vector<RFGeometry::Vertex*>* _pBuffer;
        std::vector<RFGeometry::Vertex*>* _pOutput;
        std::vector<RFGeometry::Vertex*>* _pOutputMap;

        RFMath::Matrix _projectionTransform;
        RFMath::Matrix _mapTransform;

        float _nearView;
        float _farView;
        float _fieldOfView;
    };
}

#endif