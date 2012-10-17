#pragma once

#ifndef _WORLD_H_
#define _WORLD_H_

#include "../Resources.h"
#include "Geometry.h"

#include <map>
#include <vector>

namespace RFGeometry
{
    class DLL_API World
    {
    public:
        World();
        virtual ~World();

        int AddGeometry(Geometry* pGeometry);
        void RemoveGeometry(int index);

        std::vector<RFGeometry::Vertex*>* BuildGeometry();
    protected:
        std::map<int, Geometry*>* _pGeometry;
        std::vector<RFGeometry::Vertex*>* _pVertices;
        int _currentIndex;
    };
}

#endif