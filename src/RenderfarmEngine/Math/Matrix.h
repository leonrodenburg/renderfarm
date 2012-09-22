#pragma once

#ifndef _MATRIX_H_
#define _MATRIX_H_
#define DLLEX __declspec(dllexport)

#include <iostream>
#include "Utility.h"

namespace RFMath
{
    class DLLEX Matrix
    {
    public:
        /**
         * Constructor and destructor
         */
        Matrix();
        virtual ~Matrix();

        /**
         * Operators
         */
        DLLEX friend std::ostream& operator<<(std::ostream& output, const Matrix& matrix);
    protected:
        float _elements[16];
    };
}

#endif