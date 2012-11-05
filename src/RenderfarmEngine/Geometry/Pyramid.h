#pragma once

#ifndef _PYRAMID_H_
#define _PYRAMID_H_

#include "../Resources.h"
#include "Geometry.h"

#include <iostream>
#include <vector>

namespace RFGeometry
{
    class DLL_API Pyramid : public Geometry
    {
    public:
        Pyramid();
        Pyramid(float base, float height);
        Pyramid(float base, float height, const RFMath::Vector3& position);
        virtual ~Pyramid();

        float GetBase();
        void SetBase(float base);

        float GetHeight();
        void SetHeight(float height);

        void PrepareBuffers();
        void Print(std::ostream& output);
    private:
        void _Construct(float base, float height);

        float _base;
        float _height;
    };
}

#endif