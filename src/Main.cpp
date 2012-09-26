#include "Geometry/Cube.h"
#include "Geometry/Cube.h"

#include <iostream>
#include <cstdio>
//#include <vld.h>

int main(int argc, char** argv)
{
    std::cout << "Renderfarm 0.1a - by Leon Rodenburg" << std::endl;

    RFGeometry::Cube* pCube = new RFGeometry::Cube(10.0f, RFMath::Vector3(10.0f, 10.0f, 10.0f));
    std::cout << *pCube << std::endl;
    delete pCube;

    std::getchar();
    return 0;
}