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
        Matrix();
        virtual ~Matrix();
    protected:
    };
}

#endif