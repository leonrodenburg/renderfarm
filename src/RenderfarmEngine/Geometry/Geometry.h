#pragma once

#ifndef _GEOMETRY_H_
#define _GEOMETRY_H_

#include "../Resources.h"
#include "../Math/Vector3.h"
#include "../Geometry/Vertex.h"

#include <iostream>
#include <vector>

namespace RFGeometry
{
    class DLL_API Geometry
    {
    public:
        Geometry();
        Geometry(const RFMath::Vector3& position);
        virtual ~Geometry();

        RFMath::Vector3& GetPosition();
        void SetPosition(const RFMath::Vector3& position);

        std::vector<RFMath::Vector3*>* GetVertexPositions();
        std::vector<RFGeometry::Vertex*>* GetVertexBuffer();

        virtual void PrepareBuffers() = 0;
        virtual void Print(std::ostream& output) = 0;

        DLL_API friend std::ostream& operator<<(std::ostream& output, Geometry& geometry);
    protected:
        RFMath::Vector3 _position;
        std::vector<RFMath::Vector3*>* _pVertexPositions;
        std::vector<RFGeometry::Vertex*>* _pVertexBuffer;
    private:
        void _Construct(const RFMath::Vector3& position);
    };
}

#endif