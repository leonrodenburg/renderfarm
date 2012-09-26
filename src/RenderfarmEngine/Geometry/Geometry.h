#pragma once

#ifndef _GEOMETRY_H_
#define _GEOMETRY_H_

#include "../Resources.h"
#include "../Math/Vector3.h"

#include <iostream>

#ifdef DLL_EXPORTS
#define DLL_API __declspec(dllexport)
#else
#define DLL_API __declspec(dllimport)
#endif

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

        virtual RFMath::Vector3* GetVertices() = 0;
        virtual const RFMath::Vector3** GetVertexBuffer() = 0;
        virtual void Print(std::ostream& output) = 0;

        DLL_API friend std::ostream& operator<<(std::ostream& output, Geometry& geometry);
    protected:
        RFMath::Vector3 _position;
    };
}

#endif