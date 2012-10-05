#pragma once

#ifndef _MATRIX_H_
#define _MATRIX_H_

#include "../Resources.h"
#include "Utility.h"
#include "Vector3.h"
#include "Vector4.h"

#include <iostream>

#ifdef DLL_EXPORT
#define DLL_API __declspec(dllexport)
#else
#define DLL_API __declspec(dllimport)
#endif

namespace RFMath
{
    class DLL_API Matrix
    {
    public:
        Matrix();
        Matrix(const Matrix& matrix);
        virtual ~Matrix();

        void Identity();
        void Clean();

        bool IsIdentity();
        bool IsZero();

        float* GetPointer();

        Vector3 Transform(const Vector3& vector);

        Matrix& Transpose();
        DLL_API friend Matrix Transpose(const Matrix& matrix);

        Matrix& Inverse();
        DLL_API friend Matrix Inverse(const Matrix& matrix);

        Matrix& Translate(const Vector3& vector);
        Matrix& Translate(float x, float y, float z);
        Matrix& TranslateX(float x);
        Matrix& TranslateY(float y);
        Matrix& TranslateZ(float z);

        Matrix& Scale(const Vector3& vector);
        Matrix& Scale(float x, float y, float z);
        Matrix& ScaleX(float x);
        Matrix& ScaleY(float y);
        Matrix& ScaleZ(float z);

        Matrix& Rotate(float yaw, float pitch, float roll);
        Matrix& RotateX(float angle);
        Matrix& RotateY(float angle);
        Matrix& RotateZ(float angle);

        Matrix operator-() const;

        Matrix& operator=(const Matrix& matrix);
        bool operator==(const Matrix& matrix);
        bool operator!=(const Matrix& matrix);

        float operator[](unsigned int i) const;
        float operator()(unsigned int i) const;
        float operator()(unsigned int i, unsigned int j) const;

        Matrix operator+(const Matrix& matrix) const;
        Matrix& operator+=(const Matrix& matrix);
        Matrix operator-(const Matrix& matrix) const;
        Matrix& operator-=(const Matrix& matrix);

        Matrix operator*(float scalar) const;
        DLL_API friend Matrix operator*(float scalar, const Matrix& matrix);
        Matrix& operator*=(float scalar);
        Vector4 operator*(const Vector4& vector) const;
        DLL_API friend Vector4 operator*(const Vector4& vector, const Matrix& matrix);
        Matrix operator*(const Matrix& matrix) const;
        Matrix& operator*=(const Matrix& matrix);

        DLL_API friend std::ostream& operator<<(std::ostream& output, const Matrix& matrix);

    protected:
        float _elements[16];
    };
}

#endif