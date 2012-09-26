#pragma once

#ifndef _KERNEL_H_
#define _KERNEL_H_

#include "../Resources.h"

#ifdef DLL_EXPORTS
#define DLL_API __declspec(dllexport)
#else
#define DLL_API __declspec(dllimport)
#endif

namespace RFCore
{
    class DLL_API Kernel
    {
    public:
        Kernel();
        virtual ~Kernel();

        void Run();
    protected:
    };
}

#endif