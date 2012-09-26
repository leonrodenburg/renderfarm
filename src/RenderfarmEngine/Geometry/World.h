#pragma once

#ifndef _WORLD_H_
#define _WORLD_H_

#include "../Resources.h"
#include "Geometry.h"

#include <map>
#include <vector>

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

        std::vector<RFMath::Vector3*>& BuildGeometry();
    protected:
        std::map<int, Geometry*>* _pGeometry;
        std::vector<RFMath::Vector3*>* _pVertices;
        int _currentIndex;
    };
}

#endif