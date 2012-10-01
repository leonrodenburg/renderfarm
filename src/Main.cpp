#include "Core/Kernel.h"

#include "Geometry/World.h"
#include "Geometry/Cube.h"

#include <iostream>
#include <cstdio>
#include <vld.h> // Visual Leak Detector (http://vld.codeplex.com/)

int main(int argc, char** argv)
{
    std::cout << "Renderfarm 0.1a - by Leon Rodenburg" << std::endl;

    // Create world
    RFGeometry::World world;

    // Add geometry to world
    RFGeometry::Cube cube(1.0f, RFMath::Vector3(0.5f, 0.5f, 0.5f));
    world.AddGeometry(&cube);

    // Create kernel
    RFCore::Kernel kernel(&world, 800, 600);

    // Start the kernel
    kernel.Run();

    std::getchar();
    return 0;
}