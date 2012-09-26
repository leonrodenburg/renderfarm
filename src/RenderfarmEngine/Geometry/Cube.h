#pragma once

#ifndef _CUBE_H_
#define _CUBE_H_

#include "../Resources.h"
#include "Geometry.h"

#include <iostream>

#ifdef DLL_EXPORTS
#define DLL_API __declspec(dllexport)
#else
#define DLL_API __declspec(dllimport)
#endif

namespace RFGeometry
{
    class DLL_API Cube : public Geometry
    {
    public:
        Cube();
        Cube(float size);
        Cube(float size, const RFMath::Vector3& position);
        virtual ~Cube();

        float GetSize();
        void SetSize(float size);

        RFMath::Vector3* GetVertices();
        unsigned int GetVerticesCount();
        RFMath::Vector3** GetVertexBuffer();
        unsigned int GetVertexBufferCount();
        
        void Print(std::ostream& output);
    private:
        void _Construct(float size);

        void _CalculateVertices();
        void _CalculateVertexBuffer();

        float _size;
        RFMath::Vector3 _vertices[8];
        RFMath::Vector3* _vertexBuffer[36];
    };
}

#endif