#pragma once

#ifndef _VERTEX_H_
#define _VERTEX_H_

#include "../Resources.h"
#include "../Math/Vector3.h"

#include <iostream>

namespace RFGeometry
{
    class DLL_API Vertex
    {
    public:
        Vertex(RFMath::Vector3* pPosition, RFMath::Vector3* pColor);
        virtual ~Vertex();

        RFMath::Vector3* GetPosition();
        RFMath::Vector3* GetColor();

        void SetPosition(RFMath::Vector3* pPosition);
        void SetColor(RFMath::Vector3* pColor);
    private:
        RFMath::Vector3* _pPosition;
        RFMath::Vector3* _pColor;
    };
}

#endif