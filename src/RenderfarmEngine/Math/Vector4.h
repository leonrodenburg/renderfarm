#pragma once

#ifndef _VECTOR4_H_
#define _VECTOR4_H_

#include "../Resources.h"
#include "Utility.h"

#include <iostream>

#ifdef DLL_EXPORT
#define DLL_API __declspec(dllexport)
#else
#define DLL_API __declspec(dllimport)
#endif

namespace RFMath
{
    class Matrix;
    class Vector3;

    class DLL_API Vector4
    {
    public:
        Vector4();
        Vector4(const Vector3& vector, float w);
        Vector4(float x, float y, float z, float w);
        Vector4(const Vector4& vector);
        virtual ~Vector4();

        bool IsZero() const;
        bool IsUnit() const;
        void Clean();

        float Length() const;
        float LengthSquared() const;
        Vector4 Normalize();

        float Dot(const Vector4& vector) const;

        float GetX() const { return this->_x; }
        float GetY() const { return this->_y; }
        float GetZ() const { return this->_z; }
        float GetW() const { return this->_w; }

        void Set(float x, float y, float z, float w);
        void SetX(float x) { this->_x = x; }
        void SetY(float y) { this->_y = y; }
        void SetZ(float z) { this->_z = z; }
        void SetW(float w) { this->_w = w; }

        Vector4& operator=(const Vector4& vector);
        Vector4 operator-() const;
        Vector4 operator+(const Vector4& vector) const;
        Vector4& operator+=(const Vector4& vector);
        Vector4 operator-(const Vector4& vector) const;
        Vector4& operator-=(const Vector4& vector);
        Vector4 operator*(const float scalar) const;
        DLL_API friend Vector4 operator*(const float scalar, const Vector4& vector);
        Vector4& operator*=(const float scalar);
        float operator[](unsigned int i) const;
        bool operator==(const Vector4& vector) const;
        DLL_API friend std::ostream& operator<<(std::ostream& output, const Vector4& vector);

        static Vector4 xAxis;
        static Vector4 yAxis;
        static Vector4 zAxis;
        static Vector4 wAxis;
        static Vector4 origin;

    protected:
        float _x;
        float _y;
        float _z;
        float _w;
    };
}

#endif