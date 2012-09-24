#pragma once

#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <iostream>
#include "Utility.h"

#include "Vector3.h"
#include "Vector4.h"

#ifdef DLL_EXPORTS
#define DLL_API __declspec(dllexport)
#else
#define DLL_API __declspec(dllimport)
#endif

namespace RFMath
{
    class DLL_API Matrix
    {
    public:
        /**
         * Constructor and destructor
         */
        Matrix();
        Matrix(const Matrix& matrix);
        virtual ~Matrix();

        /**
         * Methods
         */
        void Identity();
        void Clean();

        bool IsIdentity();
        bool IsZero();

        float* GetPointer();

        Matrix& Transpose();
        friend Matrix Transpose(const Matrix& matrix);

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

        Matrix& Rotation(float y, float x, float z);
        Matrix& RotationX(float angle);
        Matrix& RotationY(float angle);
        Matrix& RotationZ(float angle);

        /**
         * Operators
         */
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
        Vector3 operator*(const Vector3& vector) const;
        DLL_API friend Vector3 operator*(const Vector3& vector, const Matrix& matrix);
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