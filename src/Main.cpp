#include "Geometry/World.h"
#include "Geometry/Cube.h"

#include <iostream>
#include <cstdio>
//#include <vld.h>

int main(int argc, char** argv)
{
    std::cout << "Renderfarm 0.1a - by Leon Rodenburg" << std::endl;

    // Create world
    RFGeometry::World* pWorld = new RFGeometry::World();

    // Create some geometry
    RFGeometry::Cube* pCube1 = new RFGeometry::Cube(10.0f, RFMath::Vector3(10.0f, 10.0f, 10.0f));
    RFGeometry::Cube* pCube2 = new RFGeometry::Cube(5.0f);
   
    // Add geometry to world
    pWorld->AddGeometry(pCube1);
    pWorld->AddGeometry(pCube2);

    std::cout << *pCube1 << std::endl;
    std::cout << *pCube2 << std::endl;

    // Build the buffer (this can be fed to the pipeline later)
    std::vector<RFMath::Vector3*> buffer = pWorld->BuildGeometry();

    delete pCube1;
    delete pCube2;
    delete pWorld;

    std::getchar();
    return 0;
}