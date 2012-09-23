#pragma once

#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <iostream>
#include "Utility.h"

namespace RFMath
{
	class Vector;

    class DLLEX Matrix
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
		bool IsIdentity();

		float* GetPointer();

        /**
         * Operators
         */
		Matrix operator=(const Matrix& matrix);
		float operator[](unsigned int i);
		float operator()(unsigned int i);
		float operator()(unsigned int i, unsigned int j);
		Matrix operator*(float scalar);
		DLLEX friend Matrix operator*(float scalar, const Matrix& matrix);
		Matrix operator*(const Matrix& matrix);
		DLLEX friend std::ostream& operator<<(std::ostream& output, const Matrix& matrix);
    protected:
        float _elements[16];
    };
}

#endif