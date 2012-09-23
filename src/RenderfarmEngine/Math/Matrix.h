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

		Matrix& Translate(const Vector3& vector);
		Matrix& TranslateX(float x);
		Matrix& TranslateY(float y);
		Matrix& TranslateZ(float z);

        /**
         * Operators
         */
		Matrix& operator=(const Matrix& matrix);
		bool operator==(const Matrix& matrix);
		bool operator!=(const Matrix& matrix);
		float operator[](unsigned int i) const;
		float operator()(unsigned int i) const;
		float operator()(unsigned int i, unsigned int j) const;
		Matrix operator*(float scalar) const;
		DLL_API friend Matrix operator*(float scalar, const Matrix& matrix);
		Matrix& operator*=(float scalar);
		Matrix operator*(const Matrix& matrix) const;
		Matrix& operator*=(const Matrix& matrix);
		DLL_API friend std::ostream& operator<<(std::ostream& output, const Matrix& matrix);
    protected:
        float _elements[16];
    };
}

#endif