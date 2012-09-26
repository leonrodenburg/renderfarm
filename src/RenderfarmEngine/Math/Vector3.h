#pragma once

#ifndef _VECTOR3_H_
#define _VECTOR3_H_

#include "../Resources.h"
#include "Utility.h"

#include <iostream>

#ifdef DLL_EXPORTS
#define DLL_API __declspec(dllexport)
#else
#define DLL_API __declspec(dllimport)
#endif

namespace RFMath
{
    class Matrix;

    class DLL_API Vector3
    {
    public:
        Vector3();
        Vector3(float x, float y, float z);
        Vector3(const Vector3& vector);
        virtual ~Vector3();

        bool IsZero() const;
        bool IsUnit() const;
        void Clean();

        float Length() const;
        float LengthSquared() const;
        Vector3 Normalize();

        float Dot(const Vector3& vector) const;
        Vector3 Cross(const Vector3& vector) const;

        float GetX() const { return this->_x; }
        float GetY() const { return this->_y; }
        float GetZ() const { return this->_z; }

        void Set(float x, float y, float z);
        void SetX(float x) { this->_x = x; }
        void SetY(float y) { this->_y = y; }
        void SetZ(float z) { this->_z = z; }

        Vector3& operator=(const Vector3& vector);
        Vector3 operator-() const;
        Vector3 operator+(const Vector3& vector) const;
        Vector3& operator+=(const Vector3& vector);
        Vector3 operator-(const Vector3& vector) const;
        Vector3& operator-=(const Vector3& vector);
        Vector3 operator*(const float scalar) const;
        DLL_API friend Vector3 operator*(const float scalar, const Vector3& vector);
        Vector3& operator*=(const float scalar);
        float operator[](unsigned int i) const;
        bool operator==(const Vector3& vector) const;
        DLL_API friend std::ostream& operator<<(std::ostream& output, const Vector3& vector);

        static Vector3 xAxis;
        static Vector3 yAxis;
        static Vector3 zAxis;
        static Vector3 origin;

    protected:
        float _x;
        float _y;
        float _z;
    };
}

#endif