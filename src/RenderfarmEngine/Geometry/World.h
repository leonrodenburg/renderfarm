#pragma once

#ifndef _WORLD_H_
#define _WORLD_H_

#include "../Resources.h"
#include "Geometry.h"
#include <map>

#ifdef DLL_EXPORTS
#define DLL_API __declspec(dllexport)
#else
#define DLL_API __declspec(dllimport)
#endif

namespace RFGeometry
{
    class DLL_API World
    {
    public:
        World();
        virtual ~World();

        int AddGeometry(Geometry* pGeometry);
        void RemoveGeometry(int index);
    protected:
        std::map<int, Geometry*>* _pGeometry;
        int _currentIndex;
    };
}

#endif