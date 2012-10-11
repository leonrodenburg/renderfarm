//
//  Main.cpp
//  renderfarm-osx
//
//  Created by Léon Rodenburg on 10/11/12.
//  Copyright (c) 2012 Léon Rodenburg. All rights reserved.
//

#include "Geometry/World.h"
#include "Core/Kernel.h"

int main(int argc, const char * argv[])
{
    RFGeometry::World* pWorld = new RFGeometry::World();
    RFCore::Kernel* pKernel = new RFCore::Kernel(pWorld, 800, 600);
    
    std::cout << "Now also on OS X!" << std::endl;
    
    delete pKernel;
    delete pWorld;
}

