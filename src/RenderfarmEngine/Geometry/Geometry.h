#pragma once

#ifndef _GEOMETRY_H_
#define _GEOMETRY_H_

#include "../Resources.h"
#include "../Math/Vector3.h"

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

        std::vector<RFMath::Vector3*>* GetVertices();
        std::vector<RFMath::Vector3*>* GetVertexBuffer();

        virtual void PrepareBuffers() = 0;
        virtual void Print(std::ostream& output) = 0;

        DLL_API friend std::ostream& operator<<(std::ostream& output, Geometry& geometry);
    protected:
        RFMath::Vector3 _position;
        std::vector<RFMath::Vector3*>* _pVertices;
        std::vector<RFMath::Vector3*>* _pVertexBuffer;
    private:
        void _Construct(const RFMath::Vector3& position);
    };
}

#endif